#pragma once
//前方宣言
class TextBox;

class BattleManager
{
private:
	//キー入力用変数
	int mKey[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている

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

