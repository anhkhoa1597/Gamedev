#include <algorithm>
#include "debug.h"

#include "Mario.h"


CMario::CMario(float x, float y) : CGameObject(x, y, MARIO)
{
	koopa = NULL;
	maxVx = 0.0f;
	avgVx = 0.0f;
	currentPower = 0;
	maxPower = setting->mario_max_power;
	ax = 0.0f;
	ay = setting->mario_gravity;
	level = MARIO_LEVEL_SMALL;
	height = setting->mario_small_height;
	untouchable = 0;
	points_in_level = { setting->point_0, setting->point_1, setting->point_2, setting->point_3, setting->point_4, setting->point_5, setting->point_6, setting->point_7 };

	untouchable_start = -1;
	kick_start = -1;
	powerTime_start = -1;
	invisible_start = -1;
	slow_falling_start = -1;
	flying_start = -1;
	fly_falling_start = -1;
	attack_start = -1;
	attack_left_start = -1;
	attack_right_start = -1;

	isBlockingKeyboard = false;
	isOnPlatform = false;
	isCarryingKoopa = false;
	isBlockedLeftRight = false;
	isInvisible = false;
	isPlayer = true;
	isSitting = false;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	LPGAME game = CGame::GetInstance();
	LPHUD hud = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHud();
	hud->UpdatePowerMeter(currentPower);

	//handle speed
	if (abs(ax) == abs(setting->mario_accel_run_x) && isOnPlatform)
	{	
		if (abs(vx) > abs(avgVx * (currentPower + 1)))
		{
			vx = avgVx * (currentPower + 1);
		}
		if (abs(vx) >= abs(avgVx * (currentPower + 1)) && GetTickCount64() - powerTime_start > setting->mario_power_increase_delay_timeout)
		{
			if (currentPower < maxPower)
			{
				currentPower++;
			}
			powerTime_start = GetTickCount64();
		}
	}
	else
	{
		if (abs(vx) > abs(maxVx))
		{
			vx = maxVx;
		}
		if (currentPower >= maxPower)
		{
			if (level != MARIO_LEVEL_RACCOON)
			{
				if (GetTickCount64() - powerTime_start > setting->mario_max_power_timeout)
				{
					powerTime_start = GetTickCount64();
					currentPower--;
				}
			}
			else
			{
				if (isOnPlatform)
				{
					if (GetTickCount64() - powerTime_start > setting->mario_max_power_timeout)
					{
						powerTime_start = GetTickCount64();
						currentPower--;
					}
				}
				else
				{
					if (GetTickCount64() - flying_start > setting->mario_flying_timeout)
					{
						currentPower = 0;
						ay = setting->mario_gravity;
					}
				}
			}
		}
		else
		{
			if (currentPower > 0 && GetTickCount64() - powerTime_start > setting->mario_power_decrease_delay_timeout)
			{
				powerTime_start = GetTickCount64();
				currentPower--;
			}
		}
	}

	if (state != MARIO_STATE_GO_DOWN && state != MARIO_STATE_GO_UP && GetTickCount64() - slow_falling_start > setting->mario_slow_falling_timeout && GetTickCount64() - fly_falling_start > setting->mario_fly_falling_timeout)
	{
		ay = setting->mario_gravity;
	}

	 //reset untouchable timer if untouchable time has passed
	if (untouchable == 1 && GetTickCount64() - untouchable_start <= setting->mario_untouchable_time)
	{
		if (GetTickCount64() - invisible_start <= setting->mario_invisible_timeout / 2)
		{
			isInvisible = true;
		}
		else if (GetTickCount64() - invisible_start <= setting->mario_invisible_timeout)
		{
			isInvisible = false;
		}
		else
		{
			invisible_start = GetTickCount64();
		}
	}
	else if (untouchable == 1 && GetTickCount64() - untouchable_start > setting->mario_untouchable_time)
	{
		isInvisible = false;
		untouchable_start = 0;
		untouchable = 0;
	}
	
	//time animate
	if (state != MARIO_STATE_GO_DOWN && state != MARIO_STATE_GO_UP)
	{
		if (GetTickCount64() - kick_start <= setting->mario_ani_kick_time)
		{
			state = MARIO_STATE_KICK;
		}
		else if (GetTickCount64() - attack_start <= 300)
		{
			if (GetTickCount64() - attack_left_start <= 200)
			{
				state = MARIO_STATE_ATTACK_LEFT;
			}
			else if (GetTickCount64() - attack_right_start <= 100)
			{
				state = MARIO_STATE_ATTACK_RIGHT;
			}
			if (GetTickCount64() - attack_left_start > 200 && GetTickCount64() - attack_left_start <= 300)
			{
				SetState(MARIO_STATE_ATTACK_RIGHT);
			}
			else
			{
				SetState(MARIO_STATE_ATTACK_LEFT);
			}
		}
		else if (GetTickCount64() - slow_falling_start <= setting->mario_ani_slow_falling_time)
		{
			state = MARIO_STATE_SLOW_FALLING;
		}
		else if (GetTickCount64() - fly_falling_start <= setting->mario_ani_fly_falling_time)
		{
			state = MARIO_STATE_FLYING;
		}
	}
	
	
	if (IsGoOutOfPipe()) SetState(MARIO_STATE_NORMAL);
	if (state == MARIO_STATE_DIE)
	{
		float cx, cy;
		game->GetCamPos(cx, cy);
		if (y > cy + game->GetBackBufferHeight())
			DeadImmediately();
	}
	isOnPlatform = false;
	isBlockedLeftRight = false;
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
		if (e->ny < 0)
		{
			isOnPlatform = true;
			ay = setting->mario_gravity;
			current_point = 0;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		isBlockedLeftRight = true;
		switch (state) //handle collison with object blocking nx to smother
		{
		case MARIO_STATE_RUNNING_LEFT: case MARIO_STATE_WALKING_LEFT:
			SetState(MARIO_STATE_WALKING_LEFT);
			vx = -0.01f;
			break;
		case MARIO_STATE_RUNNING_RIGHT: case MARIO_STATE_WALKING_RIGHT:
			SetState(MARIO_STATE_WALKING_RIGHT);
			vx = 0.01f;
			break;
		}
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CDeadzone*>(e->obj))
		OnCollisionWithDeadzone(e);
	else if (dynamic_cast<CPipe*>(e->obj))
		OnCollisionWithPipe(e);
	else if (dynamic_cast<CPause*>(e->obj))
		OnCollisionWithPause(e);
}

