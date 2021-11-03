#include "GameSetting.h"

//CGamesetting* CGamesetting::__instance = NULL;

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
}