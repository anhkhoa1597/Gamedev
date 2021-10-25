#pragma once

#include "Mario.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Animations.h"

#define ID_ANI_DCOIN 12000

#define COIN_BOUNCING_SPEED 0.15f
#define COIN_BOUNCE_HEIGHT 64
#define COIN_BOUNCE_DROP 8

#define COIN_STATE_DROP 100
class DCoin : public CGameObject {
	float initialPositionY;
	int width;
	int height;
public:
	DCoin(float x, float y, int width, int height) : CGameObject(x, y) { this->width = width; this->height = height; this->initialPositionY = y; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};