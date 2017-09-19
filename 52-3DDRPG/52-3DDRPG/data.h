#pragma once

#include <string>
using namespace std;

const int SCENARIO_SIZE = 5;
const int STAGE_SIZE = 5;
const int ITEM_TYPE_SIZE = 3;
const int ITEM_SIZE = 32;
const int ITEM_FLAG_MAX = 99;
const int NAME_SIZE = 32;
const int SKILL_CODE_SIZE = 8;
const int ITEM_SIZE = 64;
const int SOUBI_SIZE = 64;
const int SOUBI_FLAG_MAX = 99;
const int SKILL_SIZE = 64;
const int CHARACTER_SIZE = 4;
const int EVENT_SIZE = 64;

class Data_c {
private:
	int scenario;
	int dungeonX, dungeonY;
	int mapFlag[SCENARIO_SIZE][STAGE_SIZE][MAP_SIZE_X][MAP_SIZE_Y];
	int eventFlag[SCENARIO_SIZE][EVENT_SIZE];
	int playCount;
//	int itemFlag[SCENARIO_SIZE][ITEM_TYPE_SIZE][ITEM_SIZE];

	struct Skill_t {
		int num;				//�X�L���ŗL�̐���
		char name[64];			//�X�L���̖��O
		int MP;					//�X�L���̏���MP
		int effect;				//�X�L���̌���(0:HP�񕜁A1:MP�񕜁A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸�A6:�_���[�W)
		int status;				//�X�L���̌��ʂɈˑ������X�e�[�^�X
		double magnification;	//�X�L�����ʂ̃X�e�[�^�X�ˑ��̔{��
		int area;				//�X�L�����ʂ͈̔�(0:�P�́A1:�S��)
		char explain[64];		//�X�L���̐�����
	};
	Skill_t skill[SKILL_SIZE];

	struct Item_t {
		int flag;				//�A�C�e�����������Ă����
		int num;				//�A�C�e���ŗL�̐���
		char name[64];			//�A�C�e���̖��O
		int type;				//�A�C�e���̎��(0:���Օi�A1:�������Ȃ���)
		int effect1, effect2;	//�A�C�e���̌���(0:HP�񕜁A1:MP�񕜁A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸�A6:�_���[�W)
		int point1, point2;		//�A�C�e�����ʂ̌Œ�l
		int area;				//�A�C�e�����ʂ͈̔�(0:�P�́A1:�S��)
		char explain[64];		//�A�C�e���̐�����
	};
	Item_t item[ITEM_SIZE];

	struct Soubi_t {
		int flag;				//�������������Ă����
		int num;				//�����ŗL�̐���
		char name[64];			//�����̖��O
		int type;				//�����̎��(0:����A1:�A�N�Z�T���[)
		int effect;				//�����̌���(0:HP�㏸�A1:MP�㏸�A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸)
		int point;				//�������ʂ̌Œ�l
		int area;				//����̍U���͈�(0:�P�́A1:�S��)
		char explain[64];		//�����̐�����
	};
	Soubi_t soubi[SOUBI_SIZE];
	
	struct Character_t {
		int flag;
		int HPMAX, MPMAX, STR, VIT, AGI, INT;
		int HP, MP;
		char name[NAME_SIZE];
		int skillCode[SKILL_CODE_SIZE];
		int Image;
	};
	Character_t character[CHARACTER_SIZE];
	
public:
	Data_c();		//�R���X�g���N�^
	~Data_c();		//�f�X�g���N�^

	void LoadAll(int scenario);
	void ItemLoad(int scenario);
	void SoubiLoad(int scenario);
	void SkillLoad(int scenario);
	void CharacterLoad(int scenario);

	int GetItemFlag(int num);
	int GetSoubiFlag(int num);
	int GetCharacterFlag(int num);

	void CalcItemFlag(int num, int vary);
	void CalcSoubiFlag(int num, int vary);
	void SetCharacterFlag(int num, int vary);

	int GetItemPoint(int num, int sort);
	string GetItemText(int num, int sort);

	int GetSoubiPoint(int num, int sort);
	string GetSoubiText(int num, int sort);

	int GetSkillPoint(int num, int sort);
	string GetSkillText(int num, int sort);

	int GetCharacterPoint(int num, int sort);
	int GetCharacterSkillCode(int num, int order);
	string GetCharacterName(int num);

	int GetScenario();
	int GetDungeonX();
	int GetDungeonY();

	void SetScenario(int i);
	void SetDungeonX(int i);
	void SetDungeonY(int i);

	int GetMapFlag(int scenario, int stage, int x, int y);
	int GetEventFlag(int scenario,int num);
	int GetPlayCount();

	void SetMapFlag(int scenario, int stage, int x, int y, int i);
	void SetEventFlag(int scenario, int num, int i);
	void SetPlayCount(int i);
	void AddPlayCount();
};