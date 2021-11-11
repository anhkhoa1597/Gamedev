#include "Koopa.h"


CKoopa::CKoopa(float x, float y, int type, bool has_wing) : CGameObject(x, y, type)
{
	this->ax = 0;
	this->has_wing = has_wing;
	die_start = -1;
	type_shield = NO_SHIELD;
	if (this->has_wing) ay = setting->wing_koopa_gravity;
	else ay = setting->koopa_gravity;
	SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (type_shield == NO_SHIELD)
	{
		left = x;
		top = y;
		right = left + setting->koopa_width - 1;
		bottom = top + setting->koopa_height - 1;
	}
	else
	{
		left = x;
		top = y;
		right = left + setting->koopa_width - 1;
		bottom = top + setting->koopa_shield_height - 1;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMushroom*>(e->obj)) return;
	if (type_shield == NO_SHIELD)
	{
		if (!e->obj->IsBlocking()) return;
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
					if (vx < 0 && x + (float)setting->koopa_width / 2 < l) SetState(KOOPA_STATE_WALKING_RIGHT);
					else if (vx > 0 && x + (float)setting->koopa_width / 2 > r) SetState(KOOPA_STATE_WALKING_LEFT);
				}
			}
		}
		else if (e->nx > 0) SetState(KOOPA_STATE_WALKING_RIGHT);
		else if (e->nx < 0) SetState(KOOPA_STATE_WALKING_LEFT);
	}
	else
	{
		if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0;
			if (e->ny < 0 && (state == KOOPA_STATE_BOUNCE_LEFT || state == KOOPA_STATE_BOUNCE_RIGHT))
				SetState(KOOPA_STATE_SHIELD_IDLE);
		}
		else if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
			if (state == KOOPA_STATE_SHIELD_ROLLING_LEFT) SetState(KOOPA_STATE_SHIELD_ROLLING_RIGHT);
			else if (state == KOOPA_STATE_SHIELD_ROLLING_RIGHT) SetState(KOOPA_STATE_SHIELD_ROLLING_LEFT);
		}
		if (state == KOOPA_STATE_SHIELD_ROLLING_LEFT || state == KOOPA_STATE_SHIELD_ROLLING_RIGHT)
		{
			if (dynamic_cast<CKoopa*>(e->obj))
				OnCollisionWithKoopa(e);
			else if (dynamic_cast<CGoomba*>(e->obj))
				OnCollisionWithGoomba(e);
			else if (dynamic_cast<CBrick*>(e->obj))
				OnCollisionWithBrick(e);
		}
	}
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (koopa->GetState() != KOOPA_STATE_BOUNCE_DIE)
	{
		float x_koopa, y_koopa;
		koopa->GetPosition(x_koopa, y_koopa);
		if (koopa->GetState() != KOOPA_STATE_SHIELD_ROLLING_LEFT && koopa->GetState() != KOOPA_STATE_SHIELD_ROLLING_RIGHT)
		{
			koopa->LostWing();
			if (x < x_koopa) koopa->SetSpeed(setting->koopa_bouncing_speed, 0);
			else koopa->SetSpeed(-setting->koopa_bouncing_speed, 0);
			koopa->SetState(KOOPA_STATE_BOUNCE_DIE);
		}
		else
		{
			if (x < x_koopa)
			{
				koopa->SetSpeed(setting->koopa_bouncing_speed, 0);
				SetSpeed(-setting->koopa_bouncing_speed, 0);
			}
			else
			{
				koopa->SetSpeed(-setting->koopa_bouncing_speed, 0);
				SetSpeed(setting->koopa_bouncing_speed, 0);
			}
			koopa->SetState(KOOPA_STATE_BOUNCE_DIE);
			SetState(KOOPA_STATE_BOUNCE_DIE);
		}
		
	}
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_BOUNCE_DIE)
	{
		float x_goomba, y_goomba;
		goomba->GetPosition(x_goomba, y_goomba);
		goomba->LostWing();
		if (x < x_goomba) goomba->SetSpeed(setting->goomba_bouncing_speed, 0);
		else goomba->SetSpeed(-setting->goomba_bouncing_speed, 0);
		goomba->SetState(GOOMBA_STATE_BOUNCE_DIE);
	}
}

