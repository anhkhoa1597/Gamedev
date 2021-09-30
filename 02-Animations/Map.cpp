#include "debug.h"
#include "Map.h"

std::vector<std::vector<unsigned int> > parse_tiles(const std::string& gid_list, int width, int height) {
    std::vector<std::vector<unsigned int> > tiles(height);
    std::string value;
    unsigned int row = 0;
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
            value += gid_list[index];
    }

    return tiles;
}

Map::Map()
{
	Next = -1;
}

Map::~Map()
{

}

void Map::Draw()
{

}

void Map::Load(string filepath)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filepath.c_str());
	tinyxml2::XMLElement* map = doc.FirstChildElement("map");
	int width, height, tilewidth, tileheight;
	map->QueryIntAttribute("width", &width);
	map->QueryIntAttribute("height", &height);
	map->QueryIntAttribute("tilewidth", &tilewidth);
	map->QueryIntAttribute("tileheight", &tileheight);
	tinyxml2::XMLElement* pLayer = map->FirstChildElement("layer");
	tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
	if (pData != NULL)
	{
        const auto tiles = parse_tiles(pData->GetText(), width, height);
	}
}