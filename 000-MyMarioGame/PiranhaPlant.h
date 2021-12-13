#pragma once
#include "GameObject.h"
#include "PlayScene.h"

enum PiranhaPlantStates
{
	PIRANHA_PLANT_STATE_IDLE,
	PIRANHA_PLANT_STATE_GO_UP,
	PIRANHA_PLANT_STATE_GO_DOWN,
};

class CPiranhaPlant : public CGameObject
{
	int nx; //nx < 0: left, nx > 0: right
	int ny; //ny < 0: up, ny > 0: down;
	ULONGLONG delay_start;
public:
	CPiranhaPlant(float x, float y, int type);
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual int IsBlocking() { return 0; }
	bool IsMarioInZoneToPlantUp(float x_mario);
};