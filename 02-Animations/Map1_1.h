#pragma once
#include "Map.h"

#define ID_TILESET_MAP 11111
#define TILEDMAP1_1 "map/1-1.tmx"


class Map1_1 : public Map
{
public:
	Map1_1();
	~Map1_1();
	void Render();
};