#pragma once
#include <Windows.h>
#include <string>
#include <unordered_map>

#include "tinyxml2.h"
#include "debug.h"
#include "Utils.h"

using namespace std;

class CGameSetting
{
	static CGameSetting* __instance;
public:
#pragma region MARIO_SETTING
	//constant
	int mario_width = 0;
	int mario_big_height = 0;
	int mario_small_height = 0;
	int mario_sitting_height = 0;

	float mario_tele_speed = 0;
	float mario_walking_speed = 0;
	float mario_running_speed = 0;
	float mario_accel_walk_x = 0;
	float mario_accel_run_x = 0;
	float mario_jump_speed_y = 0;
	float mario_jump_run_speed_y = 0;
	float mario_gravity = 0;
	float mario_jump_deflect_speed = 0;
	float mario_untouchable_time = 0;
	int	mario_life = 0;

	//id animation
	int id_ani_mario_idle_left = -1;
	int id_ani_mario_idle_right = -1;
	int id_ani_mario_walking_left = -1; 
	int id_ani_mario_walking_right = -1;
	int id_ani_mario_running_left = -1; 
	int id_ani_mario_running_right = -1;
	int id_ani_mario_jump_run_left = -1; 
	int id_ani_mario_jump_run_right = -1;
	int id_ani_mario_jump_walk_left = -1; 
	int id_ani_mario_jump_walk_right = -1;
	int id_ani_mario_sit_left = -1; 
	int id_ani_mario_sit_right = -1;
	int id_ani_mario_brace_left = -1; 
	int id_ani_mario_brace_right = -1;
	int id_ani_mario_kick_left = -1;
	int id_ani_mario_kick_right = -1;
	int id_ani_mario_tele = -1;
	int id_ani_mario_small_idle_left = -1; 
	int id_ani_mario_small_idle_right = -1;
	int id_ani_mario_small_walking_left = -1; 
	int id_ani_mario_small_walking_right = -1;
	int id_ani_mario_small_running_left = -1; 
	int id_ani_mario_small_running_right = -1;
	int id_ani_mario_small_jump_run_left = -1; 
	int id_ani_mario_small_jump_run_right = -1;
	int id_ani_mario_small_jump_walk_left = -1;
	int id_ani_mario_small_jump_walk_right = -1;
	int id_ani_mario_small_brace_left = -1;
	int id_ani_mario_small_brace_right = -1;
	int id_ani_mario_small_kick_left = -1;
	int id_ani_mario_small_kick_right = -1;
	int id_ani_mario_small_tele = -1;
	int id_ani_mario_die = -1;
#pragma endregion

#pragma region GOOMBA
	//constant
	float goomba_gravity = 0;
	float goomba_walking_speed = 0;
	float wing_goomba_gravity = 0;
	float wing_goomba_low_jump = 0;
	float wing_goomba_high_jump = 0;
	float goomba_bouncing_speed = 0;
	float goomba_bouncing_up_speed = 0;
	int goomba_die_timeout = 0;
	int goomba_bounce_die_timeout = 0;
	int wing_goomba_walk_timeout = 0;
	//id animation
	int id_ani_goomba_walking = -1;
	int id_ani_goomba_die = -1;
	int id_ani_goomba_bounce_die = -1;
	int id_ani_red_goomba_walking = -1;
	int id_ani_red_goomba_die = -1;
	int id_ani_red_goomba_bounce_die = -1;
	int id_ani_wing_jump = -1;
	int id_ani_wing_walk = -1;
#pragma endregion

#pragma region KOOPA
	//constant
	float koopa_gravity = 0;
	float koopa_walking_speed = 0;
	float wing_koopa_gravity = 0;
	float wing_koopa_jump_speed = 0;
	float koopa_bouncing_up_speed = 0;
	float koopa_bouncing_speed = 0;
	int wing_koopa_walk_timeout = 0;
	float koopa_shield_rolling_speed = 0;
	int koopa_shield_timeout = 0;
	int koopa_shield_standing_timeout = 0;
	int koopa_die_timeout = 0;
	int koopa_bounce_die_timeout = 0;
	//id animation
	int id_ani_koopa_walking_left = -1;
	int id_ani_koopa_walking_right = -1;
	int id_ani_red_koopa_walking_left = -1;
	int id_ani_red_koopa_walking_right = -1;
	int id_ani_wing_left = -1;
	int id_ani_wing_right = -1;
	int id_ani_koopa_shield_idle_down = -1;
	int id_ani_koopa_shield_idle_up = -1;
	int id_ani_koopa_shield_standing_down = -1;
	int id_ani_koopa_shield_standing_up = -1;
	int id_ani_koopa_shield_rolling_down = -1;
	int id_ani_koopa_shield_rolling_up = -1;
	int id_ani_red_koopa_shield_idle_down = -1;
	int id_ani_red_koopa_shield_idle_up = -1;
	int id_ani_red_koopa_shield_standing_down = -1;
	int id_ani_red_koopa_shield_standing_up = -1;
	int id_ani_red_koopa_shield_rolling_down = -1;
	int id_ani_red_koopa_shield_rolling_up = -1;
#pragma endregion

#pragma region BRICK
	//constant
	float brick_bouncing_speed = 0;
	int brick_bounce_height = 0;
	int brick_number_bounce_of_multi_coin = 0;
	//id animation
	int id_ani_brick = -1;
	int id_ani_question_brick = -1;
	int id_ani_block_brick = -1;
#pragma endregion

#pragma region COIN
	//constant
	float coin_bouncing_speed = 0;
	int coin_bounce_height = 0;
	int coin_drop_height = 0;
	//id animation
	int id_ani_coin_spinning = -1;
	int id_ani_coin_idle = -1;
	int id_ani_coin_drop = -1;
#pragma endregion

#pragma region MUSHROOM
	//constant
	float mushroom_gravity = 0;
	float mushroom_speed = 0;
	float mushroom_bouncing_speed = 0;
	int mushroom_life_up = 0;
	//id animation
	int id_ani_red_mushroom = -1;
	int id_ani_green_mushroom = -1;
#pragma endregion

#pragma region OTHER
	int pipe_height = 0;
	float pipe_adjust_width_can_go_through = 0;
#pragma endregion
	//CGameSetting() {};
	//~CGameSetting() {}
	void Load(string settingFile);
	void LoadIdAnimations(string name, int id);

	static CGameSetting* GetInstance();
}; 
typedef CGameSetting* LPGAMESETTING;