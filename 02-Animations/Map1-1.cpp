#include "Map1_1.h"

Map1_1::Map1_1() : Map()
{
	Load(TILEDMAP1_1);
};

Map1_1::~Map1_1()
{
};

void Map1_1::Render()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (tiled_background[i][j] != 0)
			{
				LPSPRITE sprite = CSprites::GetInstance()->Get(tiled_background[i][j]);
				sprite->Draw(tile_width/2 + j * tile_width,tile_height/2 + i * tile_height);
			}
		}
	}
};