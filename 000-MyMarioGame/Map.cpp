#include "Map.h"

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

CMap::CMap(int width, int height, int tile_width, int tile_height, int nextLayerId)
{
	this->width = width;
	this->height = height;
	this->tile_width = tile_width;
	this->tile_height = tile_height;
	this->nextLayerId = nextLayerId;
}

CMap::~CMap()
{
}

void CMap::GetTileWidthHeight(int& tile_width, int& tile_height)
{
	tile_width = this->tile_width;
	tile_height = this->tile_height;
}

void CMap::GetNumberTileWidthHeight(int& w, int& h)
{
	w = this->width;
	h = this->height;
}

void CMap::AddLayer(int id, string layer)
{
	vector<vector<unsigned int>> background;
	parse_tiles(layer, height, background);
	layers[id] = background;
}

vector<vector<unsigned int>> CMap::GetLayer(int id)
{ 
	vector<vector<unsigned int>> layer = layers[id];
	if (layer.size() == 0)
		DebugOut(L"[ERROR] layer ID %d not found\n", id);
		
	return layer;
}

void CMap::Render(int left, int top, int right, int bottom, int id)
{
	vector<vector<unsigned int>> layer = GetLayer(id);
	for (int row = top; row < bottom; row++)
	{
		for (int column = left; column < right; column++)
		{
			if (layer[row][column] != 0)
			{
				CAnimations* animations = CAnimations::GetInstance();
				float x = (float)(column * tile_width);
				float y = (float)(row * tile_height);
				animations->Get(ID_SPRITE_TILESET + layer[row][column])->Render(x, y);
			}
		}
	}
}