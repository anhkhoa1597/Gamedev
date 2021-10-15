#include "Map1_1.h"

extern Tileset* tileset;

Map1_1::Map1_1() : Map()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	
	Load(TILEDMAP1_1);
	int tileWidth, tileHeight, spacing, tileCount, column;
	tileset->Get(tileWidth, tileHeight, spacing, tileCount, column);

	textures->Add(ID_TILESET_MAP, TILESET_PATH);
	LPTEXTURE texTileset = textures->Get(ID_TILESET_MAP);

	for (int i = 0; i < tileCount; i++)
	{
		int id = ID_SPRITE_TILESET + i + 1;
		int l = (i % column) * tileWidth;
		int r = (tileWidth - 1) + (i % column) * tileWidth;
		int t = (i / column) * tileHeight;
		int b = (tileWidth - 1) + (i / column) * tileHeight;

		sprites->Add(id, l, t, r, b, texTileset);
		LPANIMATION ani = new CAnimation(100);
		ani->Add(id);
		animations->Add(ID_ANI_TILESET + i + 1, ani);
	}
};

Map1_1::~Map1_1()
{
};