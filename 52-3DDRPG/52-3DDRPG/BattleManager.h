#pragma once
//�O���錾
class TextBox;

class BattleManager
{
private:
	//�L�[���͗p�ϐ�
	int mKey[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���

	characterData player[CHARACTER_SIZE];
	Attack aPlayer[CHARACTER_SIZE];
	characterData enemy;
	Attack aEnemy;

	TextBox* PlayerWindow;
	TextBox* OpinionWindow[2];
	TextBox* MessageWindow;

	int phase[3];
	bool isPause;
public:
	BattleManager();
	~BattleManager();

	void Update();
	void Draw();

	void LoadPlayer(int);
	void LoadEnemy();

	void LoadSkill(int);

	void SetSkill(int,int);

	void BattleInitialize();
	void PlayerSelection();
	void EnemySelection();
	void PlayerCalc();
	void EnemyCalc();

	void Escape();


	void KeyUpdata(int[256]);
};

