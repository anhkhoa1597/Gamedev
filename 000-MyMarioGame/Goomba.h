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

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f

#define GOOMBA_WING_GRAVITY 0.0005f
#define GOOMBA_WING_LOW_JUMP 0.1f
#define GOOMBA_WING_HIGH_JUMP 0.2f
#define GOOMBA_BOUNCING_SPEED 0.5f
#define GOOMBA_WIDTH 16

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_BOUNCE_DIE_TIMEOUT 3000
#define GOOMBA_WALK_TIME_TO_JUMP 500

#define ID_ANI_GOOMBA_WALKING 5100
#define ID_ANI_GOOMBA_DIE 5190
#define ID_ANI_GOOMBA_BOUNCE_DIE 5191

#define ID_ANI_RED_GOOMBA_WALKING 5200
#define ID_ANI_RED_GOOMBA_DIE 5290
#define ID_ANI_RED_GOOMBA_BOUNCE_DIE 5291

#define ID_ANI_WING_JUMP 5300
#define ID_ANI_WING_WALK 5301

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
	void LostWing() { has_wing = false; SetState(GOOMBA_STATE_WALKING); ay = GOOMBA_GRAVITY; }
	void ChangeDir() { nx = -nx; vx = nx * vx; }
	virtual void SetState(int state);
};