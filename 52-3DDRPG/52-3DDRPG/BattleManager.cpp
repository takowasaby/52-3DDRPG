#include "Define.h"

#include "define.h"

BattleManager::BattleManager()
	: isPause(false)
{
	for (int i = 0; i < 3; i++) phase[i] = 0;
	PlayerWindow = new TextBox();
	for (int i = 0; i < 3; i++) {
		OpinionWindow[i] = new TextBox();
		OpinionWindow[i]->SetWindowMode(pageMode);
	}
	OpinionWindow[0]->SetSize(200, 4);
	OpinionWindow[0]->SetPositon(72, 480 - OpinionWindow[0]->GetHeight());
	OpinionWindow[0]->AddMessage("攻撃");
	OpinionWindow[0]->AddMessage("スキル");
	OpinionWindow[0]->AddMessage("道具");
	OpinionWindow[0]->AddMessage("防御");
//	OpinionWindow[0]->AddMessage("逃亡");
	OpinionWindow[1]->SetSize(360, 4);
	OpinionWindow[1]->SetPositon(240, 480 - OpinionWindow[0]->GetHeight());
	
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
	case 3://ダメージ計算＆効果反映
		EffectCalc();
		break;
	case 4://バトル終了処理を行うかの判定
		Judgement();
		break;
	default:
		break;
	}
}

void BattleManager::Draw()
{
	OpinionWindow[0]->DrawWindow(0, 400, 200, 80);
	OpinionWindow[0]->DrawWindow(200, 400, 440, 80);
	//Debug
	clsDx();
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		printfDx("[%d] ", i + 1);
		if (!player[i].flag) printfDx("NONE\n");
		else {
			printfDx("%-8s HP:%4d/%4d MP:%4d/%4d ( %3d %3d %3d %3d )\n"
				, player[i].name.c_str(), player[i].hp.calc, player[i].hp.base
				, player[i].mp.calc, player[i].mp.base, player[i].str.calc
				, player[i].vit.calc, player[i].agi.calc, player[i].intel.calc);
		}
	}
	printfDx("[E] %-8s HP:%4d/%4d MP:%4d/%4d ( %3d %3d %3d %3d )\n"
		, enemy.name.c_str(), enemy.hp.calc, enemy.hp.base
		, enemy.mp.calc, enemy.mp.base, enemy.str.calc
		, enemy.vit.calc, enemy.agi.calc, enemy.intel.calc);
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

	for (int i = 0; i < 2; i++) OpinionWindow[i]->Draw();
	MessageWindow->Draw();
}

void BattleManager::LoadPlayer(int index)
{
	//for Debug
	/*
	player[index].name = "PLAYER" + to_string(index + 1);
	player[index].flag = true;
	player[index].hp.base = GetRand(1000) + 1000;
	player[index].hp.calc = GetRand(999);
	player[index].mp.base = GetRand(500) + 499;
	player[index].mp.calc = GetRand(500);
	player[index].str.base = GetRand(500) + 499;
	player[index].str.calc = GetRand(500);
	player[index].vit.base = GetRand(500) + 499;
	player[index].vit.calc = GetRand(500);
	player[index].agi.base = GetRand(500) + 499;
	player[index].agi.calc = GetRand(500);
	player[index].intel.base = GetRand(500) + 499;
	player[index].intel.calc = GetRand(500);
	*/

	player[index] = GData.GetCharacterData(index);

	//for (int i = 0; i < SKILL_CODE_SIZE; i++) player[index].skillCode[i] = (int)GetRand(1);
}

void BattleManager::LoadEnemy()
{
	//for Debug
	enemy.name = "ENEMY";
	enemy.flag = true;
	enemy.hp.base = GetRand(1000) + 1000;
	enemy.hp.calc = GetRand(999);
	enemy.mp.base = GetRand(500) + 499;
	enemy.mp.calc = GetRand(500);
	enemy.str.base = GetRand(500) + 499;
	enemy.str.calc = GetRand(500);
	enemy.vit.base = GetRand(500) + 499;
	enemy.vit.calc = GetRand(500);
	enemy.agi.base = GetRand(500) + 499;
	enemy.agi.calc = GetRand(500);
	enemy.intel.base = GetRand(500) + 499;
	enemy.intel.calc = GetRand(500);
	for (int i = 0; i < SKILL_CODE_SIZE; i++) enemy.skillCode[i] = (int)GetRand(1);
}

void BattleManager::LoadSkill(int index)
{
	OpinionWindow[1]->ClearMessage();

	for (int i = 0; i < SKILL_SIZE; i++) {
		if (player[index].skillCode[i]) {
			//for debug
			OpinionWindow[1]->AddMessage(GData.GetSkillText(i, 0));
		}
	}
}

void BattleManager::LoadItem(int index)
{
	OpinionWindow[1]->ClearMessage();

	for (int i = 0; i < SKILL_CODE_SIZE; i++) {
		if (player[index].skillCode[i]) {
			//for debug
			OpinionWindow[1]->AddMessage("SkillCode[" + to_string(i) + "]");
		}
	}
}

