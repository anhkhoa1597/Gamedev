#include "GameSetting.h"

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
		else if (name == "mario-running-speed") pSetting->QueryFloatAttribute("value", &mario_running_speed);
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
		else if (name == "goomba-die-timeout") pSetting->QueryIntAttribute("value", &goomba_die_timeout);
		else if (name == "goomba-bounce-die-timeout") pSetting->QueryIntAttribute("value", &goomba_bounce_die_timeout);
		else if (name == "wing-goomba-walk-timeout") pSetting->QueryIntAttribute("value", &wing_goomba_walk_timeout);
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