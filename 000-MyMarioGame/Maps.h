#pragma once

#include "Map.h"

class CMaps
{
	static CMaps* __instance;
	unordered_map<int, LPMAP> maps;

public:
	void Add(int id, LPMAP map);
	LPMAP Get(int id);
	void Clear();

	static CMaps* GetInstance();
};