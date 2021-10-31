#pragma once

#include "GameObject.h"

class CPipes : public CGameObject {
	int width;
	int height;
public:
	CPipes(float x, float y, int width, int height) : CGameObject(x, y, PIPE) { this->width = width; this->height = height; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};