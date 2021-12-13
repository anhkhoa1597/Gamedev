#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Platform.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, string filePath) :
	CScene(id, filePath)
{
	LPGAMESETTING setting = CGameSetting::GetInstance();
	hud = new CHud(0, 0, setting->hud_width, setting->hud_height); //need constant
	map = NULL;
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}

void CPlayScene::LoadAssets(string assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", ToLPCWSTR(assetFile));

	tinyxml2::XMLDocument doc;
	doc.LoadFile(assetFile.c_str());
	tinyxml2::XMLElement* pAsset = doc.FirstChildElement("asset");

	if (pAsset == nullptr)
	{
		DebugOut(L"[ERROR] Failed to loading tileset file : %s\n", ToLPCWSTR(assetFile));
		return;
	}
	
	//Load Sprites
	tinyxml2::XMLElement* pSpriteGroup = pAsset->FirstChildElement("spritegroup");
	tinyxml2::XMLElement* pSprite = pSpriteGroup->FirstChildElement("sprite");
	while (pSprite != nullptr)
	{
		int id, l, t, r, b, texId;
		pSprite->QueryIntAttribute("id", &id);
		pSprite->QueryIntAttribute("left", &l);
		pSprite->QueryIntAttribute("top", &t);
		pSprite->QueryIntAttribute("right", &r);
		pSprite->QueryIntAttribute("bottom", &b);
		pSprite->QueryIntAttribute("texid", &texId);
		LPTEXTURE tex = CTextures::GetInstance()->Get(texId);
		if (tex == NULL)
		{
			DebugOut(L"[ERROR] Texture ID %d not found!\n", texId);
			return;
		}
		CSprites::GetInstance()->Add(id, l, t, r, b, tex);

		pSprite = pSprite->NextSiblingElement("sprite");
	}

	//Load Animation
	tinyxml2::XMLElement* pAnimationGroup = pAsset->FirstChildElement("animationgroup");
	tinyxml2::XMLElement* pAnimation = pAnimationGroup->FirstChildElement("animation");
	while (pAnimation != nullptr)
	{
		string name = pAnimation->Attribute("name");
		LPANIMATION ani = new CAnimation();
		int ani_id;
		pAnimation->QueryIntAttribute("id", &ani_id);
		CGameSetting::GetInstance()->LoadIdAnimations(name, ani_id);
		tinyxml2::XMLElement* pSprite = pAnimation->FirstChildElement("sprite");
		while (pSprite != nullptr)
		{
			int id, frame_time;
			pSprite->QueryIntAttribute("id", &id);
			pSprite->QueryIntAttribute("time", &frame_time);
			ani->Add(id, frame_time);
			pSprite = pSprite->NextSiblingElement("sprite");
		}
		CAnimations::GetInstance()->Add(ani_id, ani);

		pAnimation = pAnimation->NextSiblingElement("animation");
	}
	DebugOut(L"[INFO] Done loading assets from %s\n", ToLPCWSTR(assetFile));
}

void CPlayScene::LoadTileset(string tilesetFile)
{
	DebugOut(L"[INFO] Start loading tileset from : %s \n", ToLPCWSTR(tilesetFile));
	tinyxml2::XMLDocument doc;
	doc.LoadFile(tilesetFile.c_str());

	tinyxml2::XMLElement* pTileset = doc.FirstChildElement("tileset");

	if (pTileset == nullptr)
	{
		DebugOut(L"[ERROR] Failed to loading tileset file : %s\n", ToLPCWSTR(tilesetFile));
		return;
	}

	{
		int texId, tileWidth, tileHeight, spacing, tileCount, column;
		pTileset->QueryIntAttribute("texid", &texId);
		pTileset->QueryIntAttribute("tilewidth", &tileWidth);
		pTileset->QueryIntAttribute("tileheight", &tileHeight);
		pTileset->QueryIntAttribute("spacing", &spacing);
		pTileset->QueryIntAttribute("tilecount", &tileCount);
		pTileset->QueryIntAttribute("columns", &column);
		Tilesets::GetInstance()->Add(texId, tileWidth,tileHeight,spacing,tileCount,column);
	}
	
	DebugOut(L"[INFO] Done loading tileset from %s\n", ToLPCWSTR(tilesetFile));
}

