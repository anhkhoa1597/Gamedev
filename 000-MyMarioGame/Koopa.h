 #pragma once
#include "GameObject.h"
#include "Mushroom.h"
#include "Goomba.h"
#include "Brick.h"

enum KoopaStates
{
	KOOPA_STATE_WALKING_LEFT,
	KOOPA_STATE_WALKING_RIGHT,
	KOOPA_STATE_JUMPING,

	KOOPA_STATE_SHIELD_IDLE,
	KOOPA_STATE_SHIELD_ROLLING_LEFT,
	KOOPA_STATE_SHIELD_ROLLING_RIGHT,
	KOOPA_STATE_SHIELD_STANDING,

	KOOPA_STATE_BOUNCE_LEFT,
	KOOPA_STATE_BOUNCE_RIGHT,
	KOOPA_STATE_BOUNCE_DIE,
	//KOOPA_STATE_DIE,
};

enum ShieldTypes
{
	NO_SHIELD,
	SHIELD_DOWN,
	SHIELD_UP,
};

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	bool has_wing;

	ULONGLONG die_start;
	ULONGLONG shield_start;
	ULONGLONG standing_start;
	
	int type_shield;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != KOOPA_STATE_BOUNCE_DIE); };
	virtual int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, int type, bool has_wing = false);

	bool HasWing() { return has_wing; }
	void LostWing();
	virtual void SetState(int state);
	int GetTypeShield() { return type_shield; }
	void SetTypeShield(int typeShield) { this->type_shield = typeShield; }
};