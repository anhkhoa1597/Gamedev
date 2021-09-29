#include "Game.h"
#include "Goomba.h"

CGoomba::CGoomba(float x, float y, float vx) :CGameObject(x, y)
{
	this->vx = vx;
	//status = 0: walk left
	//status = 1: walk right
	status = 0;
};

void CGoomba::Update(DWORD dt)
{
	x += vx * dt;
	float middleOfGoomba = GOOMBA_WIDTH / 2;
	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= middleOfGoomba || x >= BackBufferWidth - middleOfGoomba) {
		vx = -vx;
		if (x <= middleOfGoomba)
		{
			status = 1;
			x = middleOfGoomba;
		}
		else if (x >= BackBufferWidth - middleOfGoomba)
		{
			status = 0;
			x = (float)(BackBufferWidth - middleOfGoomba);
		}
	}
}

void CGoomba::Render()
{
	LPANIMATION ani;
	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Goomba!!
	switch (status)
	{
	default:
		ani = CAnimations::GetInstance()->Get(ID_GOOMBA_WALK);
		break;
	//case 0:
	//	ani = CAnimations::GetInstance()->Get(ID_GOOMBA_WALK_LEFT);
	//	break;
	//case 1:
	//	ani = CAnimations::GetInstance()->Get(ID_GOOMBA_WALK_RIGHT);
	//	break;
	}
	ani->Render(x, y);
}