void CPlayScene::LoadMap(string mapFile)
{
	DebugOut(L"[INFO] Start loading map from : %s \n", ToLPCWSTR(mapFile));

	tinyxml2::XMLDocument doc;
	doc.LoadFile(mapFile.c_str());
	tinyxml2::XMLElement* pMap = doc.FirstChildElement("map");
	if (pMap == nullptr)
	{
		DebugOut(L"[ERROR] Failed to loading map file : %s\n", ToLPCWSTR(mapFile));
		return;
	}
	int id = -1;
	int width, height, tileWidth, tileHeight, nextLayerId;
	{
		pMap->QueryIntAttribute("width", &width);
		pMap->QueryIntAttribute("height", &height);
		pMap->QueryIntAttribute("tilewidth", &tileWidth);
		pMap->QueryIntAttribute("tileheight", &tileHeight);
		pMap->QueryIntAttribute("nextlayerid", &nextLayerId);
	}
	LPMAP map = new CMap(width, height, tileWidth, tileHeight, nextLayerId);
	
	LPGAME game = CGame::GetInstance();
	//Load extra properties
	tinyxml2::XMLElement* pProperty = pMap->FirstChildElement("properties")->FirstChildElement("property");
	while (pProperty != nullptr)
	{
		string nameProperty = pProperty->Attribute("name");
		if (nameProperty == "id") pProperty->QueryIntAttribute("value", &id);
		else if (nameProperty == "source")
		{
			//load tileset
			string path = pProperty->Attribute("value");
			LoadTileset(path);
		}
		//unknow property
		else {
			DebugOut(L"[WARNING] Unknow property %s of map %s\n", ToLPCWSTR(nameProperty), ToLPCWSTR(mapFile));
			return;
		}
		pProperty = pProperty->NextSiblingElement("property");
	}

	//Load Tiled-background
	tinyxml2::XMLElement* pLayer = pMap->FirstChildElement("layer");
	while (pLayer != nullptr)
	{
		string name = pLayer->Attribute("name");
		int LayerId;
		pLayer->QueryIntAttribute("id", &LayerId);
		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
		map->AddLayer(LayerId, pData->GetText());
		pLayer = pLayer->NextSiblingElement("layer");
	}
	this->map = map;
	if (id < 0) return;
	CMaps::GetInstance()->Add(id, map);

	//Load Objects
	tinyxml2::XMLElement* pObjectGroup = pMap->FirstChildElement("objectgroup");
	pObjectGroup->QueryIntAttribute("id", &layerObject);
	tinyxml2::XMLElement* pObject = pObjectGroup->FirstChildElement("object");
	while (pObject != nullptr)
	{
		float x, y;
		int width, height;
		pObject->QueryFloatAttribute("x", &x);
		pObject->QueryFloatAttribute("y", &y);
		pObject->QueryIntAttribute("width", &width);
		pObject->QueryIntAttribute("height", &height);
		string name = pObject->Attribute("name");
		CGameObject* obj = NULL;
		if (name == "mario")
		{
			string type = pObject->Attribute("type");
			if (game->IsMarioGoThroughPipe()) //specific mario go through pipe
			{
				int state = -1;
				if (type == "start")
				{
					pObject = pObject->NextSiblingElement("object");
					continue;
				}
				else if (type == "go_up") state = MARIO_STATE_GO_UP;
				else if (type == "go_down") state = MARIO_STATE_GO_DOWN;
				else DebugOut(L"[ERROR] Invalid Type of mario: %s\n", ToLPCWSTR(type));
				obj = new CMario(x, y);
				obj->SetState(state);
				obj->SetLevel(game->GetLevel());
				player = (CMario*)obj;
				DebugOut(L"[INFO] Player object has been created!\n");
			}
			else if (!game->IsMarioGoThroughPipe() && player == NULL) //normal mario starting map
			{
				obj = new CMario(x, y);
				player = (CMario*)obj;
				DebugOut(L"[INFO] Player object has been created!\n");
			}
			else
			{
				pObject = pObject->NextSiblingElement("object");
				continue;
			}
		}
		else if (name == "goomba") obj = new CGoomba(x, y, GOOMBA);
		else if (name == "wing_goomba") obj = new CGoomba(x, y, WGOOMBA);
		else if (name == "red_goomba") obj = new CGoomba(x, y, RGOOMBA);
		else if (name == "red_wing_goomba") obj = new CGoomba(x, y, RWGOOMBA);
		else if (name == "koopa") obj = new CKoopa(x, y, KOOPA);
		else if (name == "wing_koopa") obj = new CKoopa(x, y, WKOOPA);
		else if (name == "red_koopa") obj = new CKoopa(x, y, RKOOPA);
		else if (name == "red_wing_koopa") obj = new CKoopa(x, y, RWKOOPA);
		else if (name == "piranha_plant") obj = new CPiranhaPlant(x, y, PIRANHA_PLANT);
		else if (name == "horizontal_piranha_plant") obj = new CPiranhaPlant(x, y, HORIZONTAL_PIRANHA_PLANT);
		else if (name == "wall") obj = new CWall(x, y, width, height);
		else if (name == "ground") obj = new CGround(x, y, width, height);
		else if (name == "s_platform") obj = new CSpecificPlatform(x, y, width, height);
		else if (name == "coin") obj = new CCoin(x, y, width, height);
		else if (name == "brick") obj = new CBrick(x, y, width, height, BRICK_STATE_NORMAL);
		else if (name == "q_brick" || name == "s_brick" || name == "secret_brick")
		{
			string drop = "";
			int item = -1;
			tinyxml2::XMLElement* pProperty = pObject->FirstChildElement("properties")->FirstChildElement("property");
			if (pProperty != nullptr)
			{
				drop = pProperty->Attribute("name");
				if (drop == "drop")
				{
					drop = pProperty->Attribute("value");
					if (drop == "coin") item = DCOIN;
					else if (drop == "multi_coin") item = MCOIN;
					else if (drop == "red_mushroom") item = RMUSHROOM;
					else if (drop == "green_mushroom") item = GMUSHROOM;
					else if (drop == "pause") item = PAUSE;
					else DebugOut(L"[ERROR] Invalid item: %s\n", ToLPCWSTR(drop));
				}
			}
			if (name == "q_brick") obj = new CBrick(x, y, width, height, BRICK_STATE_QBRICK, item);
			else if (name == "s_brick") obj = new CBrick(x, y, width, height, BRICK_STATE_NORMAL, item);
			else if (name == "secret_brick") obj = new CBrick(x, y, width, height, BRICK_STATE_SECRET, item);
		}
		else if (name == "pipe") obj = new CPipe(x, y, width, height);
		else if (name == "position") {}
		else if (name == "portal")
		{
			int sceneId = -1;
			tinyxml2::XMLElement* pProperty = pObject->FirstChildElement("properties")->FirstChildElement("property");
			if (pProperty != nullptr)
			{
				string name = pProperty->Attribute("name");
				if (name == "scene") pProperty->QueryIntAttribute("value", &sceneId);
				else DebugOut(L"[ERROR] Invalid property: %s\n", ToLPCWSTR(name));
			}
			obj = new CPortal(x, y, width, height, sceneId);
		}
		else if (name == "dead_zone") obj = new CDeadzone(x, y, width, height);
		else DebugOut(L"[ERROR] Invalid object: %s\n", ToLPCWSTR(name));

		// General object setup
		DebugOut(L"[INFO] object %s has been created!\n", ToLPCWSTR(name));
		obj->SetPosition(x, y);
		if (obj->IsEnemies())
		{
			obj->EnemiesOutScreen();
			enemies.push_back(obj);
		}
		else
		{
			objects.push_back(obj);
		}
		pObject = pObject->NextSiblingElement("object");
	}

	DebugOut(L"[INFO] Done loading map from %s\n", ToLPCWSTR(mapFile));
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", ToLPCWSTR(sceneFilePath));

	tinyxml2::XMLDocument doc;
	doc.LoadFile(sceneFilePath.c_str());
	tinyxml2::XMLElement* pScene = doc.FirstChildElement("scene");
	if (pScene == nullptr)
	{
		DebugOut(L"[ERROR] Failed to loading scene file : %s\n", ToLPCWSTR(sceneFilePath));
		return;
	}

	//Load Setting
	tinyxml2::XMLElement* pSetting = pScene->FirstChildElement("settings")->FirstChildElement("setting");
	if (pSetting != nullptr)
	{
		//get extra setting of scene
		pSetting = pSetting->NextSiblingElement("setting");
	}

	//Load Asset
	tinyxml2::XMLElement* pAssetGroup = pScene->FirstChildElement("assetgroup");
	tinyxml2::XMLElement* pAsset = pAssetGroup->FirstChildElement("asset");
	while (pAsset != nullptr)
	{
		string path = pAsset->Attribute("source");
		LoadAssets(path);
		pAsset = pAsset->NextSiblingElement("asset");
	}

	//Load Map
	tinyxml2::XMLElement* pMap = pScene->FirstChildElement("map");
	{
		string path = pMap->Attribute("source");
		LoadMap(path);
	}

	//load other
	LPGAME game = CGame::GetInstance();
	if (!game->IsMarioGoThroughPipe()) //start time when new map,
	{
		game->StartTime();
	}

	if (game->IsOnPause() && GetTickCount64() - game->GetStartPause() <= CGameSetting::GetInstance()->pause_timeout)
	{
		game->SetIsOnPause(true);
		SwitchCoinAndBrick();
	}

	DebugOut(L"[INFO] Done loading scene : %s\n", ToLPCWSTR(sceneFilePath));
}

