#pragma once

#include "DxLib.h"

//dungeon用--------------------------------------------------------------
const int MAP_SIZE_X = 25;
const int MAP_SIZE_Y = 25;

const int WALL_SCENARIO = 5;
const int WALL_SIDE = 10;
const int WALL_TYPE = 1;
//-----------------------------------------------------------------------

//event用----------------------------------------------------------------
const int EVENT_MODE_DEFAULTSIZE = 1;
const int EVENT_MODE_RESIZE = 2;
const int EVENT_MODE_COMPLETE = 4;

const int EVENT_ACTION_POSITION = 1;
const int EVENT_ACTION_OPACITY = 2;
const int EVENT_ACTION_SCALE = 4;
const int EVENT_ACTION_TEXT = 8;
const int EVENT_ACTION_TURN = 16;
const int EVENT_ACTION_LIGHT = 32;
const int EVENT_ACTION_DARK = 64;
const int EVENT_ACTION_TEXTCLEAR = 128;
const int EVENT_ACTION_WAIT = 256;
const int EVENT_ACTION_END = 512;
//-----------------------------------------------------------------------

//data用-----------------------------------------------------------------
const int SCENARIO_SIZE = 5;
const int STAGE_SIZE = 5;
const int ITEM_TYPE_SIZE = 3;
const int ITEM_FLAG_MAX = 99;
const int NAME_SIZE = 32;
const int SKILL_CODE_SIZE = 8;
const int ITEM_SIZE = 64;
const int SOUBI_SIZE = 64;
const int SOUBI_FLAG_MAX = 99;
const int SKILL_SIZE = 64;
const int CHARACTER_SIZE = 4;
const int EVENT_SIZE = 64;
//------------------------------------------------------------------------

//BattleScene用-----------------------------------------------------------------
struct Param {
	int current, base;
};
struct Character_t {
	int flag;
	int soubi[2];
	int HPMAX, MPMAX, STR, VIT, AGI, INT;
	int HP, MP;
	char name[NAME_SIZE];
	int skillCode[SKILL_CODE_SIZE];
	int Image;
};
struct CharacterData {
	int flag;
	int soubi[2];
	Param hp, mp, str, vit, agi, intel;
	char name[NAME_SIZE];
	int skillCode[SKILL_CODE_SIZE];
	int Image;
};
//------------------------------------------------------------------------

#include <math.h>
#include <map>
#include <vector>
#include <string>
#include "control.h"
#include "data.h"
#include "dungeon.h"
#include "ECharaData.h"
#include "EDrawSetting.h"
#include "EQueueData.h"
#include "Event.h"
#include "fps.h"
#include "option.h"
#include "save_load.h"
#include "TextBox.h"
#include "title.h"
#include "menu.h"
#include "Sound.h"
#include "BattleManager.h"