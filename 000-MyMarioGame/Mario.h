#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameSetting.h"

#include "Goomba.h"
#include "Koopa.h"
#include "PiranhaPlant.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Portal.h"
#include "Deadzone.h"
#include "Pipe.h"
#include "Tail.h"

#include "Collision.h"
#include "debug.h"

enum MarioLevels
{
	MARIO_LEVEL_SMALL,
	MARIO_LEVEL_BIG,
	MARIO_LEVEL_RACCOON,
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
	MARIO_STATE_SLOW_FALLING,
	MARIO_STATE_FLYING,
	MARIO_STATE_FLY_FALLING,
	MARIO_STATE_RUNNING_RIGHT,
	MARIO_STATE_RUNNING_LEFT,


	MARIO_STATE_SIT,
	MARIO_STATE_SIT_RELEASE,

	MARIO_STATE_GO_DOWN,
	MARIO_STATE_GO_UP,
	MARIO_STATE_KICK,
	MARIO_STATE_ATTACK,
	MARIO_STATE_ATTACK_LEFT,
	MARIO_STATE_ATTACK_RIGHT,

	MARIO_STATE_BRING_IDLE,
	MARIO_STATE_BRING_WALKING_LEFT,
	MARIO_STATE_BRING_WALKING_RIGHT,
};

class CMario : public CGameObject
{
	BOOLEAN isSitting;

	//handle speed of mario
	unsigned int currentPower;
	unsigned int maxPower;
	float maxVx;
	float avgVx; //averageVx base on power
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	int height;

	bool isBlockingKeyboard;
	bool isInvisible;
	int level; 
	int untouchable;

	BOOLEAN isOnPlatform;
	bool isBlockedLeftRight;
	bool isCarryingKoopa;
	LPGAMEOBJECT koopa;

	int current_point = 0;
	vector<int> points_in_level;

	ULONGLONG powerTime_start;
	ULONGLONG untouchable_start;
	ULONGLONG invisible_start;
	ULONGLONG kick_start;
	ULONGLONG slow_falling_start;
	ULONGLONG flying_start;
	ULONGLONG fly_falling_start;
	ULONGLONG attack_start;
	ULONGLONG attack_left_start;
	ULONGLONG attack_right_start;



	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithDeadzone(LPCOLLISIONEVENT e);
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithPause(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdRaccoon();
	int GetAniIdSmall();

public:
	CMario(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return (state != MARIO_STATE_DIE); }
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	bool IsGoOutOfPipe();
	bool IsCarryingKoopa() { return isCarryingKoopa; }
	bool IsBlockedLeftRight() { return isBlockedLeftRight; }
	void NoCarryKoopa();
	void KickKoopa();
	void SetState(int state);
	void SetLevel(int l);
	int GetLevel() { return level; }
	void IncreaseMultiPoint();
	void Hitted();
	void Dead();
	void DeadImmediately();
	bool IsBlockingKeyboard() { return isBlockingKeyboard; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void StartUntouchable();
};