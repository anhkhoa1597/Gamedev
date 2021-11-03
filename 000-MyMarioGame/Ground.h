#pragma once
#include "GameObject.h"

class CGround : public CGameObject {
	int width;
	int height;
public:
	CGround(float x, float y, int width, int height) : CGameObject(x, y, GROUND) { this->width = width; this->height = height; }
	virtual void Render() {}
	virtual void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CSpecificPlatform : public CGround {
public:
	CSpecificPlatform(float x, float y, int width, int height) : CGround(x, y, width, height) { type = SPLATFORM; }

	void Update(DWORD dt) {}

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) { l = 0; t = 1; r = 0; b = 0; }
};

class CWall : public CGround {
public:
	CWall(float x, float y, int width, int height) : CGround(x, y, width, height) { type = WALL; }
	void Render() {}
	void Update(DWORD dt) {}
	void ObjectNoBlocking(vector<unsigned int>& type) { type = { GMUSHROOM, RMUSHROOM }; }
};