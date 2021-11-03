#include "Maps.h"

CMaps* CMaps::__instance = NULL;

CMaps* CMaps::GetInstance()
{
	if (__instance == NULL) __instance = new CMaps();
	return __instance;
}

void CMaps::Add(int id, LPMAP map)
{
	if (maps[id] != NULL)
		DebugOut(L"[WARNING] Map %d already exists\n", id);

	maps[id] = map;
}

LPMAP CMaps::Get(int id)
{
	LPMAP map = maps[id];
	if (map == NULL)
		DebugOut(L"[ERROR] Map ID %d not found\n", id);
	return map;
}

void CMaps::Clear()
{
	for (auto x : maps)
	{
		LPMAP map = x.second;
		delete map;
	}

	maps.clear();
}