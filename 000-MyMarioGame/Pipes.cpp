#include "Pipes.h"

void CPipes::Render()
{
	RenderBoundingBox();
}

void CPipes::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + this->width;
	b = t + this->height;
}