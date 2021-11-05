#include "Brick.h"

CBrick::CBrick(float x, float y, int width, int height, int state, int item) : CGameObject(x, y, BRICK)
{
	this->width = width; 
	this->height = height;
	this->item = item;
	initial_y = y;
	if (item == MCOIN) timesLeftToBounce = setting->brick_number_bounce_of_multi_coin;
	else timesLeftToBounce = 1;
	SetState(state);
}

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = setting->id_ani_brick;
	if (state == BRICK_STATE_QBRICK) aniId = setting->id_ani_question_brick;
	else if (state == BRICK_STATE_BBRICK) aniId = setting->id_ani_block_brick;
	else if (state == BRICK_STATE_BREAK) aniId = setting->id_ani_block_brick; //need ani break brick
	else if (state == BRICK_STATE_SECRET) return;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);

	y += vy * dt;
	if (y <= initial_y - setting->brick_bounce_height)
	{
		//y = initial_y - BRICK_BOUNCE_HEIGHT;
		vy = setting->brick_bouncing_speed;
		if (timesLeftToBounce == 0) SetState(BRICK_STATE_BBRICK);
		else SetState(BRICK_STATE_NORMAL);
	}
	if (y > initial_y)
	{
		y = initial_y;
		vy = 0;
		CGameObject* object = NULL;
		float x, y;
		int width, height;
		Get(x, y, width, height);
		if (item == DCOIN) { object = new CDropCoin(x, y, width, height); }
		else if (item == RMUSHROOM) { object = new CMushroom(x, y, width, height, RMUSHROOM); }
		else if (item == GMUSHROOM) { object = new CMushroom(x, y, width, height, GMUSHROOM); }
		else if (item == MCOIN) { object = new CDropCoin(x, y, width, height); }
		else if (item == -1) { return; }
		else
		{
			DebugOut(L"[ERROR] Item %d doesn't exist. \n", item);
			return;
		}
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(object);
	}
}

void CBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
}

void CBrick::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	float x_mushroom, y_mushroom;
	mushroom->GetPosition(x_mushroom, y_mushroom);
	if (e->ny > 0)
	{
		if (state == BRICK_STATE_BOUNCE)
		{
			if (x_mushroom < x) mushroom->SetState(MUSHROOM_STATE_BOUNCING_LEFT);
			else mushroom->SetState(MUSHROOM_STATE_BOUNCING_RIGHT);
		}
	}
}

void CBrick::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (e->ny > 0)
	{
		if (state == BRICK_STATE_BOUNCE)
		{
			float x_goomba, y_goomba;
			goomba->GetPosition(x_goomba, y_goomba);
			goomba->LostWing();
			if (x_goomba < x) goomba->SetSpeed(-setting->brick_bouncing_speed, 0);
			else  goomba->SetSpeed(setting->brick_bouncing_speed, 0);
			goomba->SetState(GOOMBA_STATE_BOUNCE_DIE);
		}
	}
}

void CBrick::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (e->ny > 0)
	{
		if (state == BRICK_STATE_BOUNCE)
		{
			if (koopa->HasWing()) koopa->LostWing();
			else
			{
				float x_koopa, y_koopa;
				koopa->GetPosition(x_koopa, y_koopa);
				koopa->LostWing();
				koopa->SetTypeShield(SHIELD_UP);
				if (x_koopa > x) koopa->SetState(KOOPA_STATE_BOUNCE_RIGHT);
				else koopa->SetState(KOOPA_STATE_BOUNCE_LEFT);
			}
				
		}
	}
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}

void CBrick::Get(float& x, float& y, int& width, int& height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BRICK_STATE_NORMAL:
		//type = BRICK;
		break;
	case BRICK_STATE_QBRICK:
		//type = QBRICK;
		break;
	case BRICK_STATE_SECRET:
		//type = SECRET_BRICK;
		break;
	case BRICK_STATE_BBRICK:
		//type = BBRICK;
		break;
	case BRICK_STATE_BOUNCE:
		vy = -setting->brick_bouncing_speed;
		timesLeftToBounce--;
		break;
	case BRICK_STATE_BREAK:
		isDeleted = true;
		break;
	}

}