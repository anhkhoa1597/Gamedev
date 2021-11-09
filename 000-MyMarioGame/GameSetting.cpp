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
		else if (name == "mario-tele-speed") pSetting->QueryFloatAttribute("value", &mario_tele_speed);
		else if (name == "mario-accel-walk-x") pSetting->QueryFloatAttribute("value", &mario_accel_walk_x);
		else if (name == "mario-accel-run-x") pSetting->QueryFloatAttribute("value", &mario_accel_run_x);
		else if (name == "mario-jump-speed-y") pSetting->QueryFloatAttribute("value", &mario_jump_speed_y);
		else if (name == "mario-jump-run-speed-y") pSetting->QueryFloatAttribute("value", &mario_jump_run_speed_y);
		else if (name == "mario-gravity") pSetting->QueryFloatAttribute("value", &mario_gravity);
		else if (name == "mario-jump-deflect-speed") pSetting->QueryFloatAttribute("value", &mario_jump_deflect_speed);
		else if (name == "mario-untouchabletime") pSetting->QueryFloatAttribute("value", &mario_untouchable_time);
		else if (name == "mario-life") pSetting->QueryIntAttribute("value", &mario_life);
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

		//unknow setting
		else
		{
			DebugOut(L"[ERROR] Unknow setting: %s \n", ToLPCWSTR(name));
			return;
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
	else if (name == "big-kick-left") id_ani_mario_kick_left = id;
	else if (name == "big-kick-right") id_ani_mario_kick_right = id;
	else if (name == "big-tele") id_ani_mario_tele = id;
	else if (name == "mario-die") id_ani_mario_die = id;
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
	else if (name == "small-kick-left") id_ani_mario_small_kick_left = id;
	else if (name == "small-kick-right") id_ani_mario_small_kick_right = id;
	else if (name == "small-tele") id_ani_mario_small_tele = id;
	else if (name == "mario-die") id_ani_mario_die = id;
	//goomba
	else if (name == "goomba-walking") id_ani_goomba_walking = id;
	else if (name == "goomba-die") id_ani_goomba_die = id;
	else if (name == "goomba-bounce-die") id_ani_goomba_bounce_die = id;
	else if (name == "red-goomba-walking") id_ani_red_goomba_walking = id;
	else if (name == "red-goomba-die") id_ani_red_goomba_die = id;
	else if (name == "red-goomba-bounce-die") id_ani_red_goomba_bounce_die = id;
	else if (name == "wing-jump") id_ani_wing_jump = id;
	else if (name == "wing-walk") id_ani_wing_walk = id;
	//koopa
	else if (name == "koopa-walking-left") id_ani_koopa_walking_left = id;
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

	else if (name == "hud") id_ani_hud = id;
}


CGameSetting* CGameSetting::GetInstance()
{
	if (__instance == NULL) __instance = new CGameSetting();
	return __instance;
}