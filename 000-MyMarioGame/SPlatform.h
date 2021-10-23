#pragma once
#include "Ground.h"

class SPlatform : public Ground {
	//BOOLEAN isMarioOnTop;
public:
	SPlatform(float x, float y, float width, float height) : Ground(x, y, width, height) {/* isMarioOnTop = false; */}
	void Update(DWORD dt) {}
	//void SetBlocking(BOOLEAN isBlock) { this->isMarioOnTop = isBlock; }

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	virtual int IsBlockingFromTop() { return 1; }
	virtual int IsBlockingFromLeft() { return 0; }
	virtual int IsBlockingFromRight() { return 0; }
	virtual int IsBlockingFromBottom() { return 0; }
};