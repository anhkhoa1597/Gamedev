#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	//translationX = translationY = 0;
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
	isDeleted = false;
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy; 
	CGame::GetInstance()->GetCamPos(cx, cy);

	//translationX, translationY to draw base adjust the coor of boundingbox to the top left corner
	float translationX = (float)rect.right / 2;
	float translationY = (float)rect.bottom / 2;
	CGame::GetInstance()->Draw(x - cx + translationX, y - cy + translationY, bbox, rect.left, rect.top, rect.right, rect.bottom, 0.5f);
}

CGameObject::~CGameObject()
{

}