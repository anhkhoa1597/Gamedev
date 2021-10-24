#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "QBrick.h"
#include "Coin.h"
#include "DCoin.h"
#include "Mario.h"
#include "Goomba.h"
#include "Tilesets.h"
#include "Maps.h"
#include "Ground.h"
#include "SPlatform.h"
//#include "Koopas.h"


class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;
	LPMap map;

	void LoadAssets(string assetFile);
	void LoadMap(string mapFile);
	void LoadTileset(string tilesetFile);
public:
	CPlayScene(int id, string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

