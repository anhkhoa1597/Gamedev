#include "DCoin.h"

void DCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y <= initialPositionY - COIN_BOUNCE_HEIGHT)
	{
		y = initialPositionY - COIN_BOUNCE_HEIGHT;
		vy = COIN_BOUNCING_SPEED;
	}
	if (vy > 0 && y > initialPositionY - COIN_BOUNCE_DROP)
	{
		isDeleted = true;
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->IncreaseCoin();
	}
}

void DCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_DCOIN)->Render(x, y);
}

void DCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}

void DCoin::SetState(int state)
{
	switch (state)
	{
	case COIN_STATE_DROP:
		vy = -COIN_BOUNCING_SPEED;
		break;
	}
	CGameObject::SetState(state);
}