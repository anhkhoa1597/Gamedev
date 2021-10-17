#include "Tileset.h"

Tileset* Tileset::__instance = NULL;

Tileset::Tileset()
{

}

Tileset::Tileset(int id, int tile_width, int tile_height, int spacing, int tile_count, int column)
{
	this->id = id;
	this->tile_width = tile_width;
	this->tile_height = tile_height;
	this->spacing = spacing;
	this->tile_count = tile_count;
	this->column = column;
}

Tileset::~Tileset()
{

}

void Tileset::Get(int& tile_width, int& tile_height, int& spacing, int& tile_count, int& column)
{
	tile_width = this->tile_width;
	tile_height = this->tile_height;
	spacing = this->spacing;
	tile_count = this->tile_count;
	column = this->column;
}

void Tileset::Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	if (tileset[id] != NULL)
		DebugOut(L"[WARNING] Sprite %d already exists\n", id);

	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	tileset[id] = s;
}

LPSPRITE Tileset::Get(int id)
{
	return tileset[id];
}

void Tileset::Clear()
{
	for (auto x : tileset)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	tileset.clear();
}

Tileset* Tileset::GetInstance()
{
	if (__instance == NULL) __instance = new Tileset();
	return __instance;
}