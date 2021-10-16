/* =============================================================
	INTRODUCTION TO MY MARIO GAME PROGRAMMING
	Version:
		0.1: Create new project, re-initiate by code from 04-Collision sample
		0.2: Add tinyxml2 lib, create class Map, Map1-1 to manager all map and test to make tiled-background
		0.3: + Change the logic of camera: 
					- camera follow to mario if move right 
					- camera dont follow when mario move left
			 + Create function CAnimations::Add to add an animation from a texture animate
		0.4: fix the Draw function, fix anamtion are blurred, update function Canimation::Add
		0.5: load tiled-map, fix animation blurred, update animation texture mario
		0.6: load object, load boundingbox of object
		0.7: add attributes: translationX, translationY in to function CSprite::Draw to draw sprite correctly
		0.8: update mario animation smoother and transparent correctly.
			 ***To make animation weren't blurred: + the textures's width and height are even
												   + the width must divisible to lenght
		0.9: fix tileset transparent, fix boudingbox of object
		0.10: add file from scene-manager
================================================================ */

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <list>

#include "Animations.h"

#include "Map1_1.h"
#include "Map.h"

#include "SampleKeyEventHandler.h"

#include "AssetIDs.h"
#include "AssetPaths.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"000 - MyMarioGame"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 270


CGame *game;
Map* currentMap;

list<LPGAMEOBJECT> objects;

CSampleKeyHandler * keyHandler; 

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadTileSet()
{

}

