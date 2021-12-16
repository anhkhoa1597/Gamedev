#include "HeadUpDisplay.h"

using namespace std;

CHud::CHud(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	world = 1;
	life = vector<unsigned int>(2, 0);
	point = vector<unsigned int>(7, 0);
	coin = vector<unsigned int>(2, 0);
	time = vector<unsigned int>(3, 0);
	currentPower = 0;
	maxPower = setting->mario_max_power;
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
	int x_adjust = (game->GetBackBufferWidth() - setting->hud_width) / 2;
	float translationX = (float)(rect.right + 1) / 2;
	float translationY = (float)(rect.bottom + 1) / 2;
	CGame::GetInstance()->Draw(x - cx + translationX - x_adjust, y - cy + translationY, hudBackground, rect.left, rect.top, rect.right, rect.bottom, 1.0f);
}

void CHud::Render()
{
	RenderBackground();
	CAnimations::GetInstance()->Get(setting->id_ani_hud)->Render(x, y);
	RenderCoin();
	RenderPoint();
	RenderLife();
	RenderTime();
	RenderPowerMeter();
	CSprites::GetInstance()->Get(setting->sprite_id_hud_and_font + world)->Draw(x + setting->font_world_x, y + setting->font_world_y);
}

void CHud::RenderTime()
{
	for (int i = 0; i < time.size(); i++)
	{
		CSprites::GetInstance()->Get(setting->sprite_id_hud_and_font + time[i])->Draw(x + setting->font_time_x + i * setting->font_width, y + setting->font_time_y);
 	}
}

void CHud::RenderPoint()
{
	for (int i = 0; i < point.size(); i++)
	{
		CSprites::GetInstance()->Get(setting->sprite_id_hud_and_font + point[i])->Draw(x + setting->font_point_x + i * setting->font_width, y + setting->font_point_y);
	}
}

void CHud::RenderCoin()
{
	for (int i = 0; i < coin.size(); i++)
	{
		CSprites::GetInstance()->Get(setting->sprite_id_hud_and_font + coin[i])->Draw(x + setting->font_coin_x + i * setting->font_width, y + setting->font_coin_y);
	}
}

void CHud::RenderLife()
{
	for (int i = 0; i < life.size(); i++)
	{
		CSprites::GetInstance()->Get(setting->sprite_id_hud_and_font + life[i])->Draw(x + setting->font_life_x + i * setting->font_width, y + setting->font_life_y);
	}
}

void CHud::RenderPowerMeter()
{
	for (unsigned int i = 0; i < maxPower - 1; i++)
	{
		if (i >= currentPower)
		{
			CSprites::GetInstance()->Get(setting->sprite_id_font_power_meter_normal)->Draw(x + setting->font_power_meter_x + i * setting->font_width, y + setting->font_power_meter_y);
		}
		else
		{
			CSprites::GetInstance()->Get(setting->sprite_id_font_power_meter_running)->Draw(x + setting->font_power_meter_x + i * setting->font_width, y + setting->font_power_meter_y);
		}
	}
	if (currentPower != maxPower)
	{
		CSprites::GetInstance()->Get(setting->sprite_id_font_power_meter_p_normal)->Draw(x + setting->font_power_meter_x + (maxPower - 1) * setting->font_width, y + setting->font_power_meter_y);
	}
	else
	{
		CAnimations::GetInstance()->Get(setting->id_font_power_meter_p_running)->Render(x + setting->font_power_meter_x + (maxPower - 1) * setting->font_width, y + setting->font_power_meter_y);
	}
}

void CHud::Update()
{
	float x_cam, y_cam;
	int x_adjust = (CGame::GetInstance()->GetBackBufferWidth() - width) / 2;
	LPGAME game = CGame::GetInstance();
	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	UpdateCoin(game->GetCoin());
	UpdateTime(game->GetTime());
	UpdatePoint(game->GetPoint());
	UpdateLife(game->GetLife());
	game->GetCamPos(x_cam, y_cam);
	x = x_cam + x_adjust;
	//x = x_cam;
	y = y_cam + CGame::GetInstance()->GetBackBufferHeight() - height;
}

void CHud::UpdateCoin(unsigned int coin)
{
	int size_coin = (int)this->coin.size();
	for (int i = 0; i < size_coin; i++)
	{
		int m = (int)pow(10, size_coin - i - 1);
		this->coin[i] = (coin / m) % 10;
	}
}

void CHud::UpdateTime(int time)
{
	int size_time = (int)this->time.size();
	for (int i = 0; i < size_time; i++)
	{
		int m = (int)pow(10, size_time - i - 1);
		this->time[i] = (time / m) % 10;
	}
}

void CHud::UpdatePoint(unsigned int point)
{
	int size_point = (int)this->point.size();
	for (int i = 0; i < size_point; i++)
	{
		int m = (int)pow(10, size_point - i - 1);
		this->point[i] = (point / m) % 10;
	}
}

void CHud::UpdateLife(unsigned int life)
{
	int size_life = (int)this->life.size();
	for (int i = 0; i < size_life; i++)
	{
		int m = (int)pow(10, size_life - i - 1);
		this->life[i] = (life / m) % 10;
	}
}
