#pragma once

#include "GameObject.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

class CCoin : public CGameObject {
	int width;
	int height;
public:
	CCoin(float x, float y, int width, int height) : CGameObject(x, y) { this->width = width; this->height = height; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};