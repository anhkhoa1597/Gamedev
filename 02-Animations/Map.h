#pragma once
#include <d3dx10.h>
#include <vector>
#include "Texture.h"
#include "tinyxml2.h"
#include <string>

using namespace std;

/*
	Manage Map database
*/
class Map
{
	int Next;
public:
	Map();
	virtual ~Map();
	virtual void Draw();
	void Load(string filePath);
};