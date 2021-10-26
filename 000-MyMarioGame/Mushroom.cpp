#include "Mushroom.h"

Mushroom::Mushroom(float x, float y, int width, int height, int type) : CGameObject(x, y)
{
	vy = 0;
	vx = 0;
	ax = 0;
	ay = 0;
	this->width = width;
	this->height = height;
	this->type = type;
	this->initialPositionY = y;
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

		if (y <= initialPositionY - 16 && state == MUSHROOM_STATE_DROP)
		{
			y = initialPositionY - 16;
			ay = MUSHROOM_GRAVITY;
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			float x_mario, y_mario;
			mario->GetPosition(x_mario, y_mario);
			if (x < x_mario) vx = -MUSHROOM_SPEED;
			else vx = MUSHROOM_SPEED;
		}
		if (state == MUSHROOM_STATE_BOUNCING && vx != 0) //vx != 0 to separate idle mushroom and moving mushroom
		{
			//logic game
		}

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}

void Mushroom::Render()
{
	if (!isDeleted)
	{
		int aniId = -1;
		if (type == MUSHROOM_TYPE_RED)
		{
			aniId = ID_ANI_RED_MUSHROOM;
		}
		else if (type == MUSHROOM_TYPE_GREEN)
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
	case MUSHROOM_STATE_BOUNCING:
		vy = -MUSHROOM_BOUNCING_SPEED;
	}
}
