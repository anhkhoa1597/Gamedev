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
	vy = -setting->coin_bouncing_speed;
}

void CDropCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsDeleted())
	{
		y += vy * dt;
		if (y <= initY - setting->coin_bounce_height)
		{
			y = initY- setting->coin_bounce_height;
			vy = setting->coin_bouncing_speed;
		}
		if (vy > 0 && y > initY - setting->coin_drop_height)
		{
			isDeleted = true;
			CGame::GetInstance()->IncreaseCoin();
			CGame::GetInstance()->IncreasePoint(100);
			return;
		}
	}
}

void CDropCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(setting->id_ani_coin_drop)->Render(x, y);
}