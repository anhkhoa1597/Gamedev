#include "Pipe.h"

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width - 1;
	b = t + height - 1;
}