#pragma once
#include "GameObject.h"
#include "Mushroom.h"

enum GoombaStates
{
	GOOMBA_STATE_WALKING_LEFT,
	GOOMBA_STATE_WALKING_RIGHT,
	GOOMBA_STATE_LOW_JUMP,
	GOOMBA_STATE_HIGH_JUMP,
	GOOMBA_STATE_BOUNCE_DIE,
	GOOMBA_STATE_DIE,
};

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	bool has_wing;

	ULONGLONG die_start;

	ULONGLONG walk_start;
	int numberOfLowJump;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != GOOMBA_STATE_BOUNCE_DIE); };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithDeadzone(LPCOLLISIONEVENT e);
public: 	
	CGoomba(float x, float y, int type, bool has_wing = false);

	bool HasWing() { return has_wing; }
	void LostWing();
	virtual void SetState(int state);
};