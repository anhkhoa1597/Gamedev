#pragma once
#include "GameObject.h"
#include "Textures.h"

class CHud
{
	float x;
	float y;
	int width;
	int height;
	LPGAMESETTING setting = CGameSetting::GetInstance();
public:
	CHud(float x, float y, int width, int height);
	int GetHeight() { return height; }
	void RenderBackground();
	void Render();
	void Update();
}; typedef CHud* LPHUD;