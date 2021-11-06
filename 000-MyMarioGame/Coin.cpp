#include "Coin.h"


void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(setting->id_ani_coin_spinning)->Render(x, y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}

CDropCoin::CDropCoin(float x, float y, int width, int height) : CCoin(x, y, width, height)
{
	initial_y = y;
	vy = -setting->coin_bouncing_speed;
}

void CDropCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsDeleted())
	{
		y += vy * dt;
		if (y <= initial_y - setting->coin_bounce_height)
		{
			y = initial_y - setting->coin_bounce_height;
			vy = setting->coin_bouncing_speed;
		}
		if (vy > 0 && y > initial_y - setting->coin_drop_height)
		{
			isDeleted = true;
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			mario->IncreaseCoin();
			return;
		}
	}
}

void CDropCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(setting->id_ani_coin_drop)->Render(x, y);
}