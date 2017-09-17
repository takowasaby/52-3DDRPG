#pragma once

const int SCENARIO_SIZE = 5;
const int STAGE_SIZE = 5;
const int ITEM_TYPE_SIZE = 3;
const int ITEM_SIZE = 32;
const int NAME_SIZE = 32;
const int SKILL_CODE_SIZE = 16;

class Data_c {
private:
	int scenario;
	int dungeonX, dungeonY;
	int mapFlag[SCENARIO_SIZE][STAGE_SIZE][MAP_SIZE_X][MAP_SIZE_Y];
	int eventFlag[SCENARIO_SIZE][64];
	int playCount;
//	int itemFlag[SCENARIO_SIZE][ITEM_TYPE_SIZE][ITEM_SIZE];

	struct Skill_t {
	};

	struct Item_t {
		int flag;
	};
	
	struct Character_t {
		const int HPMAX, MPMAX, STR, VIT, AGI, INT;
		int HP, MP;
		char name[NAME_SIZE];
		int skillCode[SKILL_CODE_SIZE];
		int Image;
	};

public:
	Data_c();		//コンストラクタ
	~Data_c();		//デストラクタ

	int GetScenario();
	int GetDungeonX();
	int GetDungeonY();

	void SetScenario(int i);
	void SetDungeonX(int i);
	void SetDungeonY(int i);
};