#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <unordered_map>

using namespace std;
	
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Texture.h"
#include "KeyEventHandler.h"
#include "Scene.h"
#include "GameSetting.h"
#include "tinyxml2.h"
#include "debug.h"

#define MAX_FRAME_RATE 100
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

/*
	Our simple game framework
*/
class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state

	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	HINSTANCE hInstance;

	ID3D10SamplerState* pPointSamplerState;

	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	int next_scene = -1;
	bool isReload_scene = false;

	bool isMarioGoThroughPipe = false;
	int current_map = -1; //need this feature
	int mario_life = 0;
	int mario_coin = 0;
	int mario_point = 0;
	int mario_level = 0;
	int time = 0; // need constant
	ULONGLONG start_time = 0;
	int max_time = 0;
	bool isOnPause = false;
	ULONGLONG start_pause = 0;
public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen. (x,y) is at the CENTER of the image
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL, float alpha = 1.0f);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b, float alpha = 1.0f)
	{
		RECT rect{};
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect, alpha);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }


	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }

	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }

	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	static CGame* GetInstance();

	void SetPointSamplerState();

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }
	void GetCam(float& l, float& t, float& r, float& b) { l = cam_x; t = cam_y; r = l + (float)backBufferWidth; b = t + (float)backBufferHeight; }
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	int GetCurrentSceneId() { return current_scene; }

	void Load(string gameFile);
	void SwitchScene();
	void InitiateSwitchScene(int scene_id);
	void ReloadScene();

	//mario and other data can be transferred to another scene
	bool IsMarioGoThroughPipe() { return isMarioGoThroughPipe; }
	void SetMarioGoThroughPipe(bool isMarioGoThroughPipe) { this->isMarioGoThroughPipe = isMarioGoThroughPipe; }
	void IncreaseCoin() 
	{ mario_coin++; 
		if (mario_coin == 100)
		{
			mario_coin = 0;
			LifeUp(1);
		}
	}
	int GetCoin() { return mario_coin; }
	int GetPoint() { return mario_point; }
	void IncreasePoint(int point) { mario_point += point; }
	int GetLife() { return mario_life; }
	void LifeUp(int life) { mario_life += life; }
	void LifeDown() { mario_life--; }
	int GetLevel() { return mario_level; }
	void SetLevel(int level) { mario_level = level; }
	void StartTime() { start_time = GetTickCount64(); max_time = CGameSetting::GetInstance()->game_time; }
	void UpdateTime() { time = max_time - (int)(GetTickCount64() - start_time) / 1000; }
	int GetTime() { return time; }
	void StartItemPause() { start_pause = GetTickCount64(); }
	ULONGLONG GetStartPause() { return start_pause; }
	void StopPause() { isOnPause = false; start_pause = 0; }
	void SetIsOnPause(bool isOnPause) { this->isOnPause = isOnPause; }
	bool IsOnPause() { return isOnPause; }



	~CGame();
};
typedef CGame* LPGAME;