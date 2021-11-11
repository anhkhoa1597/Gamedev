#pragma once

#include "GameObject.h"

class CPipe : public CGameObject {
	int width;
	int height;
	bool isBlockingMario;
public:
	CPipe(float x, float y, int width, int height);
	virtual void Render() {} ;
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetNoBlocking();
	void SetBlocking();
	void GetZoneToGoThrough(float& left, float& right);
	void ObjectNoBlocking(vector<unsigned int>& type);
	int IsBlocking();
};