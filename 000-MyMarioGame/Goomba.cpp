#include "Goomba.h"


CGoomba::CGoomba(float x, float y, int type, bool has_wing):CGameObject(x, y, type)
{
	this->ax = 0;
	this->has_wing = has_wing;
	die_start = -1;
	if (this->has_wing) ay = setting->wing_goomba_gravity;
	else ay = setting->goomba_gravity;
	SetState(GOOMBA_STATE_WALKING_LEFT);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x;
		top = y;
		right = left + setting->goomba_width - 1;
		bottom = top + setting->goomba_height_die - 1;
	}
	else
	{ 
		left = x;
		top = y;
		right = left + setting->goomba_width - 1;
		bottom = top + setting->goomba_height - 1;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		if (this->has_wing)
		{
			if (e->ny < 0)
			{
				switch (state)
				{
				case GOOMBA_STATE_WALKING_LEFT: case GOOMBA_STATE_WALKING_RIGHT:
					if (GetTickCount64() - this->walk_start > setting->wing_goomba_walk_timeout)
					{
						SetState(GOOMBA_STATE_LOW_JUMP);
					}
					break;
				case GOOMBA_STATE_LOW_JUMP:
					if (numberOfLowJump > 0) SetState(GOOMBA_STATE_LOW_JUMP);
					else SetState(GOOMBA_STATE_HIGH_JUMP);
					break;
				case GOOMBA_STATE_HIGH_JUMP:
					if (vx < 0) SetState(GOOMBA_STATE_WALKING_LEFT);
					else if (vx > 0) SetState(GOOMBA_STATE_WALKING_RIGHT);
					break;
				}
			}
			else vy = 0;
		}
		else
		{
			vy = 0;
			if (this->type == RGOOMBA)
			{
				float l, t, r, b;
				e->obj->GetBoundingBox(l, t, r, b);
				if (vx < 0 && x + (float)setting->goomba_width / 2 < l) SetState(GOOMBA_STATE_WALKING_RIGHT);
				else if (vx > 0 && x + (float)setting->goomba_width / 2 > r) SetState(GOOMBA_STATE_WALKING_LEFT);
			}
		}
	}
	else if (e->nx != 0) vx = -vx;
}

void CGoomba::LostWing()
{ 
	has_wing = false;
	if (vx < 0) SetState(GOOMBA_STATE_WALKING_LEFT);
	else if (vx > 0) SetState(GOOMBA_STATE_WALKING_RIGHT);
	ay = setting->goomba_gravity; 
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((this->state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > setting->goomba_die_timeout))
	{
		isDeleted = true;
		return;
	}
	else if ((this->state == GOOMBA_STATE_BOUNCE_DIE) && (GetTickCount64() - die_start > setting->goomba_bounce_die_timeout))
	{
		isDeleted = true;
		return;
	}
	if (type == RGOOMBA && has_wing && (state == GOOMBA_STATE_WALKING_LEFT || state == GOOMBA_STATE_WALKING_RIGHT))
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		float x_mario, y_mario;
		mario->GetPosition(x_mario, y_mario);
		if (x_mario < x) vx = -setting->goomba_walking_speed;
		else if (x_mario > x) vx = setting->goomba_walking_speed;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoomba::Render()
{
	int aniId = -1;
	if (type == GOOMBA)
	{
		aniId = setting->id_ani_goomba_walking;
		if (state == GOOMBA_STATE_DIE) aniId = setting->id_ani_goomba_die;
		else if (state == GOOMBA_STATE_BOUNCE_DIE) aniId = setting->id_ani_goomba_bounce_die;
	}
	else if (type == RGOOMBA)
	{
		aniId = setting->id_ani_red_goomba_walking;
		if (state == GOOMBA_STATE_DIE) aniId = setting->id_ani_red_goomba_die;
		else if (state == GOOMBA_STATE_BOUNCE_DIE) aniId = setting->id_ani_red_goomba_bounce_die;
	}
	if (has_wing)
	{
		int aniWingId = setting->id_ani_wing_walk;
		if (state == GOOMBA_STATE_LOW_JUMP || state == GOOMBA_STATE_HIGH_JUMP)
		{
			aniWingId = setting->id_ani_wing_jump;
		}
		CAnimations::GetInstance()->Get(aniWingId)->Render(x - 2, y - 10);
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING_LEFT: 
			walk_start = GetTickCount64();
			numberOfLowJump = 3;
			vx = -setting->goomba_walking_speed;
			break;
		case GOOMBA_STATE_WALKING_RIGHT:
			walk_start = GetTickCount64();
			numberOfLowJump = 3;
			vx = setting->goomba_walking_speed;
			break;
		case GOOMBA_STATE_LOW_JUMP:
			vy = -setting->wing_goomba_low_jump;
			numberOfLowJump--;
			break;
		case GOOMBA_STATE_HIGH_JUMP:
			vy = -setting->wing_goomba_high_jump;
			break;
		case GOOMBA_STATE_BOUNCE_DIE:
			die_start = GetTickCount64();
			vy = -setting->goomba_bouncing_up_speed;
			break;
	}
	CGameObject::SetState(state);
}
