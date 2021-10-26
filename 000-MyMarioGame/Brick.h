#pragma once

#include "GameObject.h"
#include "Animations.h"
#include "Utils.h"
#include "DCoin.h"

#define ID_ANI_BRICK 10100
#define ID_ANI_QBRICK 10200
#define ID_ANI_BBRICK 10300

#define BRICK_STATE_NORMAL 100
#define BRICK_STATE_QBRICK 200
#define BRICK_STATE_BBRICK 300
#define BRICK_STATE_BOUNCE 400
#define BRICK_STATE_BREAK 500
#define BRICK_STATE_SECRET 600

#define BRICK_BOUNCING_SPEED 0.2f
#define BRICK_BOUNCE_HEIGHT 12

#define NUMBER_OF_BOUNCE 10

class CBrick : public CGameObject {
protected:
	int width;
	int height; 
	string item;
	float initial_y;
	int timesLeftToBounce;

public:
	CBrick(float x, float y, int width, int height, int state, string item = "");
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Get(float& x, float& y, int& width, int& height);
	virtual int GetTimesLeftToBounce() { return timesLeftToBounce; }
	virtual bool IsNoItem() { return item == ""; }
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	bool IsSecret() { return state == BRICK_STATE_SECRET; }
	void DirectBlocking(int& l, int& t, int& r, int& b) { l = !IsSecret(); t = !IsSecret(); r = !IsSecret(); b = 1; }

};