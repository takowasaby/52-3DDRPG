#pragma once
//�O���錾
class TextBox;

class BattleManager
{
private:
	//�L�[���͗p�ϐ�
	int mKey[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
	CommandAgi commandAgi[CHARACTER_SIZE + 1];
	float damageCut[CHARACTER_SIZE + 1];

	characterData player[CHARACTER_SIZE + 12];
	Command aPlayer[CHARACTER_SIZE + 12];
	enemyData enemy;
//	Command aEnemy;

	int enemySkill[4][16];	//�G�X�L���̕���(0:�U���A1:HP�񕜁A2:MP�񕜁A3:�o�t)

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

