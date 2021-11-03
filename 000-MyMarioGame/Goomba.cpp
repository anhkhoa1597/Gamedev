#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int type, bool has_wing):CGameObject(x, y, type)
{
	this->ax = 0;
	this->has_wing = has_wing;
	die_start = -1;
	nx = -1;
	if (this->has_wing) ay = GOOMBA_WING_GRAVITY;
	else ay = GOOMBA_GRAVITY;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x;
		top = y;
		right = left + GOOMBA_BBOX_WIDTH - 1;
		bottom = top + GOOMBA_BBOX_HEIGHT - 1;
	}
	else
	{ 
		left = x;
		top = y;
		right = left + GOOMBA_BBOX_WIDTH - 1;
		bottom = top + GOOMBA_BBOX_HEIGHT - 1;
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

	if (e->ny != 0)
	{
		if (this->has_wing)
		{
			if (e->ny < 0)
			{
				switch (state)
				{
				case GOOMBA_STATE_WALKING:
					break;
				case GOOMBA_STATE_LOW_JUMP:
					if (numberOfLowJump > 0) SetState(GOOMBA_STATE_LOW_JUMP);
					else SetState(GOOMBA_STATE_HIGH_JUMP);
					break;
				case GOOMBA_STATE_HIGH_JUMP:
					SetState(GOOMBA_STATE_WALKING);
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
				if ((vx < 0 && x + (float)GOOMBA_WIDTH / 2 < l) || 
					(vx > 0 && x + (float)GOOMBA_WIDTH / 2 > r))
				{
					ChangeDir();
				}
			}
		}
	}
	else if (e->nx != 0) ChangeDir();
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((this->state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	else if ((this->state == GOOMBA_STATE_BOUNCE_DIE) && (GetTickCount64() - die_start > GOOMBA_BOUNCE_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (this->has_wing)
	{
		if (this->state == GOOMBA_STATE_WALKING)
		{
			if (GetTickCount64() - this->walk_start < GOOMBA_WALK_TIME_TO_JUMP)
			{
			}
			else
			{
				SetState(GOOMBA_STATE_LOW_JUMP);
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoomba::Render()
{
	int aniId = -1;
	if (type == GOOMBA)
	{
		aniId = ID_ANI_GOOMBA_WALKING;
		if (state == GOOMBA_STATE_DIE) aniId = ID_ANI_GOOMBA_DIE;
		else if (state == GOOMBA_STATE_BOUNCE_DIE) aniId = ID_ANI_GOOMBA_BOUNCE_DIE;
	}
	else if (type == RGOOMBA)
	{
		aniId = ID_ANI_RED_GOOMBA_WALKING;
		if (state == GOOMBA_STATE_DIE) aniId = ID_ANI_RED_GOOMBA_DIE;
		else if (state == GOOMBA_STATE_BOUNCE_DIE) aniId = ID_ANI_RED_GOOMBA_BOUNCE_DIE;
	}
	if (has_wing)
	{
		int aniWingId = ID_ANI_WING_WALK;
		if (state == GOOMBA_STATE_LOW_JUMP || state == GOOMBA_STATE_HIGH_JUMP)
		{
			aniWingId = ID_ANI_WING_JUMP;
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
		case GOOMBA_STATE_WALKING: 
			walk_start = GetTickCount64();
			numberOfLowJump = 3;
			vx = nx * GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_LOW_JUMP:
			vy = -GOOMBA_WING_LOW_JUMP;
			numberOfLowJump--;
			break;
		case GOOMBA_STATE_HIGH_JUMP:
			vy = -GOOMBA_WING_HIGH_JUMP;
			break;
		case GOOMBA_STATE_BOUNCE_DIE:
			die_start = GetTickCount64();
			vy = -GOOMBA_BOUNCING_SPEED;
			break;
	}
	CGameObject::SetState(state);
}