void CMario::StartUntouchable()
{
	untouchable = 1; 
	untouchable_start = GetTickCount64();
	invisible_start = GetTickCount64();
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (e->ny > 0)
	{
		if (brick->GetState() != BRICK_STATE_BBRICK)
		{
			if (brick->IsNoItem() && brick->GetState() != BRICK_STATE_BOUNCE) //if brick doesnt have item it is normal brick so dont need to check normal brick
			{
				if (level == MARIO_LEVEL_SMALL)
				{
					brick->SetUpTimesLeftToBounce();
					brick->SetState(BRICK_STATE_BOUNCE);
				}
				else if (level >= MARIO_LEVEL_BIG)
				{
					brick->SetState(BRICK_STATE_BREAK);
					//brick->SetState(BRICK_STATE_BOUNCE);
				}
			}
			else if (brick->GetState() != BRICK_STATE_BOUNCE)
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
			IncreaseMultiPoint();
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_BOUNCE_DIE)
			{
				Hitted();
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	LPGAME game = CGame::GetInstance();

	if (e->ny < 0) //jump on top koopa
	{
		if (koopa->GetState() != KOOPA_STATE_BOUNCE_DIE)
		{
			IncreaseMultiPoint();
			if (koopa->HasWing())
			{
				vy = -setting->mario_jump_deflect_speed;
				koopa->LostWing(); //lost wing if koopa has wing
			}
			else if (koopa->GetState() == KOOPA_STATE_SHIELD_ROLLING_LEFT ||
				koopa->GetState() == KOOPA_STATE_SHIELD_ROLLING_RIGHT) //if shield koopa is rolling, it will stop
			{
				vy = -setting->mario_jump_deflect_speed;
				koopa->SetState(KOOPA_STATE_SHIELD_IDLE);
			}
			else if (koopa->GetState() == KOOPA_STATE_SHIELD_IDLE) //kick shield koopa to roll
			{
				float x_koopa, y_koopa;
				koopa->GetPosition(x_koopa, y_koopa);
				if (x > x_koopa) koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_LEFT);
				else koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_RIGHT);
			}
			else if (koopa->GetTypeShield() == NO_SHIELD)// normal koopa will change state to shield
			{
				vy = -setting->mario_jump_deflect_speed;
				koopa->SetTypeShield(SHIELD_DOWN);
				koopa->SetState(KOOPA_STATE_SHIELD_IDLE);
			}
		}
	}
	else //hit koopa from left, right, bottom
	{
		if (koopa->GetState() == KOOPA_STATE_SHIELD_IDLE || koopa->GetState() == KOOPA_STATE_SHIELD_STANDING) //idle shield will roll
		{
			if (game->IsKeyDown(DIK_A) && isCarryingKoopa == false && e->ny == 0)
			{
				isCarryingKoopa = true;
				this->koopa = koopa;
				koopa->Carried();
			}
			else
			{
				float x_koopa, y_koopa;
				koopa->GetPosition(x_koopa, y_koopa);
				SetState(MARIO_STATE_KICK);
				if (x < x_koopa) koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_RIGHT);
				else koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_LEFT);
			}
		}
		else if (untouchable == 0) //hit by koopa
		{
			if (koopa->GetState() != KOOPA_STATE_BOUNCE_DIE)
			{
				Hitted();
			}
		}
	}
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranhaPlant = dynamic_cast<CPiranhaPlant*>(e->obj);
	if (untouchable == 0)
	{
		if (piranhaPlant->GetState() != PIRANHA_PLANT_STATE_IDLE) Hitted();
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CGame::GetInstance()->IncreaseCoin();
	CGame::GetInstance()->IncreasePoint(50);

}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (mushroom->GetType() == RMUSHROOM)
	{
		SetLevel(MARIO_LEVEL_BIG);
		CGame::GetInstance()->IncreasePoint(setting->mushroom_point);
	}
	else if (mushroom->GetType() == GMUSHROOM) 
	{
		CGame::GetInstance()->LifeUp(setting->mushroom_life_up);
	}
	e->obj->Delete();
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	if (state == MARIO_STATE_GO_DOWN || state == MARIO_STATE_GO_UP) //only switch scene when mario go through pipe
	{
		CPortal* p = (CPortal*)e->obj;
		CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
	}
}

