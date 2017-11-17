#pragma once

#include "DxLib.h"

#include <vector>
#include <map>
#include <string>
#include <list>
#include <fstream>

using namespace std;

//TextBox�p--------------------------------------------------------------
//�E�B���h�E���[�h�Ɋւ���񋓑�
enum WindowMode {
	readMode,	//�I���ł��Ȃ����b�Z�[�W�p
	pageMode,	//�㉺�őI���A���E�Ńy�[�W�ړ�
	scrollMode,	//�X�N���[���ňړ�
	logMode,		//�Ōォ��\��
	infoMode		//���\��
};
//-------------------------------------------------------------------------

//dungeon�p--------------------------------------------------------------
const int MAP_SIZE_X = 25;
const int MAP_SIZE_Y = 25;

const int WALL_SCENARIO = 5;
const int WALL_SIDE = 10;
const int WALL_TYPE = 3;
//-----------------------------------------------------------------------

//event�p----------------------------------------------------------------
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

//data�p-----------------------------------------------------------------
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
	int num;								//�L�����N�^�[�̃i���o�����O
	string name;							//�L�����N�^�[�̖��O
	int flag;								//�L�����N�^�[���p�[�e�B�ɂ��邩�ǂ���
	int soubi[2] = {-1, -1};				//�L�����N�^�[�̑���
	value hp, mp, str, vit, agi, intel;		//�L�����N�^�[�̃X�e�[�^�X
	int skillCode[SKILL_SIZE] = {};			//�L�����N�^�[���X�L�����o���Ă��邩�ǂ���
	bool state[STATE_SIZE] = {};			//�L�����N�^�[�̏�Ԉُ�(0:���S)
	int image;								//�L�����N�^�[�̉摜�n���h��
};
struct enemyData {
	int num;								//�L�����N�^�[�̃i���o�����O
	string name;							//�L�����N�^�[�̖��O
	value hp, mp, str, vit, agi, intel;		//�L�����N�^�[�̃X�e�[�^�X
	int skillCode[SKILL_SIZE] = {};			//�L�����N�^�[���X�L�����o���Ă��邩�ǂ���
	bool state[STATE_SIZE] = {};			//�L�����N�^�[�̏�Ԉُ�(0:���S)
	int operate;
	int image;								//�L�����N�^�[�̉摜�n���h��
};
struct skillData{
	int num;						//�X�L���̃i���o�����O
	string name;					//�X�L���̖��O
	int target;					//�X�L���̑Ώ�(0:�����A1:�G)
	int mp;							//�X�L���̏���MP	
	int effect;						//�X�L���̌���(0:�_���[�W�A 1:HP�񕜁A2:MP�񕜁A3:STR�㏸�A4:VIT�㏸�A5:AGI�㏸�A6:INT�㏸�A7:�h��)
	int status;						//�X�L���̌��ʂɈˑ������X�e�[�^�X
	int magnification;				//�X�L�����ʂ̃X�e�[�^�X�ˑ��̔{��*1000
	int area;						//�X�L�����ʂ͈̔�(0:�P�́A1:�S��)
	string explain;					//�X�L���̐�����
};
struct itemData {
	int num;						//�A�C�e���̃i���o�����O
	string name;					//�A�C�e���̖��O
	int flag;						//�A�C�e�����������Ă����
	int target;					//�A�C�e���̑Ώ�(0:�����A1:�G)
	int type;						//�A�C�e���̎��(0:���Օi�A1:�������Ȃ���)
	int effect1, effect2;			//�A�C�e���̌���(0:�_���[�W�A 1:HP�񕜁A2:MP�񕜁A3:STR�㏸�A4:VIT�㏸�A5:AGI�㏸�A6:INT�㏸�A7:�h��)
	int point1, point2;				//�A�C�e�����ʂ̌Œ�l
	int area;						//�A�C�e�����ʂ͈̔�(0:�P�́A1:�S��)
	string explain;					//�A�C�e���̐�����
};
struct soubiData {
	int num;						//�����̃i���o�����O
	string name;					//�����̖��O
	int flag;						//�������������Ă����
	int type;						//�����̎��(0:����A1:�A�N�Z�T���[)
	int effect;						//�����̌���(0:HP�㏸�A1:MP�㏸�A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸)
	int point;						//�������ʂ̌Œ�l
	int area;						//����̍U���͈�(0:�P�́A1:�S��)
	string explain;					//�����̐�����
};


//------------------------------------------------------------------------

//room�p-----------------------------------------------------------------
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

//BattleScene�p-----------------------------------------------------------------
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
	int target;	//�G��������,���Ԗڂ�(�}�C�i�X�l�Ȃ�S��)
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