<<<<<<< HEAD
<<<<<<< HEAD
#include "Define.h"
using namespace std;
=======
#include "define.h"
>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
=======
#include "define.h"
>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d

BattleManager::BattleManager()
	: isPause(false)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
	for (int i = 0; i < 3; i++) phase[i] = 0;
>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
=======
	for (int i = 0; i < 3; i++) phase[i] = 0;
>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
	PlayerWindow = new TextBox();
	for (int i = 0; i < 2; i++) {
		OpinionWindow[i] = new TextBox();
		OpinionWindow[i]->SetWindowMode(pageMode);
	}
	OpinionWindow[0]->SetSize(200, 5);
	OpinionWindow[0]->SetPositon(0, 480 - OpinionWindow[0]->GetHeight());
	OpinionWindow[0]->AddMessage("攻撃");
	OpinionWindow[0]->AddMessage("スキル");
	OpinionWindow[0]->AddMessage("道具");
	OpinionWindow[0]->AddMessage("防御");
	OpinionWindow[0]->AddMessage("情報");
	OpinionWindow[1]->SetSize(640 - OpinionWindow[0]->GetWidth(), 5);
	OpinionWindow[1]->SetPositon(OpinionWindow[0]->GetWidth(), 480 - OpinionWindow[0]->GetHeight());
	
	MessageWindow = new TextBox();
	MessageWindow->SetWindowMode(logMode);
	MessageWindow->SetSize(640, 6);
	MessageWindow->SetPositon(0, 480 - MessageWindow->GetHeight() * 2);

	for (int i = 0; i < CHARACTER_SIZE; i++) {
		LoadPlayer(i);
	}
	LoadEnemy();
}


BattleManager::~BattleManager()
{
}

void BattleManager::Update()
{
	switch (phase[0])
	{
	case 0:
		BattleInitialize();
		break;
	case 1://プレイヤーの行動選択
		PlayerSelection();
		break;
	case 2://敵の行動選択
		EnemySelection();
		break;
	case 3://プレイヤーのダメージ計算
		PlayerCalc();
		break;
	case 4://敵のダメージ計算
		EnemyCalc();
		break;
	default:
		break;
	}
}

void BattleManager::Draw()
{
	//Debug
	clsDx();
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		printfDx("[%d] ", i + 1);
		if (!player[i].flag) printfDx("NONE\n");
		else {
			printfDx("%-8s HP:%4d/%4d MP:%4d/%4d ( %3d %3d %3d %3d )\n"
				, player[i].name.c_str(), player[i].hp.current, player[i].hp.base
				, player[i].mp.current, player[i].mp.base, player[i].str.current
				, player[i].vit.current, player[i].agi.current, player[i].intel.current);
		}
	}
	printfDx("[E] %-8s HP:%4d/%4d MP:%4d/%4d ( %3d %3d %3d %3d )\n"
		, enemy.name.c_str(), enemy.hp.current, enemy.hp.base
		, enemy.mp.current, enemy.mp.base, enemy.str.current
		, enemy.vit.current, enemy.agi.current, enemy.intel.current);
	printfDx("Phase[0] = %d\t", phase[0]);
	printfDx("Phase[1] = %d\t", phase[1]);
	printfDx("Phase[2] = %d\n", phase[2]);

	switch (phase[0])
	{
	case 0:
		break;
	case 1:
		break;
	default:
		break;
	}

	//PlayerWindow->Draw();
<<<<<<< HEAD
<<<<<<< HEAD
	//Debug
	clsDx();
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		printfDx("Player%d : ", i+1);
		if (player[i].flag) printfDx("NONE\n");
		else {
			printfDx("%s %d/%d %d/%d %d/%d %d/%d %d/%d %d/%d\n"
				, player[i].name , player[i].hp.current, player[i].hp.base
				, player[i].mp.current, player[i].mp.base, player[i].str.current
				, player[i].str.base, player[i].vit.current, player[i].vit.base
				, player[i].agi.current, player[i].agi.base
				, player[i].intel.current, player[i].intel.base);
		}
	}
=======
	for (int i = 0; i < 2; i++) OpinionWindow[i]->Draw();
	MessageWindow->Draw();

>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
=======
	for (int i = 0; i < 2; i++) OpinionWindow[i]->Draw();
	MessageWindow->Draw();

>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
}

