#include "Koopa.h"

CKoopa::CKoopa(float x, float y, int type, bool has_wing) : CGameObject(x, y, type)
{
	this->ax = 0;
	this->has_wing = has_wing;
	die_start = -1;
	if (this->has_wing) ay = setting->wing_koopa_gravity;
	else ay = setting->koopa_gravity;
	SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + KOOPA_BBOX_WIDTH - 1;
	bottom = top + KOOPA_BBOX_HEIGHT - 1;
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		if (this->has_wing)
		{
			if (e->ny < 0) SetState(KOOPA_STATE_JUMPING);
			else vy = 0;
		}
		else
		{
			vy = 0;
			if (this->type == RKOOPA)
			{
				float l, t, r, b;
				e->obj->GetBoundingBox(l, t, r, b);
				if (vx < 0 && x + (float)KOOPA_WIDTH / 2 < l) SetState(KOOPA_STATE_WALKING_RIGHT);
				else if (vx > 0 && x + (float)KOOPA_WIDTH / 2 > r) SetState(KOOPA_STATE_WALKING_LEFT);
			}
		}
	}
	else if (e->nx > 0) SetState(KOOPA_STATE_WALKING_RIGHT);
	else if (e->nx < 0) SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopa::LostWing()
{
	has_wing = false;
	ay = setting->koopa_gravity;
	if (vx < 0) SetState(KOOPA_STATE_WALKING_LEFT);
	else if (vx > 0) SetState(KOOPA_STATE_WALKING_RIGHT);
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((this->state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > setting->koopa_die_timeout))
	{
		isDeleted = true;
		return;
	}
	//else if ((this->state == KOOPA_STATE_BOUNCE_DIE) && (GetTickCount64() - die_start > setting->koopa_bounce_die_timeout))
	//{
	//	isDeleted = true;
	//	return;
	//}
	
	//if (this->has_wing)
	//{
	//	if (this->state == GOOMBA_STATE_WALKING)
	//	{
	//		if (GetTickCount64() - this->walk_start < setting->wing_goomba_walk_timeout)
	//		{
	//		}
	//		else
	//		{
	//			SetState(GOOMBA_STATE_LOW_JUMP);
	//		}
	//	}
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = setting->id_ani_coin_idle;
	if (type == KOOPA)
	{
		if (vx > 0) aniId = setting->id_ani_koopa_walking_right;
		else aniId = setting->id_ani_koopa_walking_left;
		//if (state == KOOMBA_STATE_DIE) aniId = setting->id_ani_goomba_die;
		//else if (state == KOOMBA_STATE_BOUNCE_DIE) aniId = setting->id_ani_goomba_bounce_die;
	}
	else if (type == RKOOPA)
	{
		if (vx > 0) aniId = setting->id_ani_red_koopa_walking_right;
		else aniId = setting->id_ani_red_koopa_walking_left;
		/*if (state == KOOPA_STATE_DIE) aniId = setting->id_ani_red_goomba_die;
		else if (state == KOOPA_STATE_BOUNCE_DIE) aniId = setting->id_ani_red_goomba_bounce_die;*/
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	if (has_wing)
	{
		int aniWingId = setting->id_ani_wing_left;
		if (vx < 0) CAnimations::GetInstance()->Get(aniWingId)->Render(x + 7, y - 3);
		else if (vx > 0)
		{
			aniWingId = setting->id_ani_wing_right;
			CAnimations::GetInstance()->Get(aniWingId)->Render(x, y - 3);
		}
	}
}

void CKoopa::SetState(int state)
{
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		vx = -setting->koopa_walking_speed;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		vx = setting->koopa_walking_speed;
		break;
	case KOOPA_STATE_JUMPING:
		vy = -setting->wing_koopa_jump_speed;
		break;
	//case KOOPA_STATE_BOUNCE_DIE:
	//	die_start = GetTickCount64();
	//	vy = -setting->goomba_bouncing_speed;
	//	break;
	}
	CGameObject::SetState(state);
}
