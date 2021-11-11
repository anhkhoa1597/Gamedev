#include "Tilesets.h"
#include "debug.h"

Tilesets* Tilesets::__instance = NULL;

Tilesets* Tilesets::GetInstance()
{
	if (__instance == NULL) __instance = new Tilesets();
	return __instance;
}

void Tilesets::Add(int tex_id, int tile_width, int tile_height, int spacing, int tile_count, int column)
{
	LPTEXTURE tex = CTextures::GetInstance()->Get(tex_id);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", tex_id);
		return;
	}

	LPTileset tileset = new Tileset(tex, tile_width, tile_height, spacing, tile_count, column);
	tilesets[tex_id] = tileset;
}

LPTileset Tilesets::Get(int tex_id)
{
	LPTileset tileset = tilesets[tex_id];
	if (tileset == NULL)
		DebugOut(L"[ERROR] Tileset ID %d not found\n", tex_id);
	return tileset;
}