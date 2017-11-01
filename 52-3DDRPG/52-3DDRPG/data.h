#pragma once

//#include <string>

class Data_c {
private:
	int scenario;
	int stage;
	int dir;
	int room;
	int dungeonX, dungeonY;
	int wallType[MAP_SIZE_X][MAP_SIZE_Y];
	int mapFlag[SCENARIO_SIZE][STAGE_SIZE][MAP_SIZE_X][MAP_SIZE_Y];
	int eventFlag[SCENARIO_SIZE][EVENT_SIZE];
	int playCount;
	string GoalText[SCENARIO_SIZE][EVENT_SIZE];
	//	int itemFlag[SCENARIO_SIZE][ITEM_TYPE_SIZE][ITEM_SIZE];
	int EventCallFlag;

	int BMode;
	int BScene;
	int controlMode;
	int eventScene;
	int titleScene;
	int gameScene;
	
	characterData character[CHARACTER_SIZE];
	skillData skill[SKILL_SIZE];
	itemData item[ITEM_SIZE];
	soubiData soubi[SOUBI_SIZE];
	
	/*
	struct Skill_t {
		int num;				//�X�L���̃i���o�����O
		string name;			//�X�L���̖��O
		int MP;					//�X�L���̏���MP
		int effect;				//�X�L���̌���(0:HP�񕜁A1:MP�񕜁A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸�A6:�_���[�W)
		int status;				//�X�L���̌��ʂɈˑ������X�e�[�^�X
		double magnification;	//�X�L�����ʂ̃X�e�[�^�X�ˑ��̔{��*1000
		int area;				//�X�L�����ʂ͈̔�(0:�P�́A1:�S��)
		char explain[512];		//�X�L���̐�����
	};
	Skill_t skill[SKILL_SIZE];

	struct Item_t {
		int flag;				//�A�C�e���̃i���o�����O
		int num;				//�A�C�e���ŗL�̐���
		char name[64];			//�A�C�e���̖��O
		int type;				//�A�C�e���̎��(0:���Օi�A1:�������Ȃ���)
		int effect1, effect2;	//�A�C�e���̌���(0:HP�񕜁A1:MP�񕜁A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸�A6:�_���[�W)
		int point1, point2;		//�A�C�e�����ʂ̌Œ�l
		int area;				//�A�C�e�����ʂ͈̔�(0:�P�́A1:�S��)
		char explain[512];		//�A�C�e���̐�����
	};
	Item_t item[ITEM_SIZE];

	struct Soubi_t {
		int flag;				//�������������Ă����
		int num;				//�����̃i���o�����O
		char name[64];			//�����̖��O
		int type;				//�����̎��(0:����A1:�A�N�Z�T���[)
		int effect;				//�����̌���(0:HP�㏸�A1:MP�㏸�A2:STR�㏸�A3:VIT�㏸�A4:AGI�㏸�A5:INT�㏸)
		int point;				//�������ʂ̌Œ�l
		int area;				//����̍U���͈�(0:�P�́A1:�S��)
		char explain[512];		//�����̐�����
	};
	Soubi_t soubi[SOUBI_SIZE];

	/*struct Character_t {
		int flag;
		int soubi[2] = {-1, -1};
		int HPMAX, MPMAX, STR, VIT, AGI, INT;
		int HP, MP;
		char name[NAME_SIZE];
		int skillCode[SKILL_SIZE] = {};
		int Image;
	};*/
	//Character_t character[CHARACTER_SIZE];
	
public:
	Data_c();		//�R���X�g���N�^
					//	Data_c(int* mode, int* event_scene, int* title_scene, int* game_scene);
	~Data_c();		//�f�X�g���N�^

	void LoadAll(int s);
	void GoalLoad(int s);
	void ItemLoad(int s);
	void SoubiLoad(int s);
	void SkillLoad(int s);
	void CharacterLoad(int s);

	void CalcItemFlag(int num, int vary);
	void CalcSoubiFlag(int num, int vary);
	void SetCharacterFlag(int num, int vary);

	string GetGoalText(int s, int num);

	int GetItemPoint(int num, int sort);			//0:num 1:type 2:effect1 3:effect2 4:point1 5:point2 6:area 7:target 8:flag
	void SetItemPoint(int num, int sort, int point);
	string GetItemText(int num, int sort);			//0:name 1:explain
	int ItemStringToNum(string name);

	int GetSoubiPoint(int num, int sort);			//0:num 1:type 2:effect 3:point 4:area 5:flag
	void SetSoubiPoint(int num, int sort, int point);
	string GetSoubiText(int num, int sort);			//0:name 1:explain

	int GetSkillPoint(int num, int sort);			//0:num 1:MP 2:effect 3:status 4:magnification 5:area
	void SetSkillPoint(int num, int sort, int point);
	string GetSkillText(int num, int sort);			//0:name 1:explain
	int SkillStringToNum(string name);

	int GetCharacterStatus(int num, int sort, int value);				//0:HP 1:MP 2:STR 3:VIT 4:AGI 5:INT
	void SetCharacterStatus(int num, int sort, int point, int value);	//0:HP 1:MP 2:STR 3:VIT 4:AGI 5:INT
	int GetCharacterImage(int num);
	int GetCharacterSoubi(int num, int type);
	void SetCharacterSoubi(int num, int type, int soubi);
	bool GetCharacterState(int num, int state);
	void ChangeCharacterState(int num, int state);
	int GetCharacterSkillCode(int num, int order);
	string GetCharacterName(int num);

	characterData GetCharacter(int);

	int GetScenario();
	int GetStage();
	int GetDungeonX();
	int GetDungeonY();
	int GetDir();
	int GetEventFlag();
	int GetRoom();

	void SetScenario(int i);
	void SetStage(int i);
	void SetDungeonX(int i);
	void SetDungeonY(int i);
	void SetDir(int i);
	void SetEventFlag(int i);
	void SetRoom(int i);

	int GetMapFlag(int scenario, int stage, int x, int y);
	int GetEventFlag(int scenario, int num);
	int GetPlayCount();
	int GetWallType(int x, int y);

	void SetMapFlag(int scenario, int stage, int x, int y, int i);
	void SetEventFlag(int scenario, int num, int i);
	void SetPlayCount(int i);
	void AddPlayCount();
	void SetWallType(int x, int y, int type);

	void SceneRequest(int m, int s);
	void SceneBackRequest();

	int GetMode();
	int GetScene(int mode);
};

extern Data_c GData;