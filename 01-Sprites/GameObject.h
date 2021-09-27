#pragma once

#include <Windows.h>
#include <d3dx10.h>

#include "Texture.h"

class CGameObject
{
protected:
	float x;
	float y;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object. 
	// For now, just a pointer to a single texture
	LPTEXTURE texture;

	//int top;
	//int left;
	//int right;
	//int bottom;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	float GetX() { return x; }
	float GetY() { return y; }

	CGameObject(float x = 0.0f, float y = 0.0f, LPTEXTURE texture = NULL);
	//CGameObject(float x = 0.0f, float y = 0.0f, LPTEXTURE texture = NULL, int t = 0, int l = 0, int r = 0, int b = 0);

	virtual void Update(DWORD dt) = 0;
	virtual void Render();

	virtual void Render(int l, int t, int r, int b);

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;

class CBrick : public CGameObject
{
public:
	CBrick(float x, float y, LPTEXTURE texture) : CGameObject(x, y, texture) {}
	void Update(DWORD dt) {};
};

class CMario : public CGameObject
{
	float vx;
	float vy;
public:
	CMario(float x, float y, float vx, float vy, LPTEXTURE texture) :CGameObject(x, y, texture)
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);
};

class CGoomba : public CGameObject
{
	float vx;
	float vy;
public:
	CGoomba(float x, float y, float vx, float vy, LPTEXTURE texture, int t, int l, int r, int b) :CGameObject(x, y, texture)
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);
};