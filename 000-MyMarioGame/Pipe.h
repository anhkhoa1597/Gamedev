#pragma once

#include "GameObject.h"

class CPipe : public CGameObject {
	int width;
	int height;
	bool isBlockingMario;
public:
	CPipe(float x, float y, int width, int height) : CGameObject(x, y, PIPE) { this->width = width; this->height = height; isBlockingMario = true; }
	virtual void Render() {} ;
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetNoBlocking() { isBlockingMario = false; }
	void SetBlocking() { isBlockingMario = true; }
	void GetZoneToGoThrough(float& left, float& right) { left = x + setting->pipe_adjust_width_can_go_through; right = left + width - 2*(setting->pipe_adjust_width_can_go_through); };
	void ObjectNoBlocking(vector<unsigned int>& type) { isBlockingMario ? type = {} : type = { MARIO }; }
	int IsBlocking() { return true; }
};