void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (e->nx != 0)
	{
		if (brick->GetState() != BRICK_STATE_BBRICK)
		{
			if (brick->IsNoItem()) brick->SetState(BRICK_STATE_BREAK);
			else brick->SetState(BRICK_STATE_BOUNCE);
		}
	}
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

	if ((state == KOOPA_STATE_SHIELD_IDLE) && (GetTickCount64() - shield_start > setting->koopa_shield_timeout))
	{
		SetState(KOOPA_STATE_SHIELD_STANDING);
	}
	else if ((state == KOOPA_STATE_SHIELD_STANDING) && (GetTickCount64() - standing_start > setting->koopa_shield_standing_timeout))
	{
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		float x_mario, y_mario;
		mario->GetPosition(x_mario, y_mario);
		y -= setting->koopa_height - setting->koopa_shield_height;
		if (x < x_mario) SetState(KOOPA_STATE_WALKING_RIGHT);
		else if (x >= x_mario) SetState(KOOPA_STATE_WALKING_LEFT);
	}
	else if ((state == KOOPA_STATE_BOUNCE_DIE) && (GetTickCount64() - die_start > setting->koopa_bounce_die_timeout))
	{
		isDeleted = true;
		return;
	}
		
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopa::Render()
{
	int aniId = setting->id_ani_coin_idle;
	if (type == KOOPA)
	{
		switch (type_shield)
		{
		case NO_SHIELD:
			if (vx < 0) aniId = setting->id_ani_koopa_walking_left;
			else if (vx > 0) aniId = setting->id_ani_koopa_walking_right;
			break;
		case SHIELD_DOWN:
			if (state == KOOPA_STATE_SHIELD_IDLE) aniId = setting->id_ani_koopa_shield_idle_down;
			else if (state == KOOPA_STATE_SHIELD_STANDING) aniId = setting->id_ani_koopa_shield_standing_down;
			else if (state == KOOPA_STATE_SHIELD_ROLLING_LEFT || state == KOOPA_STATE_SHIELD_ROLLING_RIGHT) 
				aniId = setting->id_ani_koopa_shield_rolling_down;
			break;
		case SHIELD_UP:
			if (state == KOOPA_STATE_SHIELD_IDLE || state == KOOPA_STATE_BOUNCE_LEFT || state == KOOPA_STATE_BOUNCE_RIGHT) aniId = setting->id_ani_koopa_shield_idle_up;
			else if (state == KOOPA_STATE_SHIELD_STANDING) aniId = setting->id_ani_koopa_shield_standing_up;
			else if (state == KOOPA_STATE_SHIELD_ROLLING_LEFT || state == KOOPA_STATE_SHIELD_ROLLING_RIGHT)
				aniId = setting->id_ani_koopa_shield_rolling_up;
			break;
		}
		if (state == KOOPA_STATE_BOUNCE_DIE) aniId = setting->id_ani_koopa_shield_idle_up;
	}
	else if (type == RKOOPA)
	{
		switch (type_shield)
		{
		case NO_SHIELD:
			if (vx < 0) aniId = setting->id_ani_red_koopa_walking_left;
			else if (vx > 0) aniId = setting->id_ani_red_koopa_walking_right;
			break;
		case SHIELD_DOWN:
			if (state == KOOPA_STATE_SHIELD_IDLE) aniId = setting->id_ani_red_koopa_shield_idle_down;
			else if (state == KOOPA_STATE_SHIELD_STANDING) aniId = setting->id_ani_red_koopa_shield_standing_down;
			else if (state == KOOPA_STATE_SHIELD_ROLLING_LEFT || state == KOOPA_STATE_SHIELD_ROLLING_RIGHT)
				aniId = setting->id_ani_red_koopa_shield_rolling_down;
			break;
		case SHIELD_UP:
			if (state == KOOPA_STATE_SHIELD_IDLE || state == KOOPA_STATE_BOUNCE_LEFT || state == KOOPA_STATE_BOUNCE_RIGHT) aniId = setting->id_ani_red_koopa_shield_idle_up;
			else if (state == KOOPA_STATE_SHIELD_STANDING) aniId = setting->id_ani_red_koopa_shield_standing_up;
			else if (state == KOOPA_STATE_SHIELD_ROLLING_LEFT || state == KOOPA_STATE_SHIELD_ROLLING_RIGHT)
				aniId = setting->id_ani_red_koopa_shield_rolling_up;
			break;
		}
		if (state == KOOPA_STATE_BOUNCE_DIE)
			aniId = setting->id_ani_red_koopa_shield_idle_up;
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
	case KOOPA_STATE_WALKING_LEFT:
		vx = -setting->koopa_walking_speed;
		type_shield = NO_SHIELD;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		vx = setting->koopa_walking_speed;
		type_shield = NO_SHIELD;
		break;
	case KOOPA_STATE_JUMPING:
		vy = -setting->wing_koopa_jump_speed;
		break;
	case KOOPA_STATE_SHIELD_IDLE:
		shield_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPA_STATE_SHIELD_ROLLING_LEFT:
		vx = -setting->koopa_shield_rolling_speed;
		break;
	case KOOPA_STATE_SHIELD_ROLLING_RIGHT:
		vx = setting->koopa_shield_rolling_speed;
		break;
	case KOOPA_STATE_SHIELD_STANDING:
		standing_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPA_STATE_BOUNCE_LEFT:
		vy = -setting->koopa_bouncing_up_speed;
		vx = -setting->koopa_bouncing_speed;
		break;
	case KOOPA_STATE_BOUNCE_RIGHT:
		vy = -setting->koopa_bouncing_up_speed;
		vx = setting->koopa_bouncing_speed;
		break;
	case KOOPA_STATE_BOUNCE_DIE:
		die_start = GetTickCount64();
		vy = -setting->koopa_bouncing_up_speed;
		break;
	}
	CGameObject::SetState(state);
}
