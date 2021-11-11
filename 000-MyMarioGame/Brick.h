#pragma once

#include "GameObject.h"
#include "Animations.h"
#include "Coin.h"
#include "Pause.h"
#include "Utils.h"

enum BrickStates
{
	BRICK_STATE_NORMAL,
	BRICK_STATE_QBRICK,
	BRICK_STATE_BBRICK,
	BRICK_STATE_BOUNCE,
	BRICK_STATE_BREAK,
	BRICK_STATE_SECRET,
};

class CBrick : public CGameObject {
protected:
	int width;
	int height; 
	int item;
	float initial_y;
	int timesLeftToBounce;
public:
	CBrick(float x, float y, int width, int height, int state, int item = -1);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Get(float& x, float& y, int& width, int& height);
	virtual int GetTimesLeftToBounce() { return timesLeftToBounce; }
	virtual void SetUpTimesLeftToBounce() { timesLeftToBounce++; }
	virtual bool IsNoItem() { return item == -1; }

	int IsCollidable() { return 1; };
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	bool IsSecret() { return state == BRICK_STATE_SECRET; }
	void DirectBlocking(int& l, int& t, int& r, int& b) { l = !IsSecret(); t = !IsSecret(); r = !IsSecret(); b = 1; }
};