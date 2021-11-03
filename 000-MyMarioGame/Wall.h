#pragma once
#include "Ground.h"

class Wall : public Ground {
public:
	Wall(float x, float y, int width, int height) : Ground(x, y, width, height) { type = WALL; }
	void Render() {}
	void Update(DWORD dt) {}
	void ObjectNoBlocking(vector<unsigned int>& type) { type = {GMUSHROOM, RMUSHROOM}; }
};