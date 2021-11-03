#pragma once
#include "GameObject.h"
#include "Mushroom.h"

enum GoombaStates
{
	GOOMBA_STATE_WALKING,
	GOOMBA_STATE_LOW_JUMP,
	GOOMBA_STATE_HIGH_JUMP,
	GOOMBA_STATE_BOUNCE_DIE,
	GOOMBA_STATE_DIE,
};

#define GOOMBA_WIDTH 16

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define WING_WIDTH 8

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
public: 	
	CGoomba(float x, float y, int type, bool has_wing = false);

	bool HasWing() { return has_wing; }
	void LostWing() { has_wing = false; SetState(GOOMBA_STATE_WALKING); ay = setting->goomba_gravity; }
	void ChangeDir() { nx = -nx; vx = nx * vx; }
	virtual void SetState(int state);
};