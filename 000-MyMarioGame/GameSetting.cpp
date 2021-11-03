#include "GameSetting.h"

CGameSetting::CGameSetting()
{
	mario_walking_speed = 0;
	mario_running_speed = 0;
	mario_accel_walk_x = 0;
	mario_accel_run_x = 0;
	mario_jump_speed_y = 0;
	mario_jump_run_speed_y = 0;
	mario_gravity = 0; 
	mario_jump_deflect_speed = 0;
	mario_untouchable_time = 0;
	mario_life = 0;

	id_ani_mario_idle_left = id_ani_mario_idle_right =
	id_ani_mario_walking_left = id_ani_mario_walking_right =
	id_ani_mario_running_left = id_ani_mario_running_right =
	id_ani_mario_jump_run_left = id_ani_mario_jump_run_right =
	id_ani_mario_jump_walk_left = id_ani_mario_jump_walk_right =
	id_ani_mario_sit_left = id_ani_mario_sit_right =
	id_ani_mario_brace_left = id_ani_mario_brace_right =
	id_ani_mario_small_idle_left = id_ani_mario_small_idle_right =
	id_ani_mario_small_walking_left = id_ani_mario_small_walking_right =
	id_ani_mario_small_running_left = id_ani_mario_small_running_right =
	id_ani_mario_small_jump_run_left = id_ani_mario_small_jump_run_right =
	id_ani_mario_small_jump_walk_left = id_ani_mario_small_jump_walk_right =
	id_ani_mario_small_brace_left = id_ani_mario_small_brace_right =
	id_ani_mario_die = -1;
}

CGameSettings* CGameSettings::__instance = NULL;

CGameSettings* CGameSettings::GetInstance()
{
	if (__instance == NULL) __instance = new CGameSettings();
	return __instance;
}

void CGameSettings::Add(int id, LPGAMESETTING gameSetting)
{
	if (gameSettings[id] != NULL)
		DebugOut(L"[WARNING] gameSetting of scene %d already exists\n", id);

	gameSettings[id] = gameSetting;
}

LPGAMESETTING CGameSettings::Get(int id)
{
	LPGAMESETTING ani = gameSettings[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] game setting ID %d not found\n", id);
	return ani;
}