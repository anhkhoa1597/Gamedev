#include "Brick.h"

CBrick::CBrick(float x, float y, int width, int height, int state, string item) : CGameObject(x, y)
{
	this->width = width; 
	this->height = height;
	this->item = item;
	initial_y = y;
	if (item == "multi_coin") timesLeftToBounce = NUMBER_OF_BOUNCE;
	else timesLeftToBounce = 1;
	SetState(state);
}

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = ID_ANI_BRICK;
	if (state == BRICK_STATE_QBRICK) aniId = ID_ANI_QBRICK;
	else if (state == BRICK_STATE_BBRICK) aniId = ID_ANI_BBRICK;
	else if (state == BRICK_STATE_BREAK) aniId = ID_ANI_BBRICK; //need ani break brick
	else if (state == BRICK_STATE_SECRET) return;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y <= initial_y - BRICK_BOUNCE_HEIGHT)
	{
		y = initial_y - BRICK_BOUNCE_HEIGHT;
		vy = BRICK_BOUNCING_SPEED;
	}
	if (y > initial_y)
	{
		y = initial_y;
		vy = 0;
		CGameObject* object = NULL;
		float x, y;
		int width, height;
		Get(x, y, width, height);
		if (item == "coin") { object = new DCoin(x, y, width, height); }
		else if (item == "red_mushroom") { object = new Mushroom(x, y, width, height, MUSHROOM_TYPE_RED); }
		else if (item == "green_mushroom") { object = new Mushroom(x, y, width, height, MUSHROOM_TYPE_GREEN); }
		else if (item == "multi_coin") { object = new DCoin(x, y, width, height); }
		else if (item == "") { return; }
		else
		{
			DebugOut(L"Item %s doesnt exist. \n", ToLPCWSTR(item));
			return;
		}
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(object);
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
	switch (state)
	{
	case BRICK_STATE_NORMAL:
		break;
	case BRICK_STATE_QBRICK:
		break;
	case BRICK_STATE_SECRET:
		break;
	case BRICK_STATE_BBRICK: case BRICK_STATE_BOUNCE:
		vy = -BRICK_BOUNCING_SPEED;
		timesLeftToBounce--;
		break;
	case BRICK_STATE_BREAK:
		break;
	}

	CGameObject::SetState(state);
}