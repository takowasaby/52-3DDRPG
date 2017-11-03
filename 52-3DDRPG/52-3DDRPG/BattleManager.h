#pragma once
//前方宣言
class TextBox;

class BattleManager
{
private:
	//キー入力用変数
	int mKey[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている

	characterData player[CHARACTER_SIZE];
	characterData enemy;

	TextBox* PlayerWindow;
	TextBox* OpinionWindow[3];
	TextBox* MessageWindow;

	int phase[3];
	bool isPause;

	int calcOrder[5];

	vector<vector<int>> enemySkill; //0:攻撃、1:バフ、2:回復、3:MP回復
	int enemySkillSize[ENEMY_SKILL_SIZE];

	struct Command {
		int type;					//コマンドの種類(0:攻撃、1:スキル、2:道具、3:防御)
		int agi;
		int whoAmI;

		bool forEnemy;				//対象は敵かそれとも味方か
		int target;					//敵か味方か,何番目か(マイナス値なら敵、4なら全体)

		int num;					//スキルorアイテムのナンバー

		int effectType[2];			//効果の種類

		int effectPoint[2];			//アイテムの効果の固定値

		int cost;					//スキルの消費MP
		int referStatus;			//スキルで参照するステータス
		int magnification;			//スキルの効果倍率
	}; 
	Command partyCommand[CHARACTER_SIZE];
	Command enemyCommand;

public:
	BattleManager();
	~BattleManager();

	void Update();
	void Draw();

	void LoadPlayer(int);
	void LoadEnemy();

	void LoadSkill(int);
	void LoadItem(int);
	void LoadStatus();

	void SetSkill(int,int);
	void SetItem(int,int);
	void SetEnemySkill(int);

	void BattleInitialize();
	void PlayerSelection();
	void EnemySelection();
	void EffectCalc();
	void Judgement();

	void CommandReset(int num);

	void Escape();

	void CalcOrderReset();
	void SetCalcOrder();

	void CompareCalcOrder();

	void KeyUpdata(int[256]);
};

