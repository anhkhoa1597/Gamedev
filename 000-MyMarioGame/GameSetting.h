#pragma once
#include <Windows.h>
#include <string>

#include "tinyxml2.h"
#include "debug.h"

using namespace std;

class CGameSetting
{
	//static CGamesetting* __instance;
public:
#pragma region MARIO_SETTING
	float mario_walking_speed, mario_running_speed, 
		mario_accel_walk_x, mario_accel_run_x,
		mario_jump_speed_y, mario_jump_run_speed_y,
		mario_gravity, mario_jump_deflect_speed,
		mario_untouchable_time;
	int	mario_life;
#pragma endregion

	CGameSetting();
	~CGameSetting() {}
	virtual void Load() {}
	//static CGamesetting* GetInstance();
}; 
typedef CGameSetting* LPGAMESETTING;