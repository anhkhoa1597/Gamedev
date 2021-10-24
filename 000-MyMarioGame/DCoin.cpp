#include "DCoin.h"

void DCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y <= initialPositionY - COIN_BOUNCE_HEIGHT)
	{
		y = initialPositionY - COIN_BOUNCE_HEIGHT;
		vy = COIN_BOUNCING_SPEED;
	}
	if (y > initialPositionY - COIN_BOUNCE_HEIGHT / 2)
	{
		isDeleted = false;
	}
}

void DCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_DCOIN)->Render(x, y);
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