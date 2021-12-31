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
	int mushroom_point = 0;
	int point_0 = 0;
	int point_1 = 0;
	int point_2 = 0;
	int point_3 = 0;
	int point_4 = 0;
	int point_5 = 0;
	int point_6 = 0;
	int point_7 = 0;

	float mario_tele_speed = 0;
	float mario_walking_speed = 0;
	float mario_running_speed = 0;
	float mario_average_speed = 0;
	int mario_max_power = 0;
	float mario_accel_walk_x = 0;
	float mario_accel_run_x = 0;
	float mario_jump_speed_y = 0;
	float mario_jump_run_speed_y = 0;
	float mario_gravity = 0;
	float mario_jump_deflect_speed = 0;
	int mario_untouchable_time = 0;
	int mario_power_increase_delay_timeout = 0;
	int mario_power_decrease_delay_timeout = 0;
	int mario_max_power_timeout = 0;
	int mario_flying_timeout = 0;
	int mario_slow_falling_timeout = 0;
	int mario_fly_falling_timeout = 0;
	int mario_ani_slow_falling_time = 0;
	int mario_ani_fly_falling_time = 0;
	int mario_ani_kick_time = 0;
	int mario_invisible_timeout = 0;
	int	mario_life = 0;

	//id animation
	int id_ani_raccoon_idle_left = -1;
	int id_ani_raccoon_idle_right = -1;
	int id_ani_raccoon_walking_left = -1;
	int id_ani_raccoon_walking_right = -1;
	int id_ani_raccoon_running_left = -1;
	int id_ani_raccoon_running_right = -1;
	int id_ani_raccoon_jump_run_left = -1;
	int id_ani_raccoon_jump_run_right = -1;
	int id_ani_raccoon_jump_walk_left = -1;
	int id_ani_raccoon_jump_walk_right = -1;
	int id_ani_raccoon_free_falling_left = -1;
	int id_ani_raccoon_free_falling_right = -1;
	int id_ani_raccoon_slow_falling_left = -1;
	int id_ani_raccoon_slow_falling_right = -1;
	int id_ani_raccoon_fly_falling_left = -1;
	int id_ani_raccoon_fly_falling_right = -1;
	int id_ani_raccoon_flying_left = -1;
	int id_ani_raccoon_flying_right = -1;
	int id_ani_raccoon_sit_left = -1;
	int id_ani_raccoon_sit_right = -1;
	int id_ani_raccoon_brace_left = -1;
	int id_ani_raccoon_brace_right = -1;
	int id_ani_raccoon_carry_idle_left = -1;
	int id_ani_raccoon_carry_idle_right = -1;
	int id_ani_raccoon_carry_jump_left = -1;
	int id_ani_raccoon_carry_jump_right = -1;
	int id_ani_raccoon_carry_walking_left = -1;
	int id_ani_raccoon_carry_walking_right = -1;
	int id_ani_raccoon_kick_left = -1;
	int id_ani_raccoon_kick_right = -1;
	int id_ani_raccoon_attack_left = -1;
	int id_ani_raccoon_attack_right = -1;
	int id_ani_raccoon_carry_change_dir = -1;
	int id_ani_raccoon_tele = -1;

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
	int id_ani_mario_carry_idle_left = -1;
	int id_ani_mario_carry_idle_right = -1;
	int id_ani_mario_carry_jump_left = -1;
	int id_ani_mario_carry_jump_right = -1;
	int id_ani_mario_carry_walking_left = -1;
	int id_ani_mario_carry_walking_right = -1;
	int id_ani_mario_kick_left = -1;
	int id_ani_mario_kick_right = -1;
	int id_ani_mario_carry_change_dir = -1;
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
	int id_ani_mario_small_carry_idle_left = -1;
	int id_ani_mario_small_carry_idle_right = -1;
	int id_ani_mario_small_carry_jump_left = -1;
	int id_ani_mario_small_carry_jump_right = -1;
	int id_ani_mario_small_carry_walking_left = -1;
	int id_ani_mario_small_carry_walking_right = -1;
	int id_ani_mario_small_kick_left = -1;
	int id_ani_mario_small_kick_right = -1;
	int id_ani_mario_small_carry_change_dir = -1;
	int id_ani_mario_small_tele = -1;
	int id_ani_mario_die = -1;
	int id_ani_mario_invisible = -1;

#pragma endregion

#pragma region GOOMBA
	//constant
	int goomba_width = 0;
	int goomba_height = 0;
	int goomba_height_die = 0;
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
	int koopa_width = 0;
	int koopa_height = 0;
	int koopa_shield_height = 0;
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

#pragma region PIRANHA_PLANT
	int piranha_plant_width = 0;
	int piranha_plant_height = 0;
	int piranha_plant_delay_timeout = 0;

	int id_ani_piranha_plant_left_down = -1;
	int id_ani_piranha_plant_left_up = -1;
	int id_ani_piranha_plant_right_down = -1;
	int id_ani_piranha_plant_right_up = -1;
	int id_ani_horizontal_piranha_plant = -1;
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

#pragma region HUD
	float hud_x = 0;
	float hud_y = 0;
	int hud_width = 0;
	int hud_height = 0;
	int id_ani_hud = -1;
	int id_tex_bbox = -1;
	int id_tex_hud_background = -1;
	int sprite_id_hud_and_font = -1;
	int sprite_id_font_power_meter_normal = -1;
	int sprite_id_font_power_meter_running = -1;
	int sprite_id_font_power_meter_p_normal = -1;
	int id_font_power_meter_p_running = -1;
	int font_width = 0;
	float font_time_x = 0;
	float font_time_y = 0;
	float font_coin_x = 0;
	float font_coin_y = 0;
	float font_point_x = 0;
	float font_point_y = 0;
	float font_life_x = 0;
	float font_life_y = 0;
	float font_world_x = 0;
	float font_world_y = 0;
	float font_power_meter_x = 0;
	float font_power_meter_y = 0;

#pragma endregion

#pragma region PIPE
	int pipe_height = 0;
	float pipe_adjust_width_can_go_through = 0;
#pragma endregion

#pragma region PAUSE
	int pause_timeout = 0;

	int id_ani_pause = -1;
	int id_ani_pause_be_hitted = -1;
#pragma endregion

#pragma region OTHER
	int game_time = 0;
#pragma endregion
	//CGameSetting() {};
	//~CGameSetting() {}
	void Load(string settingFile);
	void LoadIdAnimations(string name, int id);

	static CGameSetting* GetInstance();
}; 
typedef CGameSetting* LPGAMESETTING;