void LoadAssetsMario()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// IDLE
	sprites->Add(ID_SPRITE_MARIO_BIG_IDLE_RIGHT + 1, 1029, 93, 1029 + 15, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_IDLE_LEFT + 1, 1, 93, 1 + 15, 93 + 27, texMario);

	// WALKING LEFT
	sprites->Add(ID_SPRITE_MARIO_BIG_WALKING_RIGHT + 2, 19, 93, 19 + 17, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_WALKING_RIGHT + 3, 37, 93, 37 + 17, 93 + 27, texMario);

	// WALKING RIGHT
	sprites->Add(ID_SPRITE_MARIO_BIG_WALKING_LEFT + 2, 1009, 93, 1009 + 17, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_WALKING_LEFT + 3, 991, 93, 991 + 17, 93 + 27, texMario);

	// RUNNING RIGHT 
	sprites->Add(ID_SPRITE_MARIO_BIG_RUNNING_RIGHT + 1, 934, 93, 934 + 19, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_RUNNING_RIGHT + 2, 908, 93, 908 + 19, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_RUNNING_RIGHT + 3, 882, 93, 882 + 19, 93 + 27, texMario);

	// RUNNING LEFT
	sprites->Add(ID_SPRITE_MARIO_BIG_RUNNING_LEFT + 1, 91, 93, 91 + 19, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_RUNNING_LEFT + 2, 117, 93, 117 + 19, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_RUNNING_LEFT + 3, 113, 93, 113 + 19, 93 + 27, texMario);

	// JUMP WALK RIGHT & LEFT 
	sprites->Add(ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT + 1, 955, 93, 955 + 17, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT + 1, 73, 93, 73 + 17, 93 + 27, texMario);

	// JUMP RUN RIGHT & LEFT 
	sprites->Add(ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT + 1, 856, 93, 856 + 19, 93 + 27, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT + 1, 169, 93, 169 + 19, 93 + 27, texMario);

	// SIT RIGHT/LEFT
	sprites->Add(ID_SPRITE_MARIO_BIG_SIT_RIGHT + 1, 975, 102, 975 + 15, 102 + 19, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_SIT_LEFT + 1, 55, 102, 55 + 15, 102 + 19, texMario);

	// BRACING RIGHT/LEFT
	sprites->Add(ID_SPRITE_MARIO_BIG_BRACE_RIGHT + 1, 833, 92, 833 + 17, 92 + 29, texMario);
	sprites->Add(ID_SPRITE_MARIO_BIG_BRACE_LEFT + 1, 195, 92, 195 + 17, 92 + 29, texMario);

	// MARIO DIE
	sprites->Add(ID_SPRITE_MARIO_DIE + 1, 307, 16, 307 + 17, 16 + 17, texMario);

	// SMALL MARIO 
	sprites->Add(ID_SPRITE_MARIO_SMALL_IDLE_LEFT + 1, 3, 17, 3 + 13, 17 + 15, texMario);
	sprites->Add(ID_SPRITE_MARIO_SMALL_IDLE_RIGHT + 1, 1029, 17, 1029 + 13, 17 + 15, texMario);

	sprites->Add(ID_SPRITE_MARIO_SMALL_WALKING_RIGHT + 2, 1009, 16, 1009 + 15, 16 + 17, texMario);

	sprites->Add(ID_SPRITE_MARIO_SMALL_WALKING_LEFT + 2, 20, 16, 20 + 15, 16 + 17, texMario);

	sprites->Add(ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT + 1, 973, 16, 973 + 17, 16 + 17, texMario);
	sprites->Add(ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT + 2, 955, 16, 955 + 17, 16 + 17, texMario);

	sprites->Add(ID_SPRITE_MARIO_SMALL_RUNNING_LEFT + 1, 55, 16, 55 + 17, 16 + 17, texMario);
	sprites->Add(ID_SPRITE_MARIO_SMALL_RUNNING_LEFT + 2, 73, 16, 73 + 17, 16 + 17, texMario);

	sprites->Add(ID_SPRITE_MARIO_SMALL_BRACE_LEFT + 1, 110, 16, 110 + 15, 16 + 17, texMario);
	sprites->Add(ID_SPRITE_MARIO_SMALL_BRACE_RIGHT + 1, 920, 16, 920 + 15, 16 + 17, texMario);

	sprites->Add(ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT + 1, 37, 16, 37 + 17, 16 + 17, texMario);
	sprites->Add(ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT + 1, 991, 16, 991 + 17, 16 + 17, texMario);

	sprites->Add(ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT + 1, 91, 16, 91 + 17, 16 + 17, texMario);
	sprites->Add(ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT + 1, 937, 16, 937 + 17, 16 + 117, texMario);

	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_IDLE_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_IDLE_LEFT + 1);
	animations->Add(ID_ANI_MARIO_IDLE_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_IDLE_RIGHT + 1);
	ani->Add(ID_SPRITE_MARIO_BIG_WALKING_RIGHT + 2);
	ani->Add(ID_SPRITE_MARIO_BIG_WALKING_RIGHT + 3);
	ani->Add(ID_SPRITE_MARIO_BIG_WALKING_RIGHT + 2);
	animations->Add(ID_ANI_MARIO_WALKING_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_IDLE_LEFT + 1);
	ani->Add(ID_SPRITE_MARIO_BIG_WALKING_LEFT + 2);
	ani->Add(ID_SPRITE_MARIO_BIG_WALKING_LEFT + 3);
	ani->Add(ID_SPRITE_MARIO_BIG_WALKING_LEFT + 2);
	animations->Add(ID_ANI_MARIO_WALKING_LEFT, ani);

	ani = new CAnimation(50);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_RIGHT + 1);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_RIGHT + 2);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_RIGHT + 3);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_RIGHT + 2);
	animations->Add(ID_ANI_MARIO_RUNNING_RIGHT, ani);

	// Mario runs faster hence animation speed should be faster
	ani = new CAnimation(50);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_LEFT + 1);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_LEFT + 2);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_LEFT + 3);
	ani->Add(ID_SPRITE_MARIO_BIG_RUNNING_LEFT + 2);
	animations->Add(ID_ANI_MARIO_RUNNING_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_JUMP_WALK_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT + 1);
	animations->Add(ID_ANI_MARIO_JUMP_WALK_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_JUMP_RUN_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT + 1);
	animations->Add(ID_ANI_MARIO_JUMP_RUN_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_SIT_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_SIT_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_SIT_LEFT + 1);
	animations->Add(ID_ANI_MARIO_SIT_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_BRACE_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_BRACE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_BIG_BRACE_LEFT + 1);
	animations->Add(ID_ANI_MARIO_BRACE_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_DIE + 1);
	animations->Add(ID_ANI_MARIO_DIE, ani);

	//
	// SMALL MARIO 
	//
	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_IDLE_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_IDLE_RIGHT + 1);
	ani->Add(ID_SPRITE_MARIO_SMALL_WALKING_RIGHT + 2);
	animations->Add(ID_ANI_MARIO_SMALL_WALKING_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_IDLE_LEFT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_IDLE_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_IDLE_LEFT + 1);
	ani->Add(ID_SPRITE_MARIO_SMALL_WALKING_LEFT + 2);
	animations->Add(ID_ANI_MARIO_SMALL_WALKING_LEFT, ani);

	ani = new CAnimation(50);
	ani->Add(ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT + 1);
	ani->Add(ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT + 2);
	animations->Add(ID_ANI_MARIO_SMALL_RUNNING_RIGHT, ani);

	ani = new CAnimation(50);
	ani->Add(ID_SPRITE_MARIO_SMALL_RUNNING_LEFT + 1);
	ani->Add(ID_SPRITE_MARIO_SMALL_RUNNING_LEFT + 2);
	animations->Add(ID_ANI_MARIO_SMALL_RUNNING_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_BRACE_LEFT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_BRACE_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_BRACE_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_BRACE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT + 1);
	animations->Add(ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT, ani);
}