void BattleManager::LoadStatus()
{
	OpinionWindow[1]->ClearMessage();

	string str;
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		str += player[i].name;
		str += " HP:";
		str += to_string(player[i].hp.calc);
		str += "/";
		str += to_string(player[i].hp.base);
		str += " MP:";
		str += to_string(player[i].mp.calc);
		str += "/";
		str += to_string(player[i].mp.base);
		OpinionWindow[1]->AddMessage(str);
		str = "";
	}
}

void BattleManager::SetSkill(int sIndex, int pIndex)
{
	//for debug
	partyCommand[pIndex].cost = GetRand(100);
	partyCommand[pIndex].target = 0;
	for (int i = 0; i < EFFECT_SIZE; i++) if (GetRand(1) == 0) partyCommand[pIndex].value[i] = GetRand(99) + 1;
}
void BattleManager::SetItem(int sIndex, int pIndex)
{
	partyCommand[pIndex].cost = GetRand(100);
	partyCommand[pIndex].target = 0;
	for (int i = 0; i < EFFECT_SIZE; i++) if (GetRand(1) == 0) partyCommand[pIndex].value[i] = GetRand(99) + 1;
}

void BattleManager::BattleInitialize()
{
	if (!isPause) {
		isPause = true;
		MessageWindow->AddMessage("敵が現れた!!!");
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		MessageWindow->ClearMessage();
		isPause = false;
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
				if (OpinionWindow[0]->Enter() == "攻撃") {
					partyCommand[phase[2]].type = 0;
					partyCommand[phase[2]].forParty = false;
					partyCommand[phase[2]].target = -1;
					phase[1] = 4;
				}
				else if (OpinionWindow[0]->Enter() == "スキル") {
					LoadSkill(phase[2]);
					phase[1]++;
				}
				else if (OpinionWindow[0]->Enter() == "道具") {
					LoadItem(phase[2]);
					phase[1]++;
				}
				else if (OpinionWindow[0]->Enter() == "防御") {
					partyCommand[phase[2]].type = 3;
					partyCommand[phase[2]].forParty = true;
					partyCommand[phase[2]].target = phase[2];
					phase[1] = 4;
				}
				else if (OpinionWindow[0]->Enter() == "逃亡") {
					Escape();
				}
			}
			else if (phase[1] == 2) {
				if (OpinionWindow[0]->Enter() == "スキル") {
					SetSkill(GData.SkillStringToNum(OpinionWindow[1]->Enter()), phase[2]);
					LoadStatus();
					if (GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 6)) {
						partyCommand[phase[2]].target = -1;
						phase[1] = 4;
					}
					else if (GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 5)) {
						partyCommand[phase[2]].target = 4;
						phase[1] = 4;
					}
					else phase[1]++;
				}
				else if (OpinionWindow[0]->Enter() == "道具") {

				}
			}
		}
		break;
	case 3:
		if (mKey[KEY_INPUT_W] == 1) OpinionWindow[1]->ScrollUp();
		else if (mKey[KEY_INPUT_S] == 1) OpinionWindow[1]->ScrollDown();
		else if (mKey[KEY_INPUT_Z] == 1) {
			partyCommand[phase[2]].target = (OpinionWindow[0]->EnterInt());
			phase[1] = 4;
		}
		break;
	case 4:
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
	//for debug
	int r = GetRand(100);
	if (r < 50) {
		MessageWindow->AddMessage("ENEMYは攻撃を選択");
	}
	else {
		MessageWindow->AddMessage("ENEMYはスキルを選択");
	}
	enemyCommand.forParty = false;
	enemyCommand.value[attack] = GetRand(600);
	phase[0]++;
}

void BattleManager::EffectCalc()
{
	switch (phase[1])
	{
	case 0:
		
		phase[1]++;
		break;
	case 1:
	case 2:
		phase[1]++;
		break;
	case 3:
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

void BattleManager::Judgement()
{
}

void BattleManager::CommandReset(int num)
{
	if (num < 0) {
		enemyCommand.type = NULL;
		enemyCommand.forParty = NULL;
		enemyCommand.magnification = NULL;
		enemyCommand.num = NULL;
		enemyCommand.referStatus = NULL;
		enemyCommand.target = NULL;
		for (int i = 0; i < EFFECT_SIZE; i++) {
			enemyCommand.value[i] = NULL;
		}
	}
	else {
		partyCommand[num].type = NULL;
		partyCommand[num].forParty = NULL;
		partyCommand[num].magnification = NULL;
		partyCommand[num].num = NULL;
		partyCommand[num].referStatus = NULL;
		partyCommand[num].target = NULL;
		for (int i = 0; i < EFFECT_SIZE; i++) {
			partyCommand[num].value[i] = NULL;
		}
	}
}

void BattleManager::Escape()
{
	GData.SceneBackRequest();
}

void BattleManager::KeyUpdata(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}
