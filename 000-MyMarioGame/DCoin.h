#pragma once

#include "Mario.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Animations.h"

#define ID_ANI_DCOIN 12000

#define COIN_BOUNCING_SPEED 0.25f
#define COIN_BOUNCE_HEIGHT 48
#define COIN_BOUNCE_DROP 8

class DCoin : public CCoin {
	float initial_y;
public:
	DCoin(float x, float y, int width, int height);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};