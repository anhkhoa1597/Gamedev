#include "DCoin.h"

CDCoin::CDCoin(float x, float y, int width, int height) : CCoin(x, y, width, height) 
{ 
	initial_y = y;
	vy = -COIN_BOUNCING_SPEED;
}

void CDCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsDeleted())
	{
		y += vy * dt;
		if (y <= initial_y - COIN_BOUNCE_HEIGHT)
		{
			y = initial_y - COIN_BOUNCE_HEIGHT;
			vy = COIN_BOUNCING_SPEED;
		}
		if (vy > 0 && y > initial_y - COIN_BOUNCE_DROP)
		{
			isDeleted = true;
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			mario->IncreaseCoin();
			return;
		}
	}
}

void CDCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_DCOIN)->Render(x, y);
}