void LoadAssetsGoomba()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPTEXTURE texEnemy = textures->Get(ID_TEX_ENEMY);

	sprites->Add(ID_SPRITE_GOOMBA_WALK + 1, 5, 14, 21, 29, texEnemy);  
	sprites->Add(ID_SPRITE_GOOMBA_WALK + 2, 25, 14, 41, 29, texEnemy); 

	sprites->Add(ID_SPRITE_GOOMBA_DIE + 1, 45, 21, 61, 29, texEnemy);

	LPANIMATION ani = new CAnimation(100);
	ani->Add(ID_SPRITE_GOOMBA_WALK + 1);
	ani->Add(ID_SPRITE_GOOMBA_WALK + 2);
	animations->Add(ID_ANI_GOOMBA_WALKING, ani);

	ani = new CAnimation(100);
	ani->Add(ID_SPRITE_GOOMBA_DIE + 1);
	animations->Add(ID_ANI_GOOMBA_DIE, ani);

}
void LoadAssetsBrick()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(ID_SPRITE_BRICK + 1, 372, 153, 372 + 15, 153 + 15, texMisc);

	LPANIMATION ani = new CAnimation(100);
	ani->Add(ID_SPRITE_BRICK + 1);
	animations->Add(ID_ANI_BRICK, ani);
}
void LoadAssetsCoin()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);

	sprites->Add(ID_SPRITE_COIN + 1, 303, 99, 303 + 9, 99 + 15, texMisc);
	sprites->Add(ID_SPRITE_COIN + 2, 321, 99, 321 + 9, 99 + 15, texMisc);
	sprites->Add(ID_SPRITE_COIN + 3, 338, 99, 338 + 9, 99 + 15, texMisc);

	LPANIMATION ani = new CAnimation(300);
	ani->Add(ID_SPRITE_COIN + 1);
	ani->Add(ID_SPRITE_COIN + 2);
	ani->Add(ID_SPRITE_COIN + 3);
	animations->Add(ID_ANI_COIN, ani);
}

void LoadAssetsOther()
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();

	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(ID_SPRITE_CLOUD_BEGIN, 390, 117, 390 + 15, 117 + 14, texMisc);
	sprites->Add(ID_SPRITE_CLOUD_MIDDLE, 408, 117, 408 + 15, 117 + 14, texMisc);
	sprites->Add(ID_SPRITE_CLOUD_END, 426, 117, 426 + 15, 117 + 14, texMisc);

}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	currentMap = new Map1_1();
	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMY);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);
	textures->Add(ID_TEX_BBOX, TEXTURE_PATH_BBOX);

	LoadTileSet();
	LoadAssetsMario();
	//LoadAssetsGoomba();
	//LoadAssetsBrick();
	//LoadAssetsCoin();
	//LoadAssetsOther();
}

void ClearScene()
{ 
	list<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

//#define MARIO_START_X 88.0f
#define MARIO_START_X 24.0f
#define MARIO_START_Y 0.0f

#define BRICK_X 0.0f
#define GOOMBA_X 200.0f
#define COIN_X 100.0f

#define BRICK_Y GROUND_Y + 20.0f
#define NUM_BRICKS 70

/*
* Reload all objects of current scene 
* NOTE: super bad way to build a scene! We need to load a scene from data instead of hard-coding like this 
*/
void Reload()
{
	ClearScene();
}

bool IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void PurgeDeletedObjects()
{
	list<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), IsGameObjectDeleted),
		objects.end());
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	list<LPGAMEOBJECT>::iterator i;
	for (i = objects.begin(); i != objects.end(); ++i)
	{
		coObjects.push_back(*i);
	}

	for (i = objects.begin(); i != objects.end(); ++i)
	{
		(*i)->Update(dt,&coObjects);
	}

	PurgeDeletedObjects();
	currentMap->Update();
}

/*
	Render a frame 
*/
void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);
	currentMap->Render();
	list<LPGAMEOBJECT>::iterator i;
	for (i = objects.begin(); i != objects.end(); ++i)
	{
		(*i)->Render();
	}

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc{};
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = (DWORD)(now - frameStart);

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	LoadResources();
	Reload();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}