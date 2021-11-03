#pragma once

#include "GameObject.h"
#include "Animations.h"
#include "Mario.h"
#include "PlayScene.h"

class CCoin : public CGameObject {
	int width;
	int height;
public:
	CCoin(float x, float y, int width, int height) : CGameObject(x, y, COIN) { this->width = width; this->height = height; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};



class CDropCoin : public CCoin {
	float initial_y;
public:
	CDropCoin(float x, float y, int width, int height);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};