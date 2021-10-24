#pragma once
#include "Ground.h"

class SPlatform : public Ground {
public:
	SPlatform(float x, float y, float width, float height) : Ground(x, y, width, height) {}

	void Update(DWORD dt) {}

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) { l = 0; t = 1; r = 0; b = 0; }
};