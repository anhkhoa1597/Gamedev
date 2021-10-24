#pragma once

#include "Coin.h"
#include "Animations.h"

#define ID_ANI_DCOIN 12000

#define COIN_BOUNCING_SPEED 0.4f
#define COIN_BOUNCE_HEIGHT 80

#define COIN_STATE_DROP 100
class DCoin : public CCoin {
	float initialPositionY;
public:
	DCoin(float x, float y, int width, int height) : CCoin(x, y, width, height) { this->initialPositionY = y; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	//int IsBlocking() { return 1; }

};