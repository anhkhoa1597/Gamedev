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

class CMap
{
	int width;
	int height;
	int tile_width;
	int tile_height;
	list<vector<vector<unsigned int>>> tiled_background;
public:
	CMap(int width, int height, int tile_width, int tile_height);
	void GetWidthHeight(int& w, int& h) { w = this->width * this->tile_width; h = this->height * this->tile_height; }
	void GetTileWidthHeight(int& tile_width, int& tile_height);
	void GetNumberTileWidthHeight(int& w, int& h);
	void AddLayer(string layer);
	~CMap();
	void Render(int left, int right, int top, int bottom);
}; typedef CMap* LPMAP;