#pragma once
//�O���錾
class TextBox;

class BattleManager
{
private:
	//�L�[���͗p�ϐ�
	int mKey[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���

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

