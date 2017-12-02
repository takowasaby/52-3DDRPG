#pragma once
//前方宣言
class TextBox;

class BattleManager
{
private:
	//キー入力用変数
	int mKey[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている

	characterData player[CHARACTER_SIZE];
	Command aPlayer[CHARACTER_SIZE + 1];
	characterData enemy;
//	Command aEnemy;

	TextBox* PlayerWindow[CHARACTER_SIZE];
	TextBox* OpinionWindow[OPINIONWINDOW_NUM];
	TextBox* MessageWindow;
	  
	int phase[3];
	bool isPause;
public:
	BattleManager();
	~BattleManager();

	bool Update();
	void Draw();

	void LoadPlayer(int);
	void LoadEnemy();

	void LoadSkill(int);
	void LoadItem();
	void LoadSoubi(int);

	void SetSkill(int,int,int);
	void SetItem(int,int,int);
	void SetTarget(int);

	void BattleInitialize();
	void PlayerSelection();
	void EnemySelection();
	void PlayerCalc();
	void EnemyCalc();
	void ToNextTurn();
	bool BattleEnd(bool);

	void Infomation();

	int TargetNameToNum(string);

	void KeyUpdata(int[256]);

	//for Debug
	int SkillStringToNumForDebug(string);
	int GetSkillPointForDebug(int, int);
};

