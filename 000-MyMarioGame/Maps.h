#pragma once

#include "Map.h"

class Maps
{
	static Maps* __instance;
	unordered_map<int, LPMap> maps;

public:
	void Add(int id, LPMap map);
	LPMap Get(int id);
	void Clear();

	static Maps* GetInstance();
};