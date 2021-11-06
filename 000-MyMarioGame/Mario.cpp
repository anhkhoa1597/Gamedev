#include <algorithm>
#include "debug.h"

#include "Mario.h"


CMario::CMario(float x, float y) : CGameObject(x, y, MARIO, true)
{
	isSitting = false;
	maxVx = 0.0f;
	ax = 0.0f;
	ay = setting->mario_gravity;
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	untouchable_start = -1;

	isOnPlatform = false;
	coin = 0;
	life = setting->mario_life;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > setting->mario_untouchable_time)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (e->ny > 0)
	{
		if (brick->GetState() != BRICK_STATE_BBRICK)
		{
			if (brick->IsNoItem()) //if brick doesnt have item it is normal brick so dont need to check normal brick
			{
				if (level == MARIO_LEVEL_SMALL)
				{
					brick->SetUpTimesLeftToBounce();
					brick->SetState(BRICK_STATE_BOUNCE);
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					brick->SetState(BRICK_STATE_BREAK);
					//brick->SetState(BRICK_STATE_BOUNCE);
				}
			}
			else
			{
				brick->SetState(BRICK_STATE_BOUNCE);
			}
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_BOUNCE_DIE)
		{
			vy = -setting->mario_jump_deflect_speed;
			if (goomba->HasWing()) goomba->LostWing();
			else goomba->SetState(GOOMBA_STATE_DIE);
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_BOUNCE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					if (life > 1)
					{
						life--;
						DebugOut(L">>> Mario Life Left: %d >>> \n", life);
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (e->ny < 0)
	{
		if (koopa->GetState() != KOOPA_STATE_BOUNCE_DIE)
		{
			vy = -setting->mario_jump_deflect_speed;
			if (koopa->HasWing()) koopa->LostWing();
			else if (koopa->GetState() == KOOPA_STATE_SHIELD_ROLLING_LEFT || koopa->GetState() == KOOPA_STATE_SHIELD_ROLLING_RIGHT)
				koopa->SetState(KOOPA_STATE_SHIELD_IDLE);
			else if (koopa->GetState() == KOOPA_STATE_SHIELD_IDLE)
			{
				SetState(MARIO_STATE_KICK);
				float x_koopa, y_koopa;
				koopa->GetPosition(x_koopa, y_koopa);
				if (x > x_koopa + KOOPA_WIDTH / 2) koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_LEFT);
				else koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_RIGHT);
			}
			else if (koopa->GetTypeShield() == NO_SHIELD)
			{
				koopa->SetTypeShield(SHIELD_DOWN);
				koopa->SetState(KOOPA_STATE_SHIELD_IDLE);
			}
		}
	}
	else
	{
		if (koopa->GetState() == KOOPA_STATE_SHIELD_IDLE)
		{
			SetState(MARIO_STATE_KICK);
			if (e->nx < 0) koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_RIGHT);
			else koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_LEFT);
		}
		else if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_BOUNCE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					if (life > 1)
					{
						life--;
						DebugOut(L">>> Mario Life Left: %d >>> \n", life);
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	IncreaseCoin();
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (mushroom->GetType() == RMUSHROOM) SetLevel(MARIO_LEVEL_BIG);
	else if (mushroom->GetType() == GMUSHROOM) 
	{
		LifeUp(setting->mushroom_life_up);
		DebugOut(L">>> Mario Life Left: %d >>> \n", life);
	}
	e->obj->Delete();
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == setting->mario_accel_run_x)
		{
			if (nx >= 0) aniId = setting->id_ani_mario_small_jump_run_right;
			else aniId = setting->id_ani_mario_small_jump_run_left;
		}
		else
		{
			if (nx >= 0) aniId = setting->id_ani_mario_small_jump_walk_right;
			else aniId = setting->id_ani_mario_small_jump_walk_left;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0) aniId = setting->id_ani_mario_sit_right;
			else aniId = setting->id_ani_mario_sit_left;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = setting->id_ani_mario_small_idle_right;
				else aniId = aniId = setting->id_ani_mario_small_idle_left;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = setting->id_ani_mario_small_brace_right;
				else if (ax == setting->mario_accel_run_x) aniId = setting->id_ani_mario_small_running_right;
				else if (ax == setting->mario_accel_walk_x) aniId = setting->id_ani_mario_small_walking_right;
			}
			else // vx < 0
			{
				if (ax > 0) aniId = setting->id_ani_mario_small_brace_left;
				else if (ax == -setting->mario_accel_run_x) aniId = setting->id_ani_mario_small_running_left;
				else if (ax == -setting->mario_accel_walk_x) aniId = setting->id_ani_mario_small_walking_left;
			}
	if (state == MARIO_STATE_KICK)
	{
		if (nx < 0) aniId = setting->id_ani_mario_small_kick_left;
		else aniId = setting->id_ani_mario_small_kick_right;
	}
	if (aniId == -1) aniId = setting->id_ani_mario_small_idle_right;;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == setting->mario_accel_run_x)
		{
			if (nx >= 0) aniId = setting->id_ani_mario_jump_run_right;
			else aniId = setting->id_ani_mario_jump_run_left;
		}
		else
		{
			if (nx >= 0) aniId = setting->id_ani_mario_jump_walk_right;
			else aniId = setting->id_ani_mario_jump_walk_left;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0) aniId = setting->id_ani_mario_sit_right;
			else aniId = setting->id_ani_mario_sit_left;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = setting->id_ani_mario_idle_right;
				else aniId = setting->id_ani_mario_idle_left;
			}
			else if (vx > 0)
			{
				if (ax < 0) aniId = setting->id_ani_mario_brace_right;
				else if (ax == setting->mario_accel_run_x) aniId = setting->id_ani_mario_running_right;
				else if (ax == setting->mario_accel_walk_x) aniId = setting->id_ani_mario_walking_right;
			}
			else // vx < 0
			{
				if (ax > 0) aniId = setting->id_ani_mario_brace_left;
				else if (ax == -setting->mario_accel_run_x) aniId = setting->id_ani_mario_running_left;
				else if (ax == -setting->mario_accel_walk_x) aniId = setting->id_ani_mario_walking_left;
			}
	if (state == MARIO_STATE_KICK)
	{
		if (nx < 0) aniId = setting->id_ani_mario_kick_left;
		else aniId = setting->id_ani_mario_kick_right;
	}
	if (aniId == -1) aniId = setting->id_ani_mario_idle_right;;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = setting->id_ani_mario_die;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	if (untouchable == 0)
		animations->Get(aniId)->Render(x, y);
	else
		//need to make mario blinks
		animations->Get(aniId)->Render(x, y);
	
	DebugOutTitle(L"Coins: %d	Life: %d", coin, life);
	
	//RenderBoundingBox();
}

