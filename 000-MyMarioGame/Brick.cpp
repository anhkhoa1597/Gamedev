#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}

void CBrick::Get(float& x, float& y, int& width, int& height)
{
	x = this->x;
	y = this->y;
	width = this->width;
	height = this->height;
}