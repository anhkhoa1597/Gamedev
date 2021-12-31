#pragma once
#include "GameObject.h"
#include "Koopa.h"
#include "Goomba.h"
#include "PiranhaPlant.h"

enum TailStates
{
	TAIL_STATE_ATTACK_LEFT,
	TAIL_STATE_ATTACK_RIGHT,
};

class CTail : public CGameObject {
	int width;
	int height;

	virtual void Render() { RenderBoundingBox(); }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
public:
	CTail(float x, float y, int width, int height);
	void SetState(int state);
};