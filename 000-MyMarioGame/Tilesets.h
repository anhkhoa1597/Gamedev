#pragma once
#include <unordered_map>
#include "Tileset.h"

using namespace std;

class Tilesets
{
	static Tilesets* __instance;
	unordered_map<int, LPTileset> tilesets;
public:
	void Add(int tex_id, int tile_width, int tile_height, int spacing, int tile_count, int column);
	LPTileset Get(int tex_id);

	static Tilesets* GetInstance();
};