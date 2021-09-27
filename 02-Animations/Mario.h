#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define MARIO_WIDTH 14
#define MARIO_START_X 7.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f
#define ID_MARIO_ANI_WALK_RIGHT 500
#define ID_MARIO_ANI_WALK_LEFT 501
#define ID_BRICK_ANI 510

class CBrick : public CGameObject {
public: 
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CMario : public CGameObject
{
protected:
	float vx;
public:
	CMario(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};


