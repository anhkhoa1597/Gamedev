#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CDeadzone : public CGameObject
{
	int width;
	int height;
public:
	CDeadzone(float x, float y, int width, int height) : CGameObject(x, y, DEADZONE) { this->width = width; this->height = height; }
	virtual void Render() {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};