#include "HeadUpDisplay.h"

CHud::CHud(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void CHud::RenderBackground()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect{};
	LPGAME game = CGame::GetInstance();
	LPTEXTURE hudBackground = CTextures::GetInstance()->Get(setting->id_tex_hud_background);

	rect.left = 0;
	rect.top = 0;
	rect.right = game->GetBackBufferWidth();
	rect.bottom = height;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	float x_adjust = (game->GetBackBufferWidth() - setting->hud_width) / 2;
	float translationX = (float)(rect.right + 1) / 2;
	float translationY = (float)(rect.bottom + 1) / 2;
	CGame::GetInstance()->Draw(x - cx + translationX - x_adjust, y - cy + translationY, hudBackground, rect.left, rect.top, rect.right, rect.bottom, 1.0f);
}

void CHud::Render()
{
	RenderBackground();
	CAnimations::GetInstance()->Get(setting->id_ani_hud)->Render(x, y);
}

void CHud::Update()
{
	float x_cam, y_cam;
	float x_adjust = (CGame::GetInstance()->GetBackBufferWidth() - setting->hud_width) / 2;
	CGame::GetInstance()->GetCamPos(x_cam, y_cam);
	x = x_cam + x_adjust;
	//x = x_cam;
	y = y_cam + CGame::GetInstance()->GetBackBufferHeight() - height;
}
