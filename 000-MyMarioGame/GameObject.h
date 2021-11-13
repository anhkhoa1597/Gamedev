#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include "GameSetting.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Collision.h"


using namespace std;

enum TypeObject
{
	MARIO,
	GOOMBA, //normal goomba
	WGOOMBA, //wing normal goomba
	RGOOMBA, //red goomba
	RWGOOMBA, //red wing goomba
	KOOPA, //normal koopa
	WKOOPA, //wing normal koopa
	RKOOPA, //red koopa
	RWKOOPA, //red wing koopa
	RMUSHROOM, //red mushroom
	GMUSHROOM, //green mushroom
	COIN, //visible coin
	DCOIN, //drop coin
	MCOIN, //multi coin
	BRICK, //normal brick
	QBRICK, //question brick
	SBRICK, //specific brick
	SECRET_BRICK, //invisible brick
	WALL,
	GROUND,
	SPLATFORM, //the platform can walk through
	PIPE,
	DEADZONE,
	BBRICK, //block brick
	PLATFORM, //not need to use yet:)
	HUD,
	PAUSE,
};

class CGameObject
{
protected:
	int type;
	float initX;
	float initY;
	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 

	int state;

	bool isDeleted;
	bool isArchived = false;
	bool isEnemyCreated = false;
	
	bool isEnemy = false;
	bool isPlayer = false;
	LPGAMESETTING setting = CGameSetting::GetInstance();
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetInitPosition(float& initX, float& initY) { initX = this->initX; initY = this->initY; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	bool IsArchived() { return isArchived; }
	void Archive() { isArchived = true; }
	void Unarchive() { isArchived = false; }

	int GetState() { return this->state; }
	int GetType() { return this->type; }
	virtual void Delete() { isDeleted = true;  }
	bool IsDeleted() { return isDeleted; }
	bool IsEnemies() { return isEnemy; }
	bool IsEnemyCreated() { return isEnemyCreated; }
	void SetEnemyCreate(bool isEnemyCreated) { this->isEnemyCreated = isEnemyCreated; }
	bool IsSameObject(LPGAMEOBJECT otherObj)
	{
		float x, y;
		int type = otherObj->GetType();
		otherObj->GetInitPosition(x, y);
		if (this->x == x && this->y == y && this->type == type) return true;
		return false;
	}
	bool IsInCamera(float l, float t, float r, float b) 
	{ 
		if (x >= l - 16 && x <= r + 16 && y >= t - 16 && y <= b + 16) return true;
		else return false; 
	}
	void RenderBoundingBox();

	CGameObject();
	CGameObject(float x, float y, int type) :CGameObject() 
	{ 
		this->x = x; 
		this->y = y;
		initX = x;
		initY = y;
		this->type = type; 
	}

	bool IsPlayer() { return isPlayer; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void SetLevel(int level) {}
	
	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) { l = 1; t = 1; r = 1; b = 1; }
	virtual void ObjectNoBlocking(vector<unsigned int>& typeObjects) { typeObjects = {}; }
	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }
};
