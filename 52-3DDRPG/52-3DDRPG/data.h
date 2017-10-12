#pragma once

//#include <string>

const int MENU_MAP_UP = 200;
const int MENU_MAP_LEFT = 200;

using namespace std;

class Data_c {
private:
	int scenario;
	int stage;
	int dir;
	int dungeonX, dungeonY;
	int wallType[MAP_SIZE_X][MAP_SIZE_Y];
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
		double magnification;	//�X�L�����ʂ̃X�e�[�^�X�ˑ��̔{��*1000
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
		int soubi[2];
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

	int GetItemPoint(int num, int sort);			//0:num 1:type 2:effect1 3:effect2 4:point1 5:point2 6:area
	string GetItemText(int num, int sort);			//0:name 1:explain

	int GetSoubiPoint(int num, int sort);			//0:num 1:type 2:effect 3:point 4:area
	string GetSoubiText(int num, int sort);			//0:name 1:explain

	int GetSkillPoint(int num, int sort);			//0:num 1:MP 2:effect 3:status 4:magnification 5:area
	string GetSkillText(int num, int sort);			//0:name 1:explain

	int GetCharacterPoint(int num, int sort);		//0:HPMAX 1:MPMAX 2:HP 3:MP 4:STR 5:VIT 6:AGI 7:INT 8:Image 9:soubi[1] 10:soubi[2]
	void SetCharacterPoint(int num, int sort, int point);	//0:HPMAX 1:MPMAX 2:HP 3:MP 4:STR 5:VIT 6:AGI 7:INT 8:Image 9:soubi[1] 10:soubi[2]

	int GetCharacterSkillCode(int num, int order);	
	string GetCharacterName(int num);				

	int GetScenario();
	int GetStage();
	int GetDungeonX();
	int GetDungeonY();
	int GetDir();

	void SetScenario(int i);
	void SetStage(int i);
	void SetDungeonX(int i);
	void SetDungeonY(int i);
	void SetDir(int i);

	int GetMapFlag(int scenario, int stage, int x, int y);
	int GetEventFlag(int scenario, int num);
	int GetPlayCount();
	int GetWallType(int x, int y);

	void SetMapFlag(int scenario, int stage, int x, int y, int i);
	void SetEventFlag(int scenario, int num, int i);
	void SetPlayCount(int i);
	void AddPlayCount();
	void SetWallType(int x, int y, int type);
};