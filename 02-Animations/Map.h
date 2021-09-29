#pragma once
#include <unordered_map>
#include <d3dx10.h>

#include "Texture.h"

using namespace std;

/*
	Manage Map database
*/
class Map
{
public:
	Map();
	void Load(int id);
};