#pragma once

#include "GameObject.h"
#include "Animations.h"

#define ID_ANI_COIN 11100

class CCoin : public CGameObject {
	int width;
	int height;
public:
	CCoin(float x, float y, int width, int height) : CGameObject(x, y, COIN) { this->width = width; this->height = height; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};