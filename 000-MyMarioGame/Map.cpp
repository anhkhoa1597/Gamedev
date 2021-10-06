#include "Map.h"

//list<LPGAMEOBJECT> objects;

void parse_tiles(const std::string& gid_list, int height, std::vector<std::vector<unsigned int>>& tiled_background) {
    std::vector<std::vector<unsigned int> > tiles(height);
    std::string value;
	int row = -1;
    for (unsigned int index = 0; index < gid_list.length(); index++) {
        if (gid_list[index] == ',') {
            tiles[row].push_back(std::stoi(value));
            value.clear();
        }
        else if (gid_list[index] == '\n') {
            //tiles[row].push_back(std::stoi(value));
            //value.clear();
            //tiles.push_back();
            row += 1;
        }
		else if (gid_list[index] >= '0' && gid_list[index] <= '9')
		{
			value += gid_list[index];
		}
    }
	tiles[row - 1].push_back(std::stoi(value));

    tiled_background = tiles;
}

Map::Map()
{
	Next = -1;
}

Map::~Map()
{

}


void Map::Load(string filepath)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filepath.c_str());
	tinyxml2::XMLElement* map = doc.FirstChildElement("map");
	map->QueryIntAttribute("width", &width);
	map->QueryIntAttribute("height", &height);
	map->QueryIntAttribute("tilewidth", &tile_width);
	map->QueryIntAttribute("tileheight", &tile_height);
	tinyxml2::XMLElement* pLayer = map->FirstChildElement("layer");
	while (pLayer != nullptr)
	{
		string name = pLayer->Attribute("name");
		if (name == "background") {}
		else if (name == "graphics")
		{
			tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) parse_tiles(pData->GetText(), height, tiled_background);
		}
		pLayer = pLayer->NextSiblingElement("layer");
	}

}

void Map::Render()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (tiled_background[i][j] != 0)
			{
				LPSPRITE sprite = CSprites::GetInstance()->Get(tiled_background[i][j]);
				sprite->Draw(tile_width/2 + j * tile_width, tile_height/2 + i * tile_height);
			}
		}
	}
}