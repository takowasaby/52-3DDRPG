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
		int num;				//スキル固有の数字
		char name[64];			//スキルの名前
		int MP;					//スキルの消費MP
		int effect;				//スキルの効果(0:HP回復、1:MP回復、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇、6:ダメージ)
		int status;				//スキルの効果に依存されるステータス
		double magnification;	//スキル効果のステータス依存の倍率*1000
		int area;				//スキル効果の範囲(0:単体、1:全体)
		char explain[64];		//スキルの説明文
	};
	Skill_t skill[SKILL_SIZE];

	struct Item_t {
		int flag;				//アイテムを所持している個数
		int num;				//アイテム固有の数字
		char name[64];			//アイテムの名前
		int type;				//アイテムの種類(0:消耗品、1:だいじなもの)
		int effect1, effect2;	//アイテムの効果(0:HP回復、1:MP回復、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇、6:ダメージ)
		int point1, point2;		//アイテム効果の固定値
		int area;				//アイテム効果の範囲(0:単体、1:全体)
		char explain[64];		//アイテムの説明文
	};
	Item_t item[ITEM_SIZE];

	struct Soubi_t {
		int flag;				//装備を所持している個数
		int num;				//装備固有の数字
		char name[64];			//装備の名前
		int type;				//装備の種類(0:武器、1:アクセサリー)
		int effect;				//装備の効果(0:HP上昇、1:MP上昇、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇)
		int point;				//装備効果の固定値
		int area;				//武器の攻撃範囲(0:単体、1:全体)
		char explain[64];		//装備の説明文
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
	Data_c();		//コンストラクタ
	~Data_c();		//デストラクタ

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