#include "Mushroom.h"

Mushroom::Mushroom(float x, float y, int width, int height, int type) : CGameObject(x, y, type)
{
	vy = 0;
	vx = 0;
	ax = 0;
	ay = 0;
	this->width = width;
	this->height = height;
	this->initialPositionY = y;
	isColliable = true;
	SetState(MUSHROOM_STATE_DROP);
}

void Mushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width - 1;
	bottom = top + height - 1;
}

void Mushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Mushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<Mushroom*>(e->obj)) return;
	if (dynamic_cast<Wall*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeleted)
	{
		vy += ay * dt;
		vx += ax * dt;

		if (y <= initialPositionY - height && state == MUSHROOM_STATE_DROP)
		{
			y = initialPositionY - (height);
			ay = MUSHROOM_GRAVITY;
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			float x_mario, y_mario;
			mario->GetPosition(x_mario, y_mario);
			if (x < x_mario) vx = -MUSHROOM_SPEED;
			else vx = MUSHROOM_SPEED;
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}

void Mushroom::Render()
{
	if (!isDeleted)
	{
		int aniId = -1;
		if (type == RMUSHROOM)
		{
			aniId = ID_ANI_RED_MUSHROOM;
		}
		else if (type == GMUSHROOM)
		{
			aniId = ID_ANI_GREEN_MUSHROOM;
		}
		else DebugOut(L"[ERROR] animation %d doesnt exist\n", aniId);
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
}

void Mushroom::SetState(int state)
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
		vy = -MUSHROOM_SPEED;
		break;
	case MUSHROOM_STATE_BOUNCING_LEFT:
		vy = -MUSHROOM_BOUNCING_SPEED;
		vx = -MUSHROOM_SPEED;
		break;
	case MUSHROOM_STATE_BOUNCING_RIGHT:
		vy = -MUSHROOM_BOUNCING_SPEED;
		vx = MUSHROOM_SPEED;
		break;
	}
}
