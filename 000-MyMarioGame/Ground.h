#pragma once
#include "GameObject.h"

class Ground : public CGameObject {
	int width;
	int height;
public:
	Ground(float x, float y, int width, int height) : CGameObject(x, y) { this->width = width; this->height = height; }
	void Render() {}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};