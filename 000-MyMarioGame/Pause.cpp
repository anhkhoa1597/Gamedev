#include "Pause.h"

CPause::CPause(float x, float y, int width, int height) : CGameObject(x, y, PAUSE)
{
	this->width = width;
	this->height = height;
	pause_start = -1;
	isCollidable = true;
	SetState(PAUSE_STATE_NORMAL);
}

void CPause::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width - 1;
	bottom = top + height - 1;
}

void CPause::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == PAUSE_STATE_BE_HITTED && GetTickCount64() - pause_start <= 10000)
		//if (state == PAUSE_STATE_BE_HITTED && GetTickCount64() - pause_start > setting->pause_timeout)
	{

	}
}

void CPause::Render()
{
	int aniId = setting->id_ani_pause;
	if (state == PAUSE_STATE_BE_HITTED) aniId = setting->id_ani_pause_be_hitted;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CPause::SetState(int state)
{
	switch (state)
	{
	case PAUSE_STATE_NORMAL:
		break;
	case PAUSE_STATE_BE_HITTED:
		pause_start = GetTickCount64();
		isCollidable = false;
		break;
	}
	CGameObject::SetState(state);
}
