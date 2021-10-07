#include "Brick.h"

void CBrick::Render()
{
	//CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(ID_ANI_BRICK)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}