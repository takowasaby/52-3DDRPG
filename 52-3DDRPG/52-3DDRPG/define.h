#pragma once

#include "DxLib.h"

#include <vector>
#include <map>
#include <string>
#include <list>
#include <fstream>

using namespace std;

//TextBox用--------------------------------------------------------------
//ウィンドウモードに関する列挙体
enum WindowMode {
	readMode,	//選択できないメッセージ用
	pageMode,	//上下で選択、左右でページ移動
	scrollMode,	//スクロールで移動
	logMode,		//最後から表示
	infoMode		//情報表示
};
//-------------------------------------------------------------------------

//dungeon用--------------------------------------------------------------
const int MAP_SIZE_X = 25;
const int MAP_SIZE_Y = 25;

const int WALL_SCENARIO = 5;
const int WALL_SIDE = 10;
const int WALL_TYPE = 3;
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
const int EVENT_ACTION_STYLE = 1024;
const int EVENT_ACTION_SOUND = 2048;
const int EVENT_ACTION_LOOPSOUND = 4096;
const int EVENT_ACTION_STOPSOUND = 8192;

const int EVENT_WRITESTYLE_DEFAULT = 1;
const int EVENT_WRITESTYLE_ONEBYONE = 2;
const int EVENT_WRITESTYLE_BLACK = 4;
//-----------------------------------------------------------------------

//data用-----------------------------------------------------------------
const int SCENARIO_SIZE = 5;
const int STAGE_SIZE = 5;
const int ITEM_TYPE_NUM = 19;
const int ITEM_TYPE_SIZE = 3;
const int ITEM_FLAG_MAX = 99;
const int NAME_SIZE = 32;
const int SKILL_CODE_SIZE = 8;
const int EFFECT_SIZE = 8;
const int ITEM_SIZE = 64;
const int SOUBI_SIZE = 64;
const int SOUBI_FLAG_MAX = 99;
const int SKILL_SIZE = 64;
const int CHARACTER_SIZE = 4;
const int EVENT_SIZE = 64;
const int STATE_SIZE = 1;
const int ENEMY_SIZE = 5;

struct value {
	int base, calc;
};
struct characterData {
	int num;								//キャラクターのナンバリング
	string name;							//キャラクターの名前
	int flag;								//キャラクターがパーティにいるかどうか
	int soubi[2] = {-1, -1};				//キャラクターの装備
	value hp, mp, str, vit, agi, intel;		//キャラクターのステータス
	int skillCode[SKILL_SIZE] = {};			//キャラクターがスキルを覚えているかどうか
	bool state[STATE_SIZE] = {};			//キャラクターの状態異常(0:死亡)
	int image;								//キャラクターの画像ハンドル
};
struct enemyData {
	int num;								//キャラクターのナンバリング
	string name;							//キャラクターの名前
	value hp, mp, str, vit, agi, intel;		//キャラクターのステータス
	int skillCode[SKILL_SIZE] = {};			//キャラクターがスキルを覚えているかどうか
	bool state[STATE_SIZE] = {};			//キャラクターの状態異常(0:死亡)
	int operate;
	int image;								//キャラクターの画像ハンドル
};
struct skillData{
	int num;						//スキルのナンバリング
	string name;					//スキルの名前
	int target;					//スキルの対象(0:味方、1:敵)
	int mp;							//スキルの消費MP	
	int effect;						//スキルの効果(0:ダメージ、 1:HP回復、2:MP回復、3:STR上昇、4:VIT上昇、5:AGI上昇、6:INT上昇、7:蘇生)
	int status;						//スキルの効果に依存されるステータス
	int magnification;				//スキル効果のステータス依存の倍率*1000
	int area;						//スキル効果の範囲(0:単体、1:全体)
	string explain;					//スキルの説明文
};
struct itemData {
	int num;						//アイテムのナンバリング
	string name;					//アイテムの名前
	int flag;						//アイテムを所持している個数
	int target;					//アイテムの対象(0:味方、1:敵)
	int type;						//アイテムの種類(0:消耗品、1:だいじなもの)
	int effect1, effect2;			//アイテムの効果(0:ダメージ、 1:HP回復、2:MP回復、3:STR上昇、4:VIT上昇、5:AGI上昇、6:INT上昇、7:蘇生)
	int point1, point2;				//アイテム効果の固定値
	int area;						//アイテム効果の範囲(0:単体、1:全体)
	string explain;					//アイテムの説明文
};
struct soubiData {
	int num;						//装備のナンバリング
	string name;					//装備の名前
	int flag;						//装備を所持している個数
	int type;						//装備の種類(0:武器、1:アクセサリー)
	int effect;						//装備の効果(0:HP上昇、1:MP上昇、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇)
	int point;						//装備効果の固定値
	int area;						//武器の攻撃範囲(0:単体、1:全体)
	string explain;					//装備の説明文
};


//------------------------------------------------------------------------

//room用-----------------------------------------------------------------
const int ROOM_MAXSIZE_X = 25;
const int ROOM_MAXSIZE_Y = 25;
//const int ROOM_EVENTTIMELINE = 15;

const float ROOM_RATIO = 0.5;
const int ROOM_WALL_SIZE_Y = (int)(420 * ROOM_RATIO);
const int ROOM_WALL_SIZE_X = (int)(104 * ROOM_RATIO);
const int ROOM_SHIFT_SIZE_X = (int)(104 * ROOM_RATIO);
const int ROOM_SHIFT_SIZE_Y = (int)(60 * ROOM_RATIO);
const int ROOM_FLOOR_SIZE_X = (int)(208 * ROOM_RATIO);
const int ROOM_FLOOR_SIZE_Y = (int)(120 * ROOM_RATIO);
const int ROOM_FLOOR_HALFSIZE_X = (int)(ROOM_FLOOR_SIZE_X / 2);
const int ROOM_FLOOR_HALFSIZE_Y = (int)(ROOM_FLOOR_SIZE_Y / 2);
const int ROOM_SELECT_SIZE_Y = (int)(360 * ROOM_RATIO);
const int ROOM_SELECT_SIZE_X = (int)(208 * ROOM_RATIO);
const int ROOM_FURNITURE_MAX = 100;
const int ROOM_FURNITURE_LENGTH = (int)(ROOM_WALL_SIZE_X * 2);
const int ROOM_POINT_X = 320;
const int ROOM_POINT_Y = 240;

enum Effect{
	attack,
	healHp,
	healMp,
	buffStr,
	buffVit,
	buffAgi,
	buffInt,
	reviv
};
//------------------------------------------------------------------------

//BattleScene用-----------------------------------------------------------------
struct Param {
	int current, base;
};
enum CommandType {
	skill,
	item,
	defence
};
struct Command {
	CommandType commandType;
	string name;
	int cost;
	bool forParty;
	int target;	//敵か味方か,何番目か(マイナス値なら全体)
	int value[EFFECT_SIZE];
};
/*struct Character_t {
	int flag;
	int soubi[2];
	int HPMAX, MPMAX, STR, VIT, AGI, INT;
	int HP, MP;
	char name[NAME_SIZE];
	int skillCode[SKILL_CODE_SIZE];
	int Image;
};
struct CharacterData {
	bool flag;
	int soubi[2];
	Param hp, mp, str, vit, agi, intel;
	std::string name;
	int skillCode[SKILL_CODE_SIZE];
	int Image;
};*/
const int ENEMY_SKILL_SIZE = 4;
const int OPINIONWINDOW_NUM = 3;
//------------------------------------------------------------------------

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
#include "music.h"
#include "room.h"
#include "BattleManager.h"
#include "scenario.h"
#include "EventList.h"