void CMario::OnCollisionWithDeadzone(LPCOLLISIONEVENT e)
{
	DebugOut(L">>> Mario DIE by DEADZONE>>>\n");
	DeadImmediately();
}

void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e)
{
	CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
	LPGAME game = CGame::GetInstance();
	float left, right;
	pipe->GetZoneToGoThrough(left, right);
	if (e->ny < 0 && game->IsKeyDown(DIK_DOWN) && x >= left && x + setting->mario_width <= right)
	{
		game->SetMarioGoThroughPipe(true);
		SetState(MARIO_STATE_GO_DOWN);
		pipe->SetNoBlocking();
	}
	else if (e->ny > 0 && game->IsKeyDown(DIK_UP) && x >= left && x + setting->mario_width <= right)
	{
		game->SetMarioGoThroughPipe(true);
		SetState(MARIO_STATE_GO_UP); 
		pipe->SetNoBlocking();
	}
}

void CMario::OnCollisionWithPause(LPCOLLISIONEVENT e)
{
	CPause* pause = dynamic_cast<CPause*>(e->obj);
	
	if (e->ny < 0)
	{
		pause->SetState(PAUSE_STATE_BE_HITTED);
	}
}

void CMario::Dead()
{
	SetState(MARIO_STATE_DIE);
	//DeadImmediately();
}

