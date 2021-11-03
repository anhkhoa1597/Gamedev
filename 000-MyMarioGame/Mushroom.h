#pragma once
#include "GameObject.h"
#include "Goomba.h"
#include "Mario.h"
#include "Ground.h"

enum MushroomStates
{
	MUSHROOM_STATE_IDLE,
	MUSHROOM_STATE_DROP,
	MUSHROOM_STATE_BOUNCING_LEFT,
	MUSHROOM_STATE_BOUNCING_RIGHT,
};

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	int width;
	int height;
	float initialPositionY;
	bool isColliable;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return isColliable; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y, int width, int height, int type);
	int GetType() { return type; }
	void SetState(int state);
};