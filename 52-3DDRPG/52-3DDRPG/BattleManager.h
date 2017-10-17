#pragma once
//前方宣言
class TextBox;

class BattleManager
{
private:
	//キー入力用変数
	int mKey[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている

	CharacterData player[CHARACTER_SIZE];

	TextBox* PlayerWindow;
	TextBox* OpinionWindow[2];

	int phase;
public:
	BattleManager();
	~BattleManager();

	void Update();
	void Draw();

	void LoadPlayer(int);

	void BattleInitialize();
	void PlayerSelection();
	void EnemySelection();
	void PlayerCalc();
	void EnemyCalc();


	void KeyUpdata(int[256]);
};

