#pragma once

#define ID_ANI_TILESET 60000

class Tileset
{
	int tile_width;
	int tile_height;
	int spacing;
	int tile_count;
	int column;
public:
	Tileset(int tile_width, int tile_height, int spacing, int tile_count, int column);
	~Tileset();
	void Get(int &tile_width, int &tile_height, int &spacing, int &tile_count, int &column);
};