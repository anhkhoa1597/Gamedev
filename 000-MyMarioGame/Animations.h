#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"
#include "Textures.h"

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	void Add(LPCWSTR filePath, int id, int length, int defaultTime);
	LPANIMATION Get(int id);

	static CAnimations* GetInstance();
};