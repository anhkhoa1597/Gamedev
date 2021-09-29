#include "Game.h"
#include "Mario.h"

CMario::CMario(float x, float y, float vx):CGameObject(x, y)
{
	this->vx = vx;
};

void CMario::Update(DWORD dt)
{
	x += vx*dt;
	float middleOfMario = MARIO_WIDTH / 2;
	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= middleOfMario || x >= BackBufferWidth - middleOfMario) {

		vx = -vx;

		if (x <= middleOfMario)
		{
			x = middleOfMario;
		}
		else if (x >= BackBufferWidth - middleOfMario)
		{
			x = (float)(BackBufferWidth - middleOfMario);
		}
	}
}

void CMario::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx>0) ani = CAnimations::GetInstance()->Get(500);
	else
	{
		ani = CAnimations::GetInstance()->Get(501);
		//ani->SetSpeedAnimation(0.5);
	}

	ani->Render(x, y);
}

void CBrick::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(510);

	ani->Render(x, y);

}