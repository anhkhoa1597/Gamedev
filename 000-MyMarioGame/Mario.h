#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "DCoin.h"
#include "Mushroom.h"
#include "Portal.h"

#include "Collision.h"
#include "debug.h"

enum MarioLevels
{
	MARIO_LEVEL_SMALL,
	MARIO_LEVEL_BIG,
	MARIO_LEVEL_FIRE,
	MARIO_LEVEL_FOX,
	MARIO_LEVEL_BEAR,
	MARIO_LEVEL_FROG,
	MARIO_LEVEL_TURTLE
};

enum MarioStates
{
	MARIO_STATE_DIE,
	MARIO_STATE_IDLE,
	MARIO_STATE_WALKING_RIGHT,
	MARIO_STATE_WALKING_LEFT,

	MARIO_STATE_JUMP,
	MARIO_STATE_RELEASE_JUMP,

	MARIO_STATE_RUNNING_RIGHT,
	MARIO_STATE_RUNNING_LEFT,

	MARIO_STATE_SIT,
	MARIO_STATE_SIT_RELEASE,
};

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 401
#define ID_ANI_MARIO_IDLE_LEFT 400

#define ID_ANI_MARIO_WALKING_RIGHT 501
#define ID_ANI_MARIO_WALKING_LEFT 500

#define ID_ANI_MARIO_RUNNING_RIGHT 601
#define ID_ANI_MARIO_RUNNING_LEFT 600

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 701
#define ID_ANI_MARIO_JUMP_WALK_LEFT 700

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 801
#define ID_ANI_MARIO_JUMP_RUN_LEFT 800

#define ID_ANI_MARIO_SIT_RIGHT 901
#define ID_ANI_MARIO_SIT_LEFT 900

#define ID_ANI_MARIO_BRACE_RIGHT 1001
#define ID_ANI_MARIO_BRACE_LEFT 1000

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1101
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1100

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1201
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1200

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1301
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1300

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1401
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1400

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1501
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1500

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1601
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1600

#define ID_ANI_MARIO_SMALL_TO_BIG_LEFT 1700
#define ID_ANI_MARIO_SMALL_TO_BIG_RIGHT 1701
#pragma endregion

//global variable
//extern float	mario_walking_speed, mario_running_speed, 
//				mario_accel_walk_x, mario_accel_run_x, 
//				mario_jump_speed_y, mario_jump_run_speed_y, 
//				mario_gravity, mario_jump_deflect_speed,
//				mario_untouchable_time;
//extern int		mario_life;
//
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_UNTOUCHABLE_TIME 2500

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 18

#define MARIO_SMALL_BBOX_WIDTH  14
#define MARIO_SMALL_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST (MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITTING_BBOX_HEIGHT)
#define MARIO_CHANGE_LEVEL_HEIGHT_ADJUST (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT)

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int life;
	int untouchable; 
	ULONGLONG untouchable_start;

	BOOLEAN isOnPlatform;
	int coin;

	//float startX, startY, checkPointX, checkPointY;

	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();

public:
	CMario(float x, float y) : CGameObject(x, y, true)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;

		isOnPlatform = false;
		coin = 0;
		life = 3;

	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void SetLevel(int l);
	void IncreaseCoin() { coin++; }
	void LifeUp(int life) { this->life += life; }

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};