#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Coin.h"
#include "DCoin.h"
#include "Mario.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Tilesets.h"
#include "Maps.h"
#include "Ground.h"
#include "Wall.h"
#include "SPlatform.h"
//#include "Koopas.h"

class CPlayScene : public CScene
{
protected:
	LPGAMESETTING setting;
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;
	LPMap map;

	void LoadIdAnimation(string name, int id);
	void LoadAssets(string assetFile);
	void LoadMap(string mapFile);
	void LoadTileset(string tilesetFile);
	void LoadSceneSetting(string scenesettingFile);
public:
	CPlayScene(int id, string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	LPGAMESETTING GetSceneSetting() { return setting; }
	void AddObject(LPGAMEOBJECT object);
	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

