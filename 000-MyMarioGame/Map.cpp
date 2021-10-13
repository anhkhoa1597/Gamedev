#include "Map.h"
CMario* mario;

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
            row += 1;
        }
		else if (gid_list[index] >= '0' && gid_list[index] <= '9')
		{
			value += gid_list[index];
		}
    }
	row = row - 1;
	tiles[row].push_back(std::stoi(value));
    tiled_background = tiles;
}

Map::Map()
{
	Next = -1;
	width = 0;
	height = 0;
	tile_width = 0;
	tile_height = 0;
}

Map::~Map()
{

}


void Map::Load(string filepath, list<LPGAMEOBJECT> &objects)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filepath.c_str());
	tinyxml2::XMLElement* map = doc.FirstChildElement("map");
	{
		map->QueryIntAttribute("width", &width);
		map->QueryIntAttribute("height", &height);
		map->QueryIntAttribute("tilewidth", &tile_width);
		map->QueryIntAttribute("tileheight", &tile_height);
	}

	//load graphic of game
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

	//load object of game
	tinyxml2::XMLElement* pObjectGroup = map->FirstChildElement("objectgroup");
	while (pObjectGroup != nullptr)
	{
		string nameObjectGroup = pObjectGroup->Attribute("name");
		tinyxml2::XMLElement* pObject = pObjectGroup->FirstChildElement("object");
		while (pObject != nullptr)
		{
			float x, y, width, height;
			pObject->QueryFloatAttribute("x", &x);
			pObject->QueryFloatAttribute("y", &y);
			pObject->QueryFloatAttribute("width", &width);
			pObject->QueryFloatAttribute("height", &height);
			if (nameObjectGroup == "ground")
			{
				CGround* ground = new CGround(x, y, width, height);
				objects.push_back(ground);
			}
			else if (nameObjectGroup == "pipes")
			{
				CPipes* pipe = new CPipes(x, y, width, height);
				objects.push_back(pipe);
			}
			else if (nameObjectGroup == "bricks")
			{
				CBrick* brick = new CBrick(x, y);
				objects.push_back(brick);
			}
			else if (nameObjectGroup == "q_bricks")
			{

			}
			else if (nameObjectGroup == "other")
			{
				string nameObject = pObject->Attribute("name");
				if (nameObject == "start") {
					mario = new CMario(x, y);
					objects.push_back(mario);
				}
				else if (nameObject == "checkPoint")
				{
					//mario->SetCheckPoint(x, y);
				}
			}
			pObject = pObject->NextSiblingElement("object");
		}
		pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
	}
}

void Map::Update()
{
	// Update camera to follow mario
	float cx, cy;
	mario->GetPosition(cx, cy);

	////camera follow to mario at the center of screen.
	//cx -= SCREEN_WIDTH / 2; 

	//camera follow to mario at the middle of 6th tile and camera not follow when mario walk to left
	cx -= 80;
	float current_cx, current_cy;
	CGame::GetInstance()->GetCamPos(current_cx, current_cy);
	if (current_cx <= cx) current_cx = cx;
	else cx = current_cx;

	//DebugOut(L"cx: %0.1f, current: %0.1f\n", cx, current_cx);
	cy = 0;
	//cy -= SCREEN_HEIGHT / 2;

	if (cx < 0) cx = 0;

	CGame::GetInstance()->SetCamPos(cx, cy);
}

void Map::Render()
{
	for (int row = 0; row < this->height; row++)
	{
		for (int column = 0; column < this->width; column++)
		{
			if (tiled_background[row][column] != 0)
			{
				CAnimations* animations = CAnimations::GetInstance();
				int x = column * tile_width;
				int y = row * tile_height;
				animations->Get(tiled_background[row][column])->Render(x, y);
			}
		}
	}
}