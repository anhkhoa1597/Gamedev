#pragma once
#include "GameObject.h"

class Ground : public CGameObject {
	int width;
	int height;
public:
	Ground(float x, float y, int width, int height) : CGameObject(x, y, GROUND) { this->width = width; this->height = height; }
	virtual void Render() {}
	virtual void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};