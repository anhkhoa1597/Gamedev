#pragma once
#include <unordered_map>
#include "Sprite.h"
#include "Texture.h"

using namespace std;

class Tileset
{
	int id;
	int tile_width;
	int tile_height;
	int spacing;
	int tile_count;
	int column;

	static Tileset* __instance;

	unordered_map<int, LPSPRITE> tileset;

public:
	Tileset();
	Tileset(int id, int tile_width, int tile_height, int spacing, int tile_count, int column);
	~Tileset();
	void Get(int &tile_width, int &tile_height, int &spacing, int &tile_count, int &column);

	void Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex);
	LPSPRITE Get(int id);
	void Clear();

	static Tileset* GetInstance();
};