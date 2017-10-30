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
		int num;				//スキルのナンバリング
		string name;			//スキルの名前
		int MP;					//スキルの消費MP
		int effect;				//スキルの効果(0:HP回復、1:MP回復、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇、6:ダメージ)
		int status;				//スキルの効果に依存されるステータス
		double magnification;	//スキル効果のステータス依存の倍率*1000
		int area;				//スキル効果の範囲(0:単体、1:全体)
		char explain[512];		//スキルの説明文
	};
	Skill_t skill[SKILL_SIZE];

	struct Item_t {
		int flag;				//アイテムのナンバリング
		int num;				//アイテム固有の数字
		char name[64];			//アイテムの名前
		int type;				//アイテムの種類(0:消耗品、1:だいじなもの)
		int effect1, effect2;	//アイテムの効果(0:HP回復、1:MP回復、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇、6:ダメージ)
		int point1, point2;		//アイテム効果の固定値
		int area;				//アイテム効果の範囲(0:単体、1:全体)
		char explain[512];		//アイテムの説明文
	};
	Item_t item[ITEM_SIZE];

	struct Soubi_t {
		int flag;				//装備を所持している個数
		int num;				//装備のナンバリング
		char name[64];			//装備の名前
		int type;				//装備の種類(0:武器、1:アクセサリー)
		int effect;				//装備の効果(0:HP上昇、1:MP上昇、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇)
		int point;				//装備効果の固定値
		int area;				//武器の攻撃範囲(0:単体、1:全体)
		char explain[512];		//装備の説明文
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
	Data_c();		//コンストラクタ
					//	Data_c(int* mode, int* event_scene, int* title_scene, int* game_scene);
	~Data_c();		//デストラクタ

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