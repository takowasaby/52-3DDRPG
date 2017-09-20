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
		int num;				//スキル固有の数字
		char name[64];			//スキルの名前
		int MP;					//スキルの消費MP
		int effect;				//スキルの効果(0:HP回復、1:MP回復、2:STR上昇、3:VIT上昇、4:AGI上昇、5:INT上昇、6:ダメージ)
		int status;				//スキルの効果に依存されるステータス
		double magnification;	//スキル効果のステータス依存の倍率
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