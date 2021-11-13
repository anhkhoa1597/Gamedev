#include "Mushroom.h"


CMushroom::CMushroom(float x, float y, int width, int height, int type) : CGameObject(x, y, type)
{
	vy = 0;
	vx = 0;
	ax = 0;
	ay = 0;
	this->width = width;
	this->height = height;
	SetState(MUSHROOM_STATE_DROP);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width - 1;
	bottom = top + height - 1;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;
	if (dynamic_cast<CWall*>(e->obj)) return;
	if (dynamic_cast<CDeadzone*>(e->obj))
		OnCollisionWithDeadzone(e);
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::OnCollisionWithDeadzone(LPCOLLISIONEVENT e)
{
	isDeleted = true;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeleted)
	{
		vy += ay * dt;
		vx += ax * dt;

		if (y <= initY - height && state == MUSHROOM_STATE_DROP)
		{
			//y = initialPositionY - (height);
			ay = setting->mushroom_gravity;
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			float x_mario, y_mario;
			mario->GetPosition(x_mario, y_mario);
			if (x < x_mario) vx = -setting->mushroom_speed;
			else vx = setting->mushroom_speed;
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}

void CMushroom::Render()
{
	if (!isDeleted)
	{
		int aniId = -1;
		if (type == RMUSHROOM)
		{
			aniId = setting->id_ani_red_mushroom;
		}
		else if (type == GMUSHROOM)
		{
			aniId = setting->id_ani_green_mushroom;
		}
		else DebugOut(L"[ERROR] animation %d doesnt exist\n", aniId);
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		vy = 0;
		vx = 0;
		ax = 0;
		ay = 0;
		break;
	case MUSHROOM_STATE_DROP:
		vx = 0;
		ax = 0;
		vy = -setting->mushroom_speed;
		break;
	case MUSHROOM_STATE_BOUNCING_LEFT:
		vy = -setting->mushroom_bouncing_speed;
		vx = -setting->mushroom_speed;
		break;
	case MUSHROOM_STATE_BOUNCING_RIGHT:
		vy = -setting->mushroom_bouncing_speed;
		vx = setting->mushroom_speed;
		break;
	}
}
