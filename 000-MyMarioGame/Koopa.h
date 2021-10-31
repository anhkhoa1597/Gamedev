#pragma once
#include "GameObject.h"

enum KoopaStates
{
	KOOPA_STATE_WALKING,
	KOOPA_STATE_DIE,
};

#define KOOPA_GRAVITY 0.002f
#define KOOP_WALKING_SPEED 0.05f

#define KOOPA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define ID_ANI_GOOMBA_WALKING 5100
#define ID_ANI_GOOMBA_DIE 5999

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoomba(float x, float y);
	virtual void SetState(int state);
};