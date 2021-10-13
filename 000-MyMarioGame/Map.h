#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include <string>
#include <list>

#include "Collision.h"
#include "Game.h"
#include "Sprites.h"
#include "GameObject.h"
#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include "Coin.h"
#include "Platform.h"
#include "Ground.h"
#include "Pipes.h"

#include "debug.h"
#include "tinyxml2.h"
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
	virtual void Update();
	void Load(string filePath, list<LPGAMEOBJECT> &objects);
};