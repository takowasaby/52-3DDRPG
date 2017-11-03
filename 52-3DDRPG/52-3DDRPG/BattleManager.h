#pragma once
//�O���錾
class TextBox;

class BattleManager
{
private:
	//�L�[���͗p�ϐ�
	int mKey[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���

	characterData player[CHARACTER_SIZE];
	characterData enemy;

	TextBox* PlayerWindow;
	TextBox* OpinionWindow[3];
	TextBox* MessageWindow;

	int phase[3];
	bool isPause;

	int calcOrder[5];

	vector<vector<int>> enemySkill; //0:�U���A1:�o�t�A2:�񕜁A3:MP��
	int enemySkillSize[ENEMY_SKILL_SIZE];

	struct Command {
		int type;					//�R�}���h�̎��(0:�U���A1:�X�L���A2:����A3:�h��)
		int agi;
		int whoAmI;

		bool forEnemy;				//�Ώۂ͓G������Ƃ�������
		int target;					//�G��������,���Ԗڂ�(�}�C�i�X�l�Ȃ�G�A4�Ȃ�S��)

		int num;					//�X�L��or�A�C�e���̃i���o�[

		int effectType[2];			//���ʂ̎��

		int effectPoint[2];			//�A�C�e���̌��ʂ̌Œ�l

		int cost;					//�X�L���̏���MP
		int referStatus;			//�X�L���ŎQ�Ƃ���X�e�[�^�X
		int magnification;			//�X�L���̌��ʔ{��
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

