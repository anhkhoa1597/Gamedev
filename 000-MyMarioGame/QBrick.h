#pragma once
#include "Brick.h"

#define ID_ANI_QBRICK 10200
#define ID_ANI_BBrick 10300

#define BRICK_STATE_QBRICK 100
#define BRICK_STATE_BBRICK 200

#define BRICK_BOUNCING_SPEED 0.2f
#define BRICK_BOUNCE_HEIGHT 12

class QBrick : public CBrick {
	float initialPositionY;
	//string item;
public:
	QBrick(float x, float y, int width, int height);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
};