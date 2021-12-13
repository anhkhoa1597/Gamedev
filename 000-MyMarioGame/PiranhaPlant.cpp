#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y, int type) : CGameObject(x, y, type)
{
	nx = ny = -1;
	SetState(PIRANHA_PLANT_STATE_IDLE);
	//if (type == PIRANHA_PLANT) SetState(PIRANHA_PLANT_STATE_LEFT_DOWN);
	//else if (type == HORIZONTAL_PIRANHA_PLANT) SetState(PIRANHA_PLANT_STATE_HORIZONTAL);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + setting->piranha_plant_width - 1;
	bottom = top + setting->piranha_plant_height - 1;
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float x_mario, y_mario;
	mario->GetPosition(x_mario, y_mario);
	if (x_mario < x) nx = -1;
	else nx = 1;

	if (y_mario < y) ny = -1;
	else ny = 1;

	if (state == PIRANHA_PLANT_STATE_IDLE)
	{
		if (IsMarioInZoneToPlantUp(x_mario))
		{
			SetState(PIRANHA_PLANT_STATE_GO_UP);
		}
	}
	else if (state == PIRANHA_PLANT_STATE_GO_UP)
	{
		if (y <= initY - setting->piranha_plant_height)
		{
			y = initY - setting->piranha_plant_height;
			vy = 0;
			SetState(PIRANHA_PLANT_STATE_GO_DOWN);
		}
	}
	else if (state == PIRANHA_PLANT_STATE_GO_DOWN)
	{
		if (y >= initY)
		{
			y = initY;
			SetState(PIRANHA_PLANT_STATE_IDLE);
		}
	}
}

void CPiranhaPlant::Render()
{
	int aniId = setting->id_ani_coin_idle; 
	if (type == PIRANHA_PLANT)
	{
		if (nx < 0 && ny < 0) aniId = setting->id_ani_piranha_plant_left_up;
		else if (nx < 0 && ny > 0) aniId = setting->id_ani_piranha_plant_left_down;
		else if (nx > 0 && ny < 0) aniId = setting->id_ani_piranha_plant_right_up;
		else if (nx > 0 && ny > 0) aniId = setting->id_ani_piranha_plant_right_down;
	}
	else if (type == HORIZONTAL_PIRANHA_PLANT) aniId = setting->id_ani_horizontal_piranha_plant;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

bool CPiranhaPlant::IsMarioInZoneToPlantUp(float x_mario)
{
	if (x_mario > x - 32 && x_mario < x + 16 + setting->piranha_plant_width) return false;
	return true;
}

void CPiranhaPlant::SetState(int state)
{
	switch (state)
	{
	case PIRANHA_PLANT_STATE_IDLE:
		vy = 0;
		break;
	case PIRANHA_PLANT_STATE_GO_UP:
		vy = -0.02f;
		break;
	case PIRANHA_PLANT_STATE_GO_DOWN:
		vy = 0.02f;
		break;
	}
	CGameObject::SetState(state);
}
