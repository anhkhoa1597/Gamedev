#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

/*
	Initialize game object
*/
CGameObject::CGameObject(float x, float y, LPTEXTURE tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}

void CGameObject::Render(int l, int t, int r, int b)
{
	CGame::GetInstance()->Draw(x, y, texture, l, t, r, b);
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14.0f

#define GOOMBA_VX 0.05f
#define GOOMBA_HEIGHT 16.0f

void CMario::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= MARIO_WIDTH/2 || x >= BackBufferWidth - MARIO_WIDTH/2) {

		vx = -vx;

		if (x <= MARIO_WIDTH / 2)
		{
			x = MARIO_WIDTH / 2;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH/2)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH/2);
		}
	}
}

void CGoomba::Update(DWORD dt)
{
	y += vy * dt;
	if (y <= GOOMBA_HEIGHT /2 || y >= 112 - GOOMBA_HEIGHT/2) {

		vy = -vy;

		if (y <= GOOMBA_HEIGHT /2)
		{
			y = GOOMBA_HEIGHT /2;
		}
		else if (y >= 112 - GOOMBA_HEIGHT /2)
		{
			y = (float)(112 - GOOMBA_HEIGHT /2);
		}
	}
}