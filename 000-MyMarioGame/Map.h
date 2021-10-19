#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

#include "debug.h"
#include "GameObject.h"
#include "AssetIDs.h"
using namespace std;

/*
	Manage Map database
*/

class Map
{
	int width;
	int height;
	int tile_width;
	int tile_height;
	list<vector<vector<unsigned int>>> tiled_background;
public:
	Map(int width, int height, int tile_width, int tile_height);
	void AddLayer(string layer);
	~Map();
	void Render();
	void Update();
	void Load(string filePath);
}; typedef Map* LPMap;