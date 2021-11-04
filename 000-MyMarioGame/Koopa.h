#pragma once
#include "GameObject.h"
#include "Mushroom.h"
#include "Goomba.h"

enum KoopaStates
{
	KOOPA_STATE_WALKING,
	KOOPA_STATE_WALKING_LEFT,
	KOOPA_STATE_WALKING_RIGHT,
	KOOPA_STATE_JUMPING,
	KOOPA_STATE_BOUNCE,
	KOOPA_STATE_SHIELD_UP_IDLE,
	KOOPA_STATE_SHIELD_DOWN_IDLE,
	KOOPA_STATE_SHIELD_ROLLING,
	KOOPA_STATE_DIE,
	KOOPA_STATE_BOUNCE_DIE,
};

#define KOOPA_WIDTH 16

#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
//#define GOOMBA_BBOX_HEIGHT_DIE 7

//#define WING_WIDTH 8

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	bool has_wing;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != KOOPA_STATE_DIE); };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CKoopa(float x, float y, int type, bool has_wing = false);

	bool HasWing() { return has_wing; }
	void LostWing();
	void ChangeDir();
	virtual void SetState(int state);
};