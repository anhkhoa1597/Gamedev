#pragma once
#include "GameObject.h"
#include "Textures.h"
#include <math.h>

class CHud
{
	float x;
	float y;
	int width;
	int height;

	//int life_dozens, life_unit;
	vector<unsigned int> life;
	vector<unsigned int> point;
	//int coin_dozens, coin_unit;
	vector<unsigned int> coin;
	vector<unsigned int> time;
	unsigned int world;
	LPGAMESETTING setting = CGameSetting::GetInstance();
public:
	CHud(float x, float y, int width, int height);
	int GetHeight() { return height; }
	void RenderBackground();
	void Render();
	void RenderTime();
	void RenderPoint();
	void RenderCoin();
	void RenderLife();
	void Update();
	void UpdateCoin(unsigned int coin);
	void UpdateTime(int time);
	void UpdatePoint(unsigned int point);
	void UpdateLife(unsigned int life);
}; typedef CHud* LPHUD;