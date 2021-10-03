#pragma once
#include <d3dx10.h>
#include <vector>
#include "Sprites.h"
#include "tinyxml2.h"
#include <string>

using namespace std;

/*
	Manage Map database
*/
class Map
{
	int Next;
	int width;
	int height;
	int tile_width;
	int tile_height;
	vector<vector<unsigned int>> tiled_background;
public:
	Map();
	virtual ~Map();
	virtual void Render();
	void Load(string filePath);
};