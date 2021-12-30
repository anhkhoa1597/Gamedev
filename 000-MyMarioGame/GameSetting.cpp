#include "GameSetting.h"

CGameSetting* CGameSetting::__instance = NULL;

void CGameSetting::Load(string settingFile)
{
	DebugOut(L"[INFO] Start loading setting file : %s\n", ToLPCWSTR(settingFile));

	tinyxml2::XMLDocument doc;
	doc.LoadFile(settingFile.c_str());
	tinyxml2::XMLElement* pSettings = doc.FirstChildElement("settings");
	if (pSettings == nullptr)
	{
		DebugOut(L"[ERROR] Failed to loading setting file : %s\n", ToLPCWSTR(settingFile));
		return;
	}
	tinyxml2::XMLElement* pSetting = pSettings->FirstChildElement("setting");
	while (pSetting != nullptr)
	{
		string name = pSetting->Attribute("name");
		if (name == "mario-walking-speed") pSetting->QueryFloatAttribute("value", &mario_walking_speed);
		else if (name == "mario-width") pSetting->QueryIntAttribute("value", &mario_width);
		else if (name == "mario-big-height") pSetting->QueryIntAttribute("value", &mario_big_height);
		else if (name == "mario-small-height") pSetting->QueryIntAttribute("value", &mario_small_height);
		else if (name == "mario-sitting-height") pSetting->QueryIntAttribute("value", &mario_sitting_height);
		else if (name == "mario-running-speed") pSetting->QueryFloatAttribute("value", &mario_running_speed);
		else if (name == "mario-average-speed") pSetting->QueryFloatAttribute("value", &mario_average_speed);
		else if (name == "mario-max-power") pSetting->QueryIntAttribute("value", &mario_max_power);
		else if (name == "mario-tele-speed") pSetting->QueryFloatAttribute("value", &mario_tele_speed);
		else if (name == "mario-accel-walk-x") pSetting->QueryFloatAttribute("value", &mario_accel_walk_x);
		else if (name == "mario-accel-run-x") pSetting->QueryFloatAttribute("value", &mario_accel_run_x);
		else if (name == "mario-jump-speed-y") pSetting->QueryFloatAttribute("value", &mario_jump_speed_y);
		else if (name == "mario-jump-run-speed-y") pSetting->QueryFloatAttribute("value", &mario_jump_run_speed_y);
		else if (name == "mario-gravity") pSetting->QueryFloatAttribute("value", &mario_gravity);
		else if (name == "mario-jump-deflect-speed") pSetting->QueryFloatAttribute("value", &mario_jump_deflect_speed);
		else if (name == "mario-untouchabletime") pSetting->QueryIntAttribute("value", &mario_untouchable_time);
		else if (name == "mario-power-increase-delay-timeout") pSetting->QueryIntAttribute("value", &mario_power_increase_delay_timeout);
		else if (name == "mario-power-decrease-delay-timeout") pSetting->QueryIntAttribute("value", &mario_power_decrease_delay_timeout);
		else if (name == "mario-max-power-timeout") pSetting->QueryIntAttribute("value", &mario_max_power_timeout);
		else if (name == "mario-flying-timeout") pSetting->QueryIntAttribute("value", &mario_flying_timeout);
		else if (name == "mario-slow-falling-timeout") pSetting->QueryIntAttribute("value", &mario_slow_falling_timeout);
		else if (name == "mario-fly-falling-timeout") pSetting->QueryIntAttribute("value", &mario_fly_falling_timeout);
		else if (name == "mario-ani-slow-falling-time") pSetting->QueryIntAttribute("value", &mario_ani_slow_falling_time);
		else if (name == "mario-ani-fly-falling-time") pSetting->QueryIntAttribute("value", &mario_ani_fly_falling_time);
		else if (name == "mario-ani-kick-time") pSetting->QueryIntAttribute("value", &mario_ani_kick_time);
		else if (name == "mario-invisible-timeout") pSetting->QueryIntAttribute("value", &mario_invisible_timeout);
		else if (name == "mario-life") pSetting->QueryIntAttribute("value", &mario_life);
		else if (name == "mushroom-point") pSetting->QueryIntAttribute("value", &mushroom_point);
		else if (name == "point-0") pSetting->QueryIntAttribute("value", &point_0);
		else if (name == "point-1") pSetting->QueryIntAttribute("value", &point_1);
		else if (name == "point-2") pSetting->QueryIntAttribute("value", &point_2);
		else if (name == "point-3") pSetting->QueryIntAttribute("value", &point_3);
		else if (name == "point-4") pSetting->QueryIntAttribute("value", &point_4);
		else if (name == "point-5") pSetting->QueryIntAttribute("value", &point_5);
		else if (name == "point-6") pSetting->QueryIntAttribute("value", &point_6);
		else if (name == "point-7") pSetting->QueryIntAttribute("value", &point_7);
		
		else if (name == "goomba-width") pSetting->QueryIntAttribute("value", &goomba_width);
		else if (name == "goomba-height") pSetting->QueryIntAttribute("value", &goomba_height);
		else if (name == "goomba-height-die") pSetting->QueryIntAttribute("value", &goomba_height_die);
		else if (name == "goomba-gravity") pSetting->QueryFloatAttribute("value", &goomba_gravity);
		else if (name == "goomba-walking-speed") pSetting->QueryFloatAttribute("value", &goomba_walking_speed);
		else if (name == "wing-goomba-gravity") pSetting->QueryFloatAttribute("value", &wing_goomba_gravity);
		else if (name == "wing-goomba-low-jump") pSetting->QueryFloatAttribute("value", &wing_goomba_low_jump);
		else if (name == "wing-goomba-high-jump") pSetting->QueryFloatAttribute("value", &wing_goomba_high_jump);
		else if (name == "goomba-bouncing-speed") pSetting->QueryFloatAttribute("value", &goomba_bouncing_speed);
		else if (name == "goomba-bouncing-up-speed") pSetting->QueryFloatAttribute("value", &goomba_bouncing_up_speed);
		else if (name == "goomba-die-timeout") pSetting->QueryIntAttribute("value", &goomba_die_timeout);
		else if (name == "goomba-bounce-die-timeout") pSetting->QueryIntAttribute("value", &goomba_bounce_die_timeout);
		else if (name == "wing-goomba-walk-timeout") pSetting->QueryIntAttribute("value", &wing_goomba_walk_timeout);

		else if (name == "koopa-gravity") pSetting->QueryFloatAttribute("value", &koopa_gravity);
		else if (name == "koopa-walking-speed") pSetting->QueryFloatAttribute("value", &koopa_walking_speed);
		else if (name == "wing-koopa-gravity") pSetting->QueryFloatAttribute("value", &wing_koopa_gravity);
		else if (name == "wing-koopa-jump-speed") pSetting->QueryFloatAttribute("value", &wing_koopa_jump_speed);
		else if (name == "koopa-bouncing-up-speed") pSetting->QueryFloatAttribute("value", &koopa_bouncing_up_speed);
		else if (name == "koopa-bouncing-speed") pSetting->QueryFloatAttribute("value", &koopa_bouncing_speed);
		else if (name == "wing-koopa-walk-timeout") pSetting->QueryIntAttribute("value", &wing_koopa_walk_timeout);
		else if (name == "koopa-shield-rolling-speed") pSetting->QueryFloatAttribute("value", &koopa_shield_rolling_speed);
		else if (name == "koopa-shield-timeout") pSetting->QueryIntAttribute("value", &koopa_shield_timeout);
		else if (name == "koopa-shield-standing-timeout") pSetting->QueryIntAttribute("value", &koopa_shield_standing_timeout);
		else if (name == "koopa-die-timeout") pSetting->QueryIntAttribute("value", &koopa_die_timeout);
		else if (name == "koopa-bounce-die-timeout") pSetting->QueryIntAttribute("value", &koopa_bounce_die_timeout);
		else if (name == "koopa-width") pSetting->QueryIntAttribute("value", &koopa_width);
		else if (name == "koopa-height") pSetting->QueryIntAttribute("value", &koopa_height);
		else if (name == "koopa-shield-height") pSetting->QueryIntAttribute("value", &koopa_shield_height);

		else if (name == "piranha-plant-width") pSetting->QueryIntAttribute("value", &piranha_plant_width);
		else if (name == "piranha-plant-height") pSetting->QueryIntAttribute("value", &piranha_plant_height);
		else if (name == "piranha-plant-delay-timeout") pSetting->QueryIntAttribute("value", &piranha_plant_delay_timeout);

		else if (name == "brick-bouncing-speed") pSetting->QueryFloatAttribute("value", &brick_bouncing_speed);
		else if (name == "brick-bounce-height") pSetting->QueryIntAttribute("value", &brick_bounce_height);
		else if (name == "brick-number-bounce-of-multi-coin") pSetting->QueryIntAttribute("value", &brick_number_bounce_of_multi_coin);
		
		else if (name == "coin-bouncing-speed") pSetting->QueryFloatAttribute("value", &coin_bouncing_speed);
		else if (name == "coin-bounce-height") pSetting->QueryIntAttribute("value", &coin_bounce_height);
		else if (name == "coin-drop-height") pSetting->QueryIntAttribute("value", &coin_drop_height);
		
		else if (name == "mushroom-gravity") pSetting->QueryFloatAttribute("value", &mushroom_gravity);
		else if (name == "mushroom-speed") pSetting->QueryFloatAttribute("value", &mushroom_speed);
		else if (name == "mushroom-bouncing-speed") pSetting->QueryFloatAttribute("value", &mushroom_bouncing_speed);
		else if (name == "mushroom-life-up") pSetting->QueryIntAttribute("value", &mushroom_life_up);
		
		else if (name == "pipe-height") pSetting->QueryIntAttribute("value", &pipe_height);
		else if (name == "pipe-adjust-width-can-go-through") pSetting->QueryFloatAttribute("value", &pipe_adjust_width_can_go_through);
		
		else if (name == "hud-x") pSetting->QueryFloatAttribute("value", &hud_x);
		else if (name == "hud-y") pSetting->QueryFloatAttribute("value", &hud_y);
		else if (name == "hud-width") pSetting->QueryIntAttribute("value", &hud_width);
		else if (name == "hud-height") pSetting->QueryIntAttribute("value", &hud_height);
		else if (name == "tex-bbox") pSetting->QueryIntAttribute("value", &id_tex_bbox);
		else if (name == "tex-hud-background") pSetting->QueryIntAttribute("value", &id_tex_hud_background);
		else if (name == "game-time") pSetting->QueryIntAttribute("value", &game_time);
		else if (name == "sprite-id-hud-and-font") pSetting->QueryIntAttribute("value", &sprite_id_hud_and_font);
		else if (name == "sprite-id-font-power-meter-normal") pSetting->QueryIntAttribute("value", &sprite_id_font_power_meter_normal);
		else if (name == "sprite-id-font-power-meter-running") pSetting->QueryIntAttribute("value", &sprite_id_font_power_meter_running);
		else if (name == "sprite-id-font-power-meter-p-normal") pSetting->QueryIntAttribute("value", &sprite_id_font_power_meter_p_normal);
		else if (name == "font-width") pSetting->QueryIntAttribute("value", &font_width);
		else if (name == "font-time-x") pSetting->QueryFloatAttribute("value", &font_time_x);
		else if (name == "font-time-y") pSetting->QueryFloatAttribute("value", &font_time_y);
		else if (name == "font-coin-x") pSetting->QueryFloatAttribute("value", &font_coin_x);
		else if (name == "font-coin-y") pSetting->QueryFloatAttribute("value", &font_coin_y);
		else if (name == "font-point-x") pSetting->QueryFloatAttribute("value", &font_point_x);
		else if (name == "font-point-y") pSetting->QueryFloatAttribute("value", &font_point_y);
		else if (name == "font-life-x") pSetting->QueryFloatAttribute("value", &font_life_x);
		else if (name == "font-life-y") pSetting->QueryFloatAttribute("value", &font_life_y);
		else if (name == "font-world-x") pSetting->QueryFloatAttribute("value", &font_world_x);
		else if (name == "font-world-y") pSetting->QueryFloatAttribute("value", &font_world_y);
		else if (name == "font-power-meter-x") pSetting->QueryFloatAttribute("value", &font_power_meter_x);
		else if (name == "font-power-meter-y") pSetting->QueryFloatAttribute("value", &font_power_meter_y);
		else if (name == "pause-timeout")  pSetting->QueryIntAttribute("value", &pause_timeout);
		//unknow setting
		else
		{
			DebugOut(L"[ERROR] Unknow setting: %s \n", ToLPCWSTR(name));
		}
		pSetting = pSetting->NextSiblingElement("setting");
	}
	DebugOut(L"[INFO] Done loading setting from %s\n", ToLPCWSTR(settingFile));
}

