#pragma once
#include "GameObject.h"
//#include "debug.h"
#include "Goomba.h"
#include "Mario.h"

enum MushroomStates
{
	MUSHROOM_STATE_IDLE,
	MUSHROOM_STATE_DROP,
	MUSHROOM_STATE_BOUNCING,
};

enum MushroomTypes
{
	MUSHROOM_TYPE_RED,
	MUSHROOM_TYPE_GREEN,
};

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_SPEED 0.04f
#define MUSHROOM_BOUNCING_SPEED 0.4f

#define ID_ANI_RED_MUSHROOM 8100
#define ID_ANI_GREEN_MUSHROOM 8200

#define MUSHROOM_LIFE_UP 1

class Mushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	int width;
	int height;
	int type;
	float initialPositionY;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
public:
	Mushroom(float x, float y, int width, int height, int type);
	int GetType() { return type; }
	void SetState(int state);
};