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

Map::Map(int width, int height, int tile_width, int tile_height)
{
	this->width = width;
	this->height = height;
	this->tile_width = tile_width;
	this->tile_height = tile_height;
}

Map::~Map()
{
}

void Map::AddLayer(string layer)
{
	vector<vector<unsigned int>> background;
	parse_tiles(layer, this->height, background);
	this->tiled_background.push_back(background);
}

void Map::Render()
{
	list<vector<vector<unsigned int>>>::iterator i;
	for (i = tiled_background.begin(); i != tiled_background.end(); ++i)
	{
		vector<vector<unsigned int>> background = (*i);
		for (int row = 0; row < this->height; row++)
		{
			for (int column = 0; column < this->width; column++)
			{
				if (background[row][column] != 0)
				{
					CAnimations* animations = CAnimations::GetInstance();
					float x = column * tile_width;
					float y = row * tile_height;
					animations->Get(ID_SPRITE_TILESET + background[row][column])->Render(x, y);
				}
			}
		}
	}
}