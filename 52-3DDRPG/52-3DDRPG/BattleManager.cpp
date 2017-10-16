#include "Define.h"

BattleManager::BattleManager()
	: phase(0)
{
	GData.CharacterLoad(0);
	PlayerWindow = new TextBox();
	for (int i = 0; i < 2; i++) OpinionWindow[i] = new TextBox();
	
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		player[i] = GData.GetCharacter(i);
	}
}


BattleManager::~BattleManager()
{
}

void BattleManager::Update()
{
	switch (phase)
	{
	case 0:
		break;
	case 1://�v���C���[�̍s���I��
		PlayerSelection();
		break;
	case 2://�G�̍s���I��
		EnemySelection();
		break;
	case 3://�v���C���[�̃_���[�W�v�Z
		PlayerCalc();
		break;
	case 4://�G�̃_���[�W�v�Z
		EnemyCalc();
		break;
	default:
		break;
	}
}

void BattleManager::Draw()
{
	switch (phase)
	{
	case 0:
		break;
	case 1:
		break;
	default:
		break;
	}

	//PlayerWindow->Draw();
	//Debug
	clsDx();
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		printfDx("Player%d : ", i+1);
		if (player[i].flag) printfDx("NONE\n");
		else {
			printfDx("%s %d/%d %d/%d %d %d %d %d\n"
				,player[i].name, player[i].HP, player[i].HPMAX
				, player[i].MP, player[i].MPMAX, player[i].STR
				, player[i].VIT, player[i].AGI, player[i].INT);
		}
	}
}

void BattleManager::LoadPlayer(int index)
{
	
}

void BattleManager::PlayerSelection()
{
	if (mKey[KEY_INPUT_W] == 1) {
	}
	else if (mKey[KEY_INPUT_A] == 1) {
	}
	else if (mKey[KEY_INPUT_S] == 1) {
	}
	else if (mKey[KEY_INPUT_D] == 1) {
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
	}
}

void BattleManager::EnemySelection()
{
}

void BattleManager::PlayerCalc()
{
}

void BattleManager::EnemyCalc()
{
}

void BattleManager::KeyUpdata(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}
