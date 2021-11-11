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
	float initial_y;
	int height;

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
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return (state != MARIO_STATE_DIE); }
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	bool IsGoOutOfPipe();
	void SetState(int state);
	void SetLevel(int l);
	void Dead();
	void DeadImmediately();
	bool IsBlockingKeyboard() { return isBlockingKeyboard; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
};