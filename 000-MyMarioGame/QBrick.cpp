#include "QBrick.h"

QBrick::QBrick(float x, float y, int width, int height, LPGAMEOBJECT object) : CBrick(x, y, width, height)
{
	SetState(BRICK_STATE_QBRICK);
	this->initialPositionY = y;
	this->object = object;
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
	}
	if (!object->IsDeleted()) object->Update(dt, coObjects);
}

void QBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = -1;

	if (state == BRICK_STATE_QBRICK)
		aniId = ID_ANI_QBRICK;
	else if (state == BRICK_STATE_BBRICK)
		aniId = ID_ANI_BBrick;

	if(!object->IsDeleted()) object->Render();
	animations->Get(aniId)->Render(x, y);
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
		if (!object->IsDeleted())
		{
			if (object->GetState() == COIN_STATE_IDLE)
				object->SetState(COIN_STATE_DROP);
			else if (object->GetState() == MUSHROOM_STATE_IDLE)
				object->SetState(MUSHROOM_STATE_DROP);
		}
		break;
	}
	CGameObject::SetState(state);
}