//logic
void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = setting->mario_running_speed;
		ax = setting->mario_accel_run_x;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -setting->mario_running_speed;
		ax = -setting->mario_accel_run_x;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = setting->mario_walking_speed;
		ax = setting->mario_accel_walk_x;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -setting->mario_walking_speed;
		ax = -setting->mario_accel_walk_x;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == setting->mario_running_speed)
				vy = -setting->mario_jump_run_speed_y;
			else
				vy = -setting->mario_jump_speed_y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += setting->mario_jump_speed_y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_KICK:
		break;
	case MARIO_STATE_DIE:
		vy = -setting->mario_jump_deflect_speed;
		vx = 0;
		ax = 0;
		break;
	}
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH - 1;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT - 1;
		}
		else
		{
			right = left + MARIO_BIG_BBOX_WIDTH - 1;
			bottom = top + MARIO_BIG_BBOX_HEIGHT - 1;
		}
	}
	else
	{
		right = left + MARIO_SMALL_BBOX_WIDTH - 1;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT - 1;
	}
}

void CMario::SetLevel(int l)
{
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		y -= MARIO_CHANGE_LEVEL_HEIGHT_ADJUST;
		break;
	case MARIO_LEVEL_BIG:
	case MARIO_LEVEL_FIRE: //need create FIRE MARIO
	case MARIO_LEVEL_FOX: //need create FOX MARIO
	case MARIO_LEVEL_BEAR: //need create BEAR MARIO
	case MARIO_LEVEL_FROG: //need create FROG MARIO
	case MARIO_LEVEL_TURTLE: //need create TURTLE MARIO
		break;
	
	}
	level = l;
}

