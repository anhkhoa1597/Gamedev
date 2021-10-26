#include "QBrick.h"

QBrick::QBrick(float x, float y, int width, int height, string item) : CBrick(x, y, width, height)
{
	SetState(BRICK_STATE_QBRICK);
	this->initialPositionY = y;
	this->item = item;
	//this->object->SetPosition(x - 16, y - 16);
}

void QBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (y <= initialPositionY - BRICK_BOUNCE_HEIGHT)
	{
		y = initialPositionY - BRICK_BOUNCE_HEIGHT;
		vy = BRICK_BOUNCING_SPEED;
	}
	if (y > initialPositionY)
	{
		y = initialPositionY;
		vy = 0;
		CGameObject* object = NULL;
		float x, y;
		int width, height;
		Get(x, y, width, height);
		if (item == "coin") { object = new DCoin(x, y, width, height); }
		else if (item == "red_mushroom") { object = new Mushroom(x, y, width, height, MUSHROOM_TYPE_RED); }
		else if (item == "green_mushroom") { object = new Mushroom(x, y, width, height, MUSHROOM_TYPE_GREEN); }
		else
		{
			DebugOut(L"Item %s doesnt exist. \n", ToLPCWSTR(item));
			return;
		}
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(object);
	}
}

void QBrick::Render()
{
	int aniId = -1;

	if (state == BRICK_STATE_QBRICK)
		aniId = ID_ANI_QBRICK;
	else if (state == BRICK_STATE_BBRICK)
		aniId = ID_ANI_BBrick;
		

	//if(!object->IsDeleted()) object->Render();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void QBrick::SetState(int state)
{
	switch (state)
	{
	case BRICK_STATE_QBRICK:
		break;
	case BRICK_STATE_BBRICK:
		vy = -BRICK_BOUNCING_SPEED;
		break;
	}
	CGameObject::SetState(state);
}