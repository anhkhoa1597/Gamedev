#include "Animations.h"
#include "debug.h"

CAnimations* CAnimations::__instance = NULL;
CTextures* textures = CTextures::GetInstance();
CSprites* sprites = CSprites::GetInstance();
CAnimations* animations = CAnimations::GetInstance();

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	if (animations[id] != NULL)
		DebugOut(L"[WARNING] Animation %d already exists\n", id);

	animations[id] = ani;
}

void CAnimations::Add(LPCWSTR filePath, int animationId, int length, int defaultTime)
{
	//every animation is a texture
	int textureId = animationId;

	//1 animation have about from 1 to 10 sprite
	int spriteId = animationId*10;

	if (animations[animationId] != NULL)
		DebugOut(L"[WARNING] Animation %d already exists\n", animationId);

	textures->Add(textureId, filePath);
	LPTEXTURE texture = textures->Get(animationId);
	int height = texture->getHeight();
	int width = texture->getWidth() / length;

	LPANIMATION ani = new CAnimation(defaultTime);
	for (int i = 0; i < length; i++) { 
		//scan every sprite in texture
		spriteId += i;
		sprites->Add(spriteId, i * width + i, 0, ((i + 1) * width) - 1 + i, height, texture);
		ani->Add(spriteId);
	}

	animations[animationId] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Animation ID %d not found\n", id);
	return ani;
}