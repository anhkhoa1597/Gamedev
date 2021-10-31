#pragma once
#include "GameObject.h"

enum GoombaStates
{
	GOOMBA_STATE_WALKING,
	GOOMBA_STATE_DIE,
};

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f

#define GOOMBA_WING_GRAVITY 0.0015f
#define GOOMBA_WING_JUMP 0.4f

#define GOOMBA_WIDTH 16

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define ID_ANI_GOOMBA_WALKING 5100
#define ID_ANI_GOOMBA_DIE 5199

#define ID_ANI_RED_GOOMBA_WALKING 5200
#define ID_ANI_RED_GOOMBA_DIE 5299

#define ID_ANI_WING_LEFT 5300
#define ID_ANI_WING_RIGHT 5301

#define WING_WIDTH 8

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	bool has_wing;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual bool HasWing() { return has_wing; }
	virtual void LostWing() { has_wing = false; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public: 	
	CGoomba(float x, float y, int type, bool has_wing = false);
	virtual void SetState(int state);
};