void CMario::DeadImmediately()
{
	CGame::GetInstance()->StopPause();
	CGame::GetInstance()->LifeDown();
	CGame::GetInstance()->ReloadScene();
}

bool CMario::IsGoOutOfPipe()
{
	if ((state == MARIO_STATE_GO_DOWN && y >= initY + setting->pipe_height) || (state == MARIO_STATE_GO_UP && y < initY - height))
	{
		return true;
	}
	return false;
}

void CMario::KickKoopa()
{
	SetState(MARIO_STATE_KICK);
	if (nx < 0)
	{
		koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_LEFT);
	}
	else
	{
		koopa->SetState(KOOPA_STATE_SHIELD_ROLLING_RIGHT);
	}
	koopa = NULL;
	isCarryingKoopa = false;
}

void CMario::NoCarryKoopa()
{
	CKoopa* coKoopa = (CKoopa*)koopa;
	isCarryingKoopa = false; 
	coKoopa->NoCarried(); 
	koopa = NULL;
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (!isCarryingKoopa)
		{
			if (abs(ax) == setting->mario_accel_run_x && currentPower == maxPower)
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
		{
			if (nx >= 0) aniId = setting->id_ani_mario_small_carry_jump_right;
			else aniId = setting->id_ani_mario_small_carry_jump_left;
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
				if (!isCarryingKoopa)
				{
					if (nx > 0) aniId = setting->id_ani_mario_small_idle_right;
					else aniId = setting->id_ani_mario_small_idle_left;
				}
				else
				{
					if (nx > 0) aniId = setting->id_ani_mario_small_carry_idle_right;
					else aniId = setting->id_ani_mario_small_carry_idle_left;
				}
			}
			else if (vx > 0)
			{
				if (!isCarryingKoopa)
				{
					if (ax < 0) aniId = setting->id_ani_mario_small_brace_right;
					else if (ax == setting->mario_accel_run_x && currentPower == maxPower) aniId = setting->id_ani_mario_small_running_right;
					else aniId = setting->id_ani_mario_small_walking_right;
				}
				else
				{
					if (ax < 0) aniId = setting->id_ani_mario_small_carry_walking_left;
					else aniId = setting->id_ani_mario_small_carry_walking_right;
				}
			}
			else // vx < 0
			{
				if (!isCarryingKoopa)
				{
					if (ax > 0) aniId = setting->id_ani_mario_small_brace_left;
					else if (ax == -setting->mario_accel_run_x && currentPower == maxPower) aniId = setting->id_ani_mario_small_running_left;
					else aniId = setting->id_ani_mario_small_walking_left;
				}
				else
				{
					if (ax < 0) aniId = setting->id_ani_mario_small_carry_walking_left;
					else aniId = setting->id_ani_mario_small_carry_walking_right;
				}
			}
	if (state == MARIO_STATE_KICK)
	{
		if (nx < 0) aniId = setting->id_ani_mario_small_kick_left;
		else aniId = setting->id_ani_mario_small_kick_right;
	}
	else if (state == MARIO_STATE_GO_DOWN || state == MARIO_STATE_GO_UP) aniId = setting->id_ani_mario_small_tele;

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
		if (!isCarryingKoopa)
		{
			if (abs(ax) == setting->mario_accel_run_x && currentPower == maxPower)
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
		else //carry koopa
		{
			if (nx >= 0) aniId = setting->id_ani_mario_carry_jump_right;
			else aniId = setting->id_ani_mario_carry_jump_left;
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
				if (!isCarryingKoopa)
				{
					if (nx > 0) aniId = setting->id_ani_mario_idle_right;
					else aniId = setting->id_ani_mario_idle_left;
				}
				else  //carry koopa
				{
					if (nx > 0) aniId = setting->id_ani_mario_carry_idle_right;
					else aniId = setting->id_ani_mario_carry_idle_left;
				}
			}
			else if (vx > 0)
			{
				if (!isCarryingKoopa)
				{
					if (ax < 0) aniId = setting->id_ani_mario_brace_right;
					else if (ax == setting->mario_accel_run_x && currentPower == maxPower) aniId = setting->id_ani_mario_running_right;
					else aniId = setting->id_ani_mario_walking_right;
				}
				else  //carry koopa
				{
					if (ax > 0) aniId = setting->id_ani_mario_carry_walking_right;
					else aniId = setting->id_ani_mario_carry_walking_left;
				}
			}
			else // vx < 0
			{
				if (!isCarryingKoopa)
				{
					if (ax > 0) aniId = setting->id_ani_mario_brace_left;
					else if (ax == -setting->mario_accel_run_x && currentPower == maxPower) aniId = setting->id_ani_mario_running_left;
					else aniId = setting->id_ani_mario_walking_left;
				}
				else  //carry koopa
				{
					if (ax < 0) aniId = setting->id_ani_mario_carry_walking_left;
					else aniId = setting->id_ani_mario_carry_walking_right;
				}
			}
	if (state == MARIO_STATE_KICK)
	{
		if (nx < 0) aniId = setting->id_ani_mario_kick_left;
		else aniId = setting->id_ani_mario_kick_right;
	}
	else if (state == MARIO_STATE_GO_DOWN || state == MARIO_STATE_GO_UP) aniId = setting->id_ani_mario_tele;
	if (aniId == -1) aniId = setting->id_ani_mario_idle_right;;

	return aniId;
}

//
// Get animdation ID for raccoon Mario
//
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (!isCarryingKoopa)
		{
			if (currentPower == maxPower)
			{
				if (vy <= 0)
				{
					if (nx >= 0) aniId = setting->id_ani_raccoon_jump_run_right;
					else aniId = setting->id_ani_raccoon_jump_run_left;
				}
				else
				{
					if (nx >= 0) aniId = setting->id_ani_raccoon_fly_falling_right;
					else aniId = setting->id_ani_raccoon_fly_falling_left;
				}
			}
			else
			{
				if (vy <= 0)
				{
					if (nx >= 0) aniId = setting->id_ani_raccoon_jump_walk_right;
					else aniId = setting->id_ani_raccoon_jump_walk_left;
				}
				else
				{
					if (nx >= 0) aniId = setting->id_ani_raccoon_free_falling_right;
					else aniId = setting->id_ani_raccoon_free_falling_left;
				}
			}
		}
		else //carry koopa
		{
			if (nx >= 0) aniId = setting->id_ani_raccoon_carry_jump_right;
			else aniId = setting->id_ani_raccoon_carry_jump_left;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0) aniId = setting->id_ani_raccoon_sit_right;
			else aniId = setting->id_ani_raccoon_sit_left;
		}
		else
			if (vx == 0)
			{
				if (!isCarryingKoopa)
				{
					if (nx > 0) aniId = setting->id_ani_raccoon_idle_right;
					else aniId = setting->id_ani_raccoon_idle_left;
				}
				else  //carry koopa
				{
					if (nx > 0) aniId = setting->id_ani_raccoon_carry_idle_right;
					else aniId = setting->id_ani_raccoon_carry_idle_left;
				}
			}
			else if (vx > 0)
			{
				if (!isCarryingKoopa)
				{
					if (ax < 0) aniId = setting->id_ani_raccoon_brace_right;
					else if (ax == setting->mario_accel_run_x && currentPower == maxPower) aniId = setting->id_ani_raccoon_running_right;
					else aniId = setting->id_ani_raccoon_walking_right;
				}
				else  //carry koopa
				{
					if (ax > 0) aniId = setting->id_ani_raccoon_carry_walking_right;
					else aniId = setting->id_ani_raccoon_carry_walking_left;
				}
			}
			else // vx < 0
			{
				if (!isCarryingKoopa)
				{
					if (ax > 0) aniId = setting->id_ani_raccoon_brace_left;
					else if (ax == -setting->mario_accel_run_x && currentPower == maxPower) aniId = setting->id_ani_raccoon_running_left;
					else aniId = setting->id_ani_raccoon_walking_left;
				}
				else  //carry koopa
				{
					if (ax < 0) aniId = setting->id_ani_raccoon_carry_walking_left;
					else aniId = setting->id_ani_raccoon_carry_walking_right;
				}
			}
	if (state == MARIO_STATE_KICK)
	{
		if (nx < 0) aniId = setting->id_ani_raccoon_kick_left;
		else aniId = setting->id_ani_raccoon_kick_right;
	}
	else if (state == MARIO_STATE_GO_DOWN || state == MARIO_STATE_GO_UP) aniId = setting->id_ani_raccoon_tele;
	else if (state == MARIO_STATE_SLOW_FALLING)
	{
		if (nx > 0) aniId = setting->id_ani_raccoon_slow_falling_right;
		else aniId = setting->id_ani_raccoon_slow_falling_left;
	}
	else if (state == MARIO_STATE_FLYING)
	{
		if (nx > 0) aniId = setting->id_ani_raccoon_flying_right;
		else aniId = setting->id_ani_raccoon_flying_left;
	}
	else if (state == MARIO_STATE_ATTACK_LEFT) aniId = setting->id_ani_raccoon_attack_left;
	else if (state == MARIO_STATE_ATTACK_RIGHT) aniId = setting->id_ani_raccoon_attack_right;
	if (aniId == -1) aniId = setting->id_ani_raccoon_idle_right;;

	return aniId;
}


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
	{
		aniId = setting->id_ani_mario_die;
		DebugOut(L"die!!!\n");
	}
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	if (!isInvisible)
	{
		if (level == MARIO_LEVEL_RACCOON)
		{
			if (nx > 0)
			{
				if (aniId == setting->id_ani_raccoon_brace_left)
				{
					animations->Get(aniId)->Render(x - 7, y - 2);
				}
				else if (aniId == setting->id_ani_raccoon_attack_right)
				{
					animations->Get(aniId)->Render(x - 7, y );
				}
				else
				{
					if (aniId == setting->id_ani_raccoon_attack_left) animations->Get(aniId)->Render(x, y);
					else animations->Get(aniId)->Render(x - 7, y);
				}
			}
			else
			{
				if (aniId == setting->id_ani_raccoon_brace_right)
				{
					animations->Get(aniId)->Render(x, y - 2);
				}
				else if (aniId == setting->id_ani_raccoon_attack_right)
				{
					animations->Get(aniId)->Render(x - 7, y);
				}
				else
				{
					animations->Get(aniId)->Render(x, y);
				}
			}
		}
		else
		{
			animations->Get(aniId)->Render(x, y);
		}
	}
	else
	{
		animations->Get(setting->id_ani_mario_invisible)->Render(x, y);
	}
	//RenderBoundingBox();
}

