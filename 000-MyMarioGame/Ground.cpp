#include "Ground.h"

void CGround::Render()
{
	//RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + this->width - 1;
	b = t + this->height - 1;
}