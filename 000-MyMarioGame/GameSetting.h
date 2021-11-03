#pragma once
#include <Windows.h>
#include <string>
#include <unordered_map>

#include "tinyxml2.h"
#include "debug.h"

using namespace std;

class CGameSetting
{
public:
#pragma region MARIO_SETTING
	//constant
	float mario_walking_speed;
	float mario_running_speed;
	float mario_accel_walk_x;
	float mario_accel_run_x;
	float mario_jump_speed_y;
	float mario_jump_run_speed_y;
	float mario_gravity;
	float mario_jump_deflect_speed;
	float mario_untouchable_time;
	int	mario_life;
	//animation
	int id_ani_mario_idle_left, id_ani_mario_idle_right,
		id_ani_mario_walking_left, id_ani_mario_walking_right,
		id_ani_mario_running_left, id_ani_mario_running_right,
		id_ani_mario_jump_run_left, id_ani_mario_jump_run_right,
		id_ani_mario_jump_walk_left, id_ani_mario_jump_walk_right,
		id_ani_mario_sit_left, id_ani_mario_sit_right,
		id_ani_mario_brace_left, id_ani_mario_brace_right,

		id_ani_mario_small_idle_left, id_ani_mario_small_idle_right,
		id_ani_mario_small_walking_left, id_ani_mario_small_walking_right,
		id_ani_mario_small_running_left, id_ani_mario_small_running_right,
		id_ani_mario_small_jump_run_left, id_ani_mario_small_jump_run_right,
		id_ani_mario_small_jump_walk_left, id_ani_mario_small_jump_walk_right,
		id_ani_mario_small_brace_left, id_ani_mario_small_brace_right,
		id_ani_mario_die;
#pragma endregion
#pragma region GOOMBA

#pragma endregion

	CGameSetting();
	~CGameSetting() {}
}; 
typedef CGameSetting* LPGAMESETTING;



class CGameSettings
{
	static CGameSettings* __instance;

	unordered_map<int, LPGAMESETTING> gameSettings;
public:
	void Add(int id, LPGAMESETTING gameSetting);
	LPGAMESETTING Get(int id);

	static CGameSettings* GetInstance();
};