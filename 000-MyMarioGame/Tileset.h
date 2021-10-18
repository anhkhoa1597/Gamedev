#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "AssetIDs.h"
#include "Animations.h"

using namespace std;

class Tileset
{
	LPTEXTURE tex;

	int tile_width;
	int tile_height;
	int spacing;
	int tile_count;
	int column;

	unordered_map<int, LPSPRITE> tileset; //a tileset has many sprite
public:
	Tileset(LPTEXTURE tex, int tile_width, int tile_height, int spacing, int tile_count, int column);
	~Tileset();
	void Load();
	LPSPRITE Get(int id);
};
typedef Tileset* LPTileset;