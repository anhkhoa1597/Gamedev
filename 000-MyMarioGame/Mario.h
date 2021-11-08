#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameSetting.h"

#include "Goomba.h"
#include "Koopa.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Portal.h"
#include "Deadzone.h"
#include "Pipe.h"

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
	MARIO_STATE_NORMAL,
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

	MARIO_STATE_GO_DOWN,
	MARIO_STATE_GO_UP,
	MARIO_STATE_KICK,
};

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 18

#define MARIO_SMALL_BBOX_WIDTH  14
#define MARIO_SMALL_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST (MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITTING_BBOX_HEIGHT)
#define MARIO_CHANGE_LEVEL_HEIGHT_ADJUST (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT)

#define PIPE_HEIGHT 32
class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	
	bool isBlockingKeyboard;
	int level; 
	int untouchable;
	ULONGLONG untouchable_start;

	BOOLEAN isOnPlatform;
	int height;
	bool isGoThroughPipe;
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithDeadzone(LPCOLLISIONEVENT e);
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();

public:
	CMario(float x, float y);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void SetLevel(int l);
	
	void Dead();
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }
	bool IsBlockingKeyboard() { return isBlockingKeyboard; }
	bool IsGoThroughOutOfPipe();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};