void CPlayScene::Update(DWORD dt)
{
	CGame* game = CGame::GetInstance();
	CGameSetting* setting = CGameSetting::GetInstance();
	//Handle Spaw Enemies
	CGameObject* enemy = NULL;
	float l_screen, t_screen, r_screen, b_screen;
	game->GetCam(l_screen, t_screen, r_screen, b_screen);
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsInCamera(l_screen - 16, t_screen - 16, r_screen + 16, b_screen + 16))
		{
			if (enemies[i]->IsEnemiesOutScreen())
			{
				float x, y;
				enemies[i]->GetInitPosition(x, y);
				int type = enemies[i]->GetType();
				if (type == GOOMBA || type == WGOOMBA || type == RGOOMBA || type == RWGOOMBA)
				{
					enemy = new CGoomba(x, y, type);
				}
				else if (type == KOOPA || type == WKOOPA || type == RKOOPA || type == RWKOOPA)
				{
					enemy = new CKoopa(x, y, type);
				}
				DebugOut(L"Add enemy in list objects\n");
				objects.push_back(enemy);
				enemies[i]->Delete();
			}
		}
		else
		{
			enemies[i]->EnemiesOutScreen();
		}
	}

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (!objects[i]->IsPlayer()) 
		{
			if (objects[i]->IsEnemies() && !objects[i]->IsInCamera(l_screen - 16, t_screen - 16, r_screen + 16, b_screen + 16))
			{
				objects[i]->Delete();
				DebugOut(L"Delete enemy out screen\n");
			}
			else coObjects.push_back(objects[i]);
		}
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	cx -= (float)game->GetBackBufferWidth() / 2;
	cy -= (float)game->GetBackBufferHeight() / 4;

	int w, h, l, t, r, b; //left, top, right, bottom of map
	map->GetWidthHeight(w, h);
	l = 0;
	t = 0;
	r = w - game->GetBackBufferWidth();
	b = h - game->GetBackBufferHeight() + hud->GetHeight();
	
	if (cx < l) cx = (float)l;
	if (cx > r) cx = (float)r;
	if (cy > b) cy = (float)b;
	if (cy < t) cy = (float)t;
	
	CGame::GetInstance()->SetCamPos(cx, cy);

	//update other
	if (!game->IsOnPause() && GetTickCount64() - game->GetStartPause() <= setting->pause_timeout)
	{
		game->SetIsOnPause(true);
		SwitchCoinAndBrick();
	}
	else if (game->IsOnPause() && GetTickCount64() - game->GetStartPause() > setting->pause_timeout)
	{
		game->SetIsOnPause(false);
		SwitchCoinAndBrick();
	}
	game->UpdateTime();
	if (game->GetTime() <= 0)
	{
		DebugOut(L"Time Out, mario die.\n");
		CMario* mario = (CMario*)player;
		mario->Dead();
		game->StartTime();
	}
	hud->Update();
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	float cx, cy, screen_cx, screen_cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame* game = CGame::GetInstance();
	screen_cx = cx + (float)game->GetBackBufferWidth();
	screen_cy = cy + (float)game->GetBackBufferHeight();
	int left, top, right, bottom, tileWidth, tileHeight, width, height;
	map->GetTileWidthHeight(tileWidth, tileHeight);
	map->GetNumberTileWidthHeight(width, height);
	left = (int)cx / tileWidth;
	right = (int)screen_cx / tileWidth + 1;
	top = (int)cy / tileHeight;
	bottom = (int)screen_cy / tileHeight + 1;
	if (right >= width) right = width;
	if (bottom >= height) bottom = height;
	for (int id = 1; id < map->GetNextLayerId(); id++)
	{
		if (id == layerObject)
		{
			for (int i = 0; i < objects.size(); i++) //render objects
			{
				objects[i]->Render();
			}
		}
		else map->Render(left, top, right, bottom, id); //render tiled-map
	}
	hud->Render();
}

