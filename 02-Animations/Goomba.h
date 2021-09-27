#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define GOOMBA_WIDTH 16
#define GOOMBA_START_X 8.0f
#define GOOMBA_START_Y 150.0f
#define GOOMBA_START_VX 0.01f
#define ID_GOOMBA_WALK_LEFT 520
#define ID_GOOMBA_WALK_RIGHT 521

class CGoomba : public CGameObject
{
protected:
	float vx;
	int status;
public:
	CGoomba(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};


