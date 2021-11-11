#include "Pipe.h"

CPipe::CPipe(float x, float y, int width, int height) : CGameObject(x, y, PIPE)
{
	this->width = width; 
	this->height = height; 
	isBlockingMario = true;
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}
void CPipe::SetNoBlocking() 
{ 
	isBlockingMario = false; 
}

void CPipe::SetBlocking()
{
	isBlockingMario = true;
}

void CPipe::GetZoneToGoThrough(float& left, float& right)
{
	left = x + setting->pipe_adjust_width_can_go_through;
	right = left + width - 2 * (setting->pipe_adjust_width_can_go_through);
};

void CPipe::ObjectNoBlocking(vector<unsigned int>& type)
{
	if (!isBlockingMario)
		type.push_back(MARIO);
	//isBlockingMario ? type = {} : type = { MARIO };
}

int CPipe::IsBlocking()
{
	return true;
}