void CPlayScene::AddObject(LPGAMEOBJECT o)
{
	objects.insert(objects.begin(), o);
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it_obj;
	for (it_obj = objects.begin(); it_obj != objects.end(); it_obj++)
	{
		delete (*it_obj);
	}
	objects.clear();
	vector<LPGAMEOBJECT>::iterator it_enemies;
	for (it_enemies = enemies.begin(); it_enemies != enemies.end(); it_enemies++)
	{
		delete (*it_enemies);
	}
	enemies.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	objects.clear();

	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	enemies.clear();

	player = NULL;
	map = NULL;
	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	CGameObject* enemy = NULL;
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			if (o->IsEnemies()) // check if enemy is delete will be stored to create 
			{
				float x, y;
				o->GetInitPosition(x, y);
				int type = o->GetType();
				if (type == GOOMBA || type == WGOOMBA || type == RGOOMBA || type == RWGOOMBA)
				{
					enemy = new CGoomba(x, y, type);
				}
				else if (type == KOOPA || type == WKOOPA || type == RKOOPA || type == RWKOOPA)
				{
					enemy = new CKoopa(x, y, type);
				}
				DebugOut(L"Add enemy in list enemies\n");
				enemies.push_back(enemy);
			}
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());

	//purge deleted enemies
	vector<LPGAMEOBJECT>::iterator it_enemy;
	for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
	{
		LPGAMEOBJECT o = *it_enemy;
		if (o->IsDeleted())
		{
			delete o;
			*it_enemy = NULL;
		}
	}
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(), CPlayScene::IsGameObjectDeleted),
		enemies.end());
}

void CPlayScene::SwitchCoinAndBrick()
{
	CGameObject* obj = NULL;
	float x_obj, y_obj;
	vector<LPGAMEOBJECT> objects_temp;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetType() == BRICK && ((CBrick*)objects[i])->IsNoItem())
		{
			objects[i]->GetPosition(x_obj, y_obj);
			objects[i]->Delete();
			obj = new CCoin(x_obj, y_obj, 16, 16);
			obj->SetPosition(x_obj, y_obj);
			objects_temp.push_back(obj);
		}
		else if (objects[i]->GetType() == COIN)
		{
			objects[i]->GetPosition(x_obj, y_obj);
			objects[i]->Delete();
			obj = new CBrick(x_obj, y_obj, 16, 16, BRICK_STATE_NORMAL);
			obj->SetPosition(x_obj, y_obj);
			objects_temp.push_back(obj);
		}
	}
	for (size_t i = 0; i < objects_temp.size(); i++)
	{
		objects.push_back(objects_temp[i]);
	}
}
