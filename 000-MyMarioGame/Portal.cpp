#include "Portal.h"

CPortal::CPortal(float x, float y, int width, int height, int scene_id, float x_mario, float y_mario, int state_mario)
{
	this->scene_id = scene_id;
	this->width = width;
	this->height = height;
	this->x_mario = x_mario;
	this->y_mario = y_mario;
	this->state_mario = state_mario;
}

void CPortal::SetMarioInNextScene()
{
	LPGAME game = CGame::GetInstance();
	game->SetMario(x_mario, y_mario, state_mario);
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