void BattleManager::LoadPlayer(int index)
{
	//for Debug
<<<<<<< HEAD
<<<<<<< HEAD
	//player[index].name = "PLAYER";
	player[index].flag = true;
	player[index].hp.base = GetRand(1000) + 1000;
	player[index].hp.current = GetRand(1000);
	player[index].mp.base = GetRand(500) + 500;
	player[index].mp.current = GetRand(500);
	player[index].str.base = GetRand(500) + 500;
	player[index].str.current = GetRand(500) + 500;
	player[index].vit.base = GetRand(500) + 500;
	player[index].vit.current = GetRand(500) + 500;
	player[index].agi.base = GetRand(500) + 500;
	player[index].agi.current = GetRand(500) + 500;
	player[index].intel.base = GetRand(500) + 500;
	player[index].intel.current = GetRand(500) + 500;
=======
=======
>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
	player[index].name = "PLAYER" + to_string(index + 1);
	player[index].flag = true;
	player[index].hp.base = GetRand(1000) + 1000;
	player[index].hp.current = GetRand(999);
	player[index].mp.base = GetRand(500) + 499;
	player[index].mp.current = GetRand(500);
	player[index].str.base = GetRand(500) + 499;
	player[index].str.current = GetRand(500);
	player[index].vit.base = GetRand(500) + 499;
	player[index].vit.current = GetRand(500);
	player[index].agi.base = GetRand(500) + 499;
	player[index].agi.current = GetRand(500);
	player[index].intel.base = GetRand(500) + 499;
	player[index].intel.current = GetRand(500);
<<<<<<< HEAD
	for (int i = 0; i < SKILL_CODE_SIZE; i++) player[index].skillCode[i] = (int)GetRand(1);
=======
<<<<<<< HEAD
>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
=======
>>>>>>> 341f3fc2f81a5b7ad244d3f7122d276a83758e3d
>>>>>>> b377ede2ee2be730612747a502aeb8509b198785
}

void BattleManager::LoadEnemy()
{
	//for Debug
	enemy.name = "ENEMY";
	enemy.flag = true;
	enemy.hp.base = GetRand(1000) + 1000;
	enemy.hp.current = GetRand(999);
	enemy.mp.base = GetRand(500) + 499;
	enemy.mp.current = GetRand(500);
	enemy.str.base = GetRand(500) + 499;
	enemy.str.current = GetRand(500);
	enemy.vit.base = GetRand(500) + 499;
	enemy.vit.current = GetRand(500);
	enemy.agi.base = GetRand(500) + 499;
	enemy.agi.current = GetRand(500);
	enemy.intel.base = GetRand(500) + 499;
	enemy.intel.current = GetRand(500);
	for (int i = 0; i < SKILL_CODE_SIZE; i++) enemy.skillCode[i] = (int)GetRand(1);
}

void BattleManager::LoadSkill(int index)
{
	for (int i = 0; i < SKILL_CODE_SIZE; i++) {
		if (player[index].skillCode[i]) {
			//for debug
			OpinionWindow[1]->AddMessage("SkillCode[" + to_string(i) + "]");
		}
	}
}

void BattleManager::BattleInitialize()
{
	if (!isPause) {
		isPause = true;
		MessageWindow->AddMessage("敵が現れた!!!");
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		MessageWindow->ClearMessage();
		phase[0]++;
	}
}

void BattleManager::PlayerSelection()
{
	switch (phase[1])
	{
	case 0:
		MessageWindow->AddMessage(player[phase[2]].name + "はどうする？");
		phase[1]++;
		break;
	case 1:
	case 2:
		if (mKey[KEY_INPUT_W] == 1) OpinionWindow[phase[1]-1]->ScrollUp();
		else if (mKey[KEY_INPUT_A] == 1) OpinionWindow[phase[1]-1]->PageDown();
		else if (mKey[KEY_INPUT_S] == 1) OpinionWindow[phase[1]-1]->ScrollDown();
		else if (mKey[KEY_INPUT_D] == 1) OpinionWindow[phase[1]-1]->PageUp();
		else if (mKey[KEY_INPUT_Z] == 1) {
			MessageWindow->AddMessage(OpinionWindow[phase[1]-1]->Enter() + "を選択");
			if (phase[1] == 1) {
				if (OpinionWindow[0]->Enter() == "攻撃") phase[1]++;
				else if (OpinionWindow[0]->Enter() == "スキル") LoadSkill(phase[2]);
				else if (OpinionWindow[0]->Enter() == "道具");
				else if (OpinionWindow[0]->Enter() == "防御");
				else if (OpinionWindow[0]->Enter() == "情報");
			}
			phase[1]++;
		}
		break;
	case 3:
		MessageWindow->ClearMessage();
		OpinionWindow[1]->ClearMessage();
		phase[2]++;
		phase[1] = 0;
		if (phase[2] >= CHARACTER_SIZE) {
			phase[2] = 0;
			phase[0]++;
		}
		break;
	default:
		break;
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