void CGameSetting::LoadIdAnimations(string name, int id)
{
	//mario
	if (name == "big-idle-left") id_ani_mario_idle_left = id;
	else if (name == "big-idle-right") id_ani_mario_idle_right = id;
	else if (name == "big-walking-left") id_ani_mario_walking_left = id;
	else if (name == "big-walking-right") id_ani_mario_walking_right = id;
	else if (name == "big-running-left") id_ani_mario_running_left = id;
	else if (name == "big-running-right") id_ani_mario_running_right = id;
	else if (name == "big-jump-walk-left") id_ani_mario_jump_walk_left = id;
	else if (name == "big-jump-walk-right") id_ani_mario_jump_walk_right = id;
	else if (name == "big-jump-run-left") id_ani_mario_jump_run_left = id;
	else if (name == "big-jump-run-right") id_ani_mario_jump_run_right = id;
	else if (name == "big-sit-left") id_ani_mario_sit_left = id;
	else if (name == "big-sit-right") id_ani_mario_sit_right = id;
	else if (name == "big-brace-left") id_ani_mario_brace_left = id;
	else if (name == "big-brace-right") id_ani_mario_brace_right = id;
	else if (name == "big-carry-idle-left") id_ani_mario_carry_idle_left = id;
	else if (name == "big-carry-idle-right") id_ani_mario_carry_idle_right = id;
	else if (name == "big-carry-jump-left") id_ani_mario_carry_jump_left = id;
	else if (name == "big-carry-jump-right") id_ani_mario_carry_jump_right = id;
	else if (name == "big-carry-walking-left") id_ani_mario_carry_walking_left = id;
	else if (name == "big-carry-walking-right") id_ani_mario_carry_walking_right = id;
	else if (name == "big-kick-left") id_ani_mario_kick_left = id;
	else if (name == "big-kick-right") id_ani_mario_kick_right = id;
	else if (name == "big-carry-change-dir") id_ani_mario_carry_change_dir = id;
	else if (name == "big-tele") id_ani_mario_tele = id;

	if (name == "raccoon-idle-left") id_ani_raccoon_idle_left = id;
	else if (name == "raccoon-idle-right") id_ani_raccoon_idle_right = id;
	else if (name == "raccoon-walking-left") id_ani_raccoon_walking_left = id;
	else if (name == "raccoon-walking-right") id_ani_raccoon_walking_right = id;
	else if (name == "raccoon-running-left") id_ani_raccoon_running_left = id;
	else if (name == "raccoon-running-right") id_ani_raccoon_running_right = id;
	else if (name == "raccoon-jump-walk-left") id_ani_raccoon_jump_walk_left = id;
	else if (name == "raccoon-jump-walk-right") id_ani_raccoon_jump_walk_right = id;
	else if (name == "raccoon-jump-run-left") id_ani_raccoon_jump_run_left = id;
	else if (name == "raccoon-jump-run-right") id_ani_raccoon_jump_run_right = id;
	else if (name == "raccoon-free-falling-left") id_ani_raccoon_free_falling_left = id;
	else if (name == "raccoon-free-falling-right") id_ani_raccoon_free_falling_right = id;
	else if (name == "raccoon-slow-falling-left") id_ani_raccoon_slow_falling_left = id;
	else if (name == "raccoon-slow-falling-right") id_ani_raccoon_slow_falling_right = id;
	else if (name == "raccoon-fly-falling-left") id_ani_raccoon_fly_falling_left = id;
	else if (name == "raccoon-fly-falling-right") id_ani_raccoon_fly_falling_right = id;
	else if (name == "raccoon-flying-left") id_ani_raccoon_flying_left = id;
	else if (name == "raccoon-flying-right") id_ani_raccoon_flying_right = id;
	else if (name == "raccoon-sit-left") id_ani_raccoon_sit_left = id;
	else if (name == "raccoon-sit-right") id_ani_raccoon_sit_right = id;
	else if (name == "raccoon-brace-left") id_ani_raccoon_brace_left = id;
	else if (name == "raccoon-brace-right") id_ani_raccoon_brace_right = id;
	else if (name == "raccoon-carry-idle-left") id_ani_raccoon_carry_idle_left = id;
	else if (name == "raccoon-carry-idle-right") id_ani_raccoon_carry_idle_right = id;
	else if (name == "raccoon-carry-jump-left") id_ani_raccoon_carry_jump_left = id;
	else if (name == "raccoon-carry-jump-right") id_ani_raccoon_carry_jump_right = id;
	else if (name == "raccoon-carry-walking-left") id_ani_raccoon_carry_walking_left = id;
	else if (name == "raccoon-carry-walking-right") id_ani_raccoon_carry_walking_right = id;
	else if (name == "raccoon-kick-left") id_ani_raccoon_kick_left = id;
	else if (name == "raccoon-kick-right") id_ani_raccoon_kick_right = id;
	else if (name == "raccoon-carry-change-dir") id_ani_raccoon_carry_change_dir = id;
	else if (name == "raccoon-tele") id_ani_raccoon_tele = id;

	if (name == "mario-die") id_ani_mario_die = id;
	else if (name == "small-idle-left") id_ani_mario_small_idle_left = id;
	else if (name == "small-idle-right") id_ani_mario_small_idle_right = id;
	else if (name == "small-walking-left") id_ani_mario_small_walking_left = id;
	else if (name == "small-walking-right") id_ani_mario_small_walking_right = id;
	else if (name == "small-running-left") id_ani_mario_small_running_left = id;
	else if (name == "small-running-right") id_ani_mario_small_running_right = id;
	else if (name == "small-jump-walk-left") id_ani_mario_small_jump_walk_left = id;
	else if (name == "small-jump-walk-right") id_ani_mario_small_jump_walk_right = id;
	else if (name == "small-jump-run-left") id_ani_mario_small_jump_run_left = id;
	else if (name == "small-jump-run-right") id_ani_mario_small_jump_run_right = id;
	else if (name == "small-brace-left") id_ani_mario_small_brace_left = id;
	else if (name == "small-brace-right") id_ani_mario_small_brace_right = id;
	else if (name == "small-carry-idle-left") id_ani_mario_small_carry_idle_left = id;
	else if (name == "small-carry-idle-right") id_ani_mario_small_carry_idle_right = id;
	else if (name == "small-carry-jump-left") id_ani_mario_small_carry_jump_left = id;
	else if (name == "small-carry-jump-right") id_ani_mario_small_carry_jump_right = id;
	else if (name == "small-carry-walking-left") id_ani_mario_small_carry_walking_left = id;
	else if (name == "small-carry-walking-right") id_ani_mario_small_carry_walking_right = id;
	else if (name == "small-kick-left") id_ani_mario_small_kick_left = id;
	else if (name == "small-kick-right") id_ani_mario_small_kick_right = id;
	else if (name == "small-carry-change-dir") id_ani_mario_small_carry_change_dir = id;
	else if (name == "small-tele") id_ani_mario_small_tele = id;
	else if (name == "mario-die") id_ani_mario_die = id;
	else if (name == "mario-invisible") id_ani_mario_invisible = id;
	//goomba
	if (name == "goomba-walking") id_ani_goomba_walking = id;
	else if (name == "goomba-die") id_ani_goomba_die = id;
	else if (name == "goomba-bounce-die") id_ani_goomba_bounce_die = id;
	else if (name == "red-goomba-walking") id_ani_red_goomba_walking = id;
	else if (name == "red-goomba-die") id_ani_red_goomba_die = id;
	else if (name == "red-goomba-bounce-die") id_ani_red_goomba_bounce_die = id;
	else if (name == "wing-jump") id_ani_wing_jump = id;
	else if (name == "wing-walk") id_ani_wing_walk = id;
	//koopa
	if (name == "koopa-walking-left") id_ani_koopa_walking_left = id;
	else if (name == "koopa-walking-right") id_ani_koopa_walking_right = id;
	else if (name == "red-koopa-walking-left") id_ani_red_koopa_walking_left = id;
	else if (name == "red-koopa-walking-right") id_ani_red_koopa_walking_right = id;
	else if (name == "wing-left") id_ani_wing_left = id;
	else if (name == "wing-right") id_ani_wing_right = id;
	else if (name == "koopa-shield-idle-down") id_ani_koopa_shield_idle_down = id;
	else if (name == "koopa-shield-idle-up") id_ani_koopa_shield_idle_up = id;
	else if (name == "koopa-shield-standing-down") id_ani_koopa_shield_standing_down = id;
	else if (name == "koopa-shield-standing-up") id_ani_koopa_shield_standing_up = id;
	else if (name == "koopa-shield-rolling-down") id_ani_koopa_shield_rolling_down = id;
	else if (name == "koopa-shield-rolling-up") id_ani_koopa_shield_rolling_up = id;
	else if (name == "red-koopa-shield-idle-down") id_ani_red_koopa_shield_idle_down = id;
	else if (name == "red-koopa-shield-idle-up") id_ani_red_koopa_shield_idle_up = id;
	else if (name == "red-koopa-shield-standing-down") id_ani_red_koopa_shield_standing_down = id;
	else if (name == "red-koopa-shield-standing-up") id_ani_red_koopa_shield_standing_up = id;
	else if (name == "red-koopa-shield-rolling-down") id_ani_red_koopa_shield_rolling_down = id;
	else if (name == "red-koopa-shield-rolling-up") id_ani_red_koopa_shield_rolling_up = id;
	//piranha plant
	if (name == "piranha-plant-left-down") id_ani_piranha_plant_left_down = id;
	else if (name == "piranha-plant-left-up") id_ani_piranha_plant_left_up = id;
	else if (name == "piranha-plant-right-down") id_ani_piranha_plant_right_down = id;
	else if (name == "piranha-plant-right-up") id_ani_piranha_plant_right_up = id;
	else if (name == "horizontal-piranha-plant") id_ani_horizontal_piranha_plant = id;

	//brick
	else if (name == "brick") id_ani_brick = id;
	else if (name == "question-brick") id_ani_question_brick = id;
	else if (name == "block-brick") id_ani_block_brick = id;
	//coin
	else if (name == "coin-spinning") id_ani_coin_spinning = id;
	else if (name == "coin-idle") id_ani_coin_idle = id;
	else if (name == "coin-drop") id_ani_coin_drop = id;
	//mushroom
	else if (name == "red-mushroom") id_ani_red_mushroom = id;
	else if (name == "green-mushroom") id_ani_green_mushroom = id;
	//hud
	else if (name == "hud") id_ani_hud = id;
	else if (name == "power-meter-p-running") id_font_power_meter_p_running = id;
	//pause
	else if (name == "pause") id_ani_pause = id;

	else if (name == "pause-be-hitted") id_ani_pause_be_hitted = id;
}


CGameSetting* CGameSetting::GetInstance()
{
	if (__instance == NULL) __instance = new CGameSetting();
	return __instance;
}