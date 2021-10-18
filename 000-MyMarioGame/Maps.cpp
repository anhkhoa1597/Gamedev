#include "Maps.h"

Maps* Maps::__instance = NULL;

Maps* Maps::GetInstance()
{
	if (__instance == NULL) __instance = new Maps();
	return __instance;
}

void Maps::Add(int id, LPMap map)
{
	if (maps[id] != NULL)
		DebugOut(L"[WARNING] Map %d already exists\n", id);

	maps[id] = map;
}

LPMap Maps::Get(int id)
{
	LPMap map = maps[id];
	if (map == NULL)
		DebugOut(L"[ERROR] Map ID %d not found\n", id);
	return map;
}

void Maps::Clear()
{
	for (auto x : maps)
	{
		LPMap map = x.second;
		delete map;
	}

	maps.clear();
}