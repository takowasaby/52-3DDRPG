#pragma once
//前方宣言
class TextBox;

class BattleManager
{
private:
	//キー入力用変数
	int mKey[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている
	CommandAgi commandAgi[CHARACTER_SIZE + 1];
	float damageCut[CHARACTER_SIZE + 1];

	characterData player[CHARACTER_SIZE + 12];
	Command aPlayer[CHARACTER_SIZE + 12];
	enemyData enemy;
//	Command aEnemy;

	int enemySkill[4][16];	//敵スキルの分類(0:攻撃、1:HP回復、2:MP回復、3:バフ)

	TextBox* PlayerWindow[CHARACTER_SIZE];
	TextBox* OpinionWindow[OPINIONWINDOW_NUM];
	TextBox* MessageWindow;
	  
	int phase[3];
	bool isPause;

	int battleBgm;
public:
	BattleManager();
	~BattleManager();

	bool Update();
	void Draw();

	int SkillMeasure(int);

	void LoadPlayer(int);
	void LoadEnemy();

	void LoadSkill(int);
	void LoadItem();
	void LoadSoubi(int);

	void SetSkill(int,int,int);
	void SetEnemySkill(int,int);
	void SetItem(int,int,int);
	void SetTarget(int);

	void BattleInitialize();
	void PlayerSelection();
	void EnemySelection();
	void CalcManager();
	void CommandAgiSort(int);
	bool PlayerCalc(int);
	bool EnemyCalc();
	void ToNextTurn();
	bool BattleEnd(bool);

	void Infomation();

	int TargetNameToNum(string);

	void KeyUpdata(int[256]);

	//for Debug
	int SkillStringToNumForDebug(string);
	int GetSkillPointForDebug(int, int);
};

