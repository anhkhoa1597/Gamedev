#include "Tileset.h"

Tileset::Tileset(LPTEXTURE tex, int tile_width, int tile_height, int spacing, int tile_count, int column)
{
	this->tex = tex;
	this->tile_width = tile_width;
	this->tile_height = tile_height;
	this->spacing = spacing;
	this->tile_count = tile_count;
	this->column = column;
	this->Load();
}

Tileset::~Tileset()
{
}

void Tileset::Load()
{
	for (int i = 0; i < this->tile_count; i++)
	{
		int id = ID_SPRITE_TILESET + i + 1;
		int l = (i % this->column) * this->tile_width;
		int r = (this->tile_width - 1) + (i % this->column) * this->tile_width;
		int t = (i / this->column) * this->tile_height;
		int b = (this->tile_width - 1) + (i / this->column) * this->tile_height;
		CSprites::GetInstance()->Add(id, l, t, r, b, this->tex);

		LPANIMATION ani = new CAnimation();
		ani->Add(id);
		CAnimations::GetInstance()->Add(id, ani);
	}
}

LPSPRITE Tileset::Get(int id)
{
	return tileset[id];
}