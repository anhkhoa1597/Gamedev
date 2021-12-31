#include "Tail.h"

CTail::CTail(float x, float y, int width, int height) : CGameObject(x, y, TAIL)
{
	vy = 0;
	vx = 0;
	this->width = width;
	this->height = height;
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x <= initX - width || x > initX + width) isDeleted = true;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
}

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
}

void CTail::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
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

void CTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
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

void CTail::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranhaPlant = dynamic_cast<CPiranhaPlant*>(e->obj);
	e->obj->Delete();
}

void CTail::OnCollisionWithBrick(LPCOLLISIONEVENT e)
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

void CTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TAIL_STATE_ATTACK_LEFT:
		vx = -0.5f;
		break;
	case TAIL_STATE_ATTACK_RIGHT:
		vx = 0.5f;
		break;
	}
}
