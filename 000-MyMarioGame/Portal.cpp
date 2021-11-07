#include "Portal.h"

CPortal::CPortal(float x, float y, int width, int height, int scene_id)
{
	this->scene_id = scene_id;
	this->width = width;
	this->height = height;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}