//logic
void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! //Go up, go down -> change scene
	if (this->state == MARIO_STATE_DIE || this->state == MARIO_STATE_GO_UP || this->state == MARIO_STATE_GO_DOWN) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = setting->mario_running_speed;
		avgVx = setting->mario_average_speed;
		ax = setting->mario_accel_run_x;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -setting->mario_running_speed;
		avgVx = -setting->mario_average_speed;
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
			if (currentPower >= maxPower)
			{
				if (level == MARIO_LEVEL_RACCOON)
				{
					flying_start = GetTickCount64();
				}
				vy = -setting->mario_jump_run_speed_y;
			}
			else
				vy = -setting->mario_jump_speed_y;
		}
		else if (!isOnPlatform && level == MARIO_LEVEL_RACCOON)
		{
			if (currentPower < maxPower)
			{
				SetState(MARIO_STATE_SLOW_FALLING);
			}
			else
			{
				SetState(MARIO_STATE_FLYING);
			}
		}
		break;
	case MARIO_STATE_SLOW_FALLING:
		vy = 0.05f;
		ay = 0;
		slow_falling_start = GetTickCount64();
		break;
	case MARIO_STATE_FLYING:
		ay = 0;
		vy = -0.075f;
		fly_falling_start = GetTickCount64();
		break;
	case MARIO_STATE_ATTACK:
		if (nx < 0) SetState(MARIO_STATE_ATTACK_LEFT);
		else SetState(MARIO_STATE_ATTACK_RIGHT);
		attack_start = GetTickCount64();
		return;
	case MARIO_STATE_ATTACK_LEFT: 
		attack_left_start = GetTickCount64();
		break;
	case MARIO_STATE_ATTACK_RIGHT:
		DebugOut(L"attack right\n");
		attack_right_start = GetTickCount64();
		break;
	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0)
		{
			if (level != MARIO_LEVEL_RACCOON || (level == MARIO_LEVEL_RACCOON && currentPower != maxPower))
			{
				vy += setting->mario_jump_speed_y / 2;
			}
		}
		break;
	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += (setting->mario_big_height - setting->mario_sitting_height);
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= (setting->mario_big_height - setting->mario_sitting_height);
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_KICK:
		kick_start = GetTickCount64();
		break;
	case MARIO_STATE_DIE:
		SetState(MARIO_STATE_NORMAL); //we need to set all is normal before die
		vy = -setting->mario_jump_deflect_speed;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_GO_DOWN:
		vx = 0;
		ax = 0;
		vy = setting->mario_tele_speed;
		ay = 0;
		isBlockingKeyboard = true;
		break;
	case MARIO_STATE_GO_UP:
		vx = 0;
		ax = 0;
		vy = -setting->mario_tele_speed;
		ay = 0;
		isBlockingKeyboard = true;
		break;
	case MARIO_STATE_NORMAL:
		isBlockingKeyboard = false;
		isSitting = false;
		CGame::GetInstance()->SetMarioGoThroughPipe(false);
		if (isCarryingKoopa) NoCarryKoopa();
		ay = setting->mario_gravity;
		return;
	}
	//if (state == MARIO_STATE_DIE) DebugOut(L"die here!!!\n");
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACCOON)
	{
		if (isSitting)
		{
			right = left + setting->mario_width - 1;
			bottom = top + setting->mario_sitting_height - 1;
		}
		else
		{
			right = left + setting->mario_width - 1;
			bottom = top + setting->mario_big_height - 1;
		}
	}
	else
	{
		right = left + setting->mario_width - 1;
		bottom = top + setting->mario_small_height - 1;
	}
}

void CMario::SetLevel(int level)
{
	//current level
	switch (this->level)
	{
	case MARIO_LEVEL_SMALL:
		y -= (setting->mario_big_height - setting->mario_small_height);
		break;
	case MARIO_LEVEL_BIG:
		break;
	case MARIO_LEVEL_RACCOON:
		break;
	}

	//next level
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		height = setting->mario_small_height;
		break;
	case MARIO_LEVEL_BIG:
		height = setting->mario_big_height;
		break;
	case MARIO_LEVEL_RACCOON:
		height = setting->mario_big_height;
		break;
	}
	this->level = level;
	CGame::GetInstance()->SetLevel(level);
}

void CMario::IncreaseMultiPoint()
{
	if (current_point <= 7) CGame::GetInstance()->IncreasePoint(points_in_level[current_point]);
	else CGame::GetInstance()->LifeUp(1);
	current_point++;
}

void CMario::Hitted()
{
	if (level > MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_BIG);
		StartUntouchable();
	}
	else if (level > MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_SMALL);
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		Dead();
	}
}

