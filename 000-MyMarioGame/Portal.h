#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	int width;
	int height;

	float x_mario;
	float y_mario;
	int state_mario;
public:
	CPortal(float x, float y, int width, int height, int scene_id, float x_mario, float y_mario, int state_mario);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetMarioInNextScene();
	int GetSceneId() { return scene_id; }
	int IsBlocking() { return 0; }
};