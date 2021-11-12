#pragma once
#include "GameObject.h"
#include "Mario.h"
#include <math.h>

using namespace std;

enum PauseStates
{
	PAUSE_STATE_NORMAL,
	PAUSE_STATE_BE_HITTED,
};

class CPause : public CGameObject
{
protected:
	int width;
	int height;
	ULONGLONG pause_start;
	bool isCollidable;
	bool isBlocking;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return isCollidable; }
	int IsBlocking() { return isBlocking; }
public:
	CPause(float x, float y, int width, int height);
	void SetState(int state);
};