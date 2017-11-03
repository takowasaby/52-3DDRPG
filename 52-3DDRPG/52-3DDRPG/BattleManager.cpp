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

	enemySkill = vector<vector<int>>(ENEMY_SKILL_SIZE, vector<int>(0));
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

	printfDx("%d\n", GData.GetSkillPoint(GData.SkillStringToNum("薙ぎ払い"), 6));

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
	for (int i = 0; i < SKILL_SIZE; i++) enemy.skillCode[i] = (int)GetRand(1);

	for (int i = 0; i < SKILL_SIZE; i++) {
		if (enemy.skillCode[i]) {
			switch (GData.GetSkillPoint(enemy.skillCode[i], 2)) {
			case 0:
				enemySkill[0].push_back(i);
				break;
			case 1:
				enemySkill[2].push_back(i);
				break;
			case 2:
				enemySkill[3].push_back(i);
				break;
			case 3:
				enemySkill[1].push_back(i);
				break;
			case 4:
				enemySkill[1].push_back(i);
				break;
			case 5:
				enemySkill[1].push_back(i);
				break;
			case 6:
				enemySkill[1].push_back(i);
				break;
			case 7:
				break;
			}
		}
	}
	for (int i = 0; i < ENEMY_SKILL_SIZE; i++) {
		enemySkillSize[i] = enemySkill[i].size();
	}

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

	string str;
	for (int i = 0; i < ITEM_SIZE; i++) {
		if (GData.GetItemFlag(i) > 0 && GData.GetItemPoint(i, 1) == 0) {
//			str += to_string(GData.GetItemFlag(i));
//			str += " X ";
			str += GData.GetItemText(i, 0);
			OpinionWindow[1]->AddMessage(str);
			str = "";
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
	partyCommand[pIndex].agi = player[pIndex].agi.calc;
	partyCommand[pIndex].whoAmI = pIndex;
	partyCommand[pIndex].cost = GData.GetSkillPoint(sIndex, 1);
	partyCommand[pIndex].forEnemy = GData.GetSkillPoint(sIndex, 6);
	partyCommand[pIndex].referStatus = GData.GetSkillPoint(sIndex, 3);
	partyCommand[pIndex].magnification = GData.GetSkillPoint(sIndex, 4);
	partyCommand[pIndex].effectType[0] = GData.GetSkillPoint(sIndex, 2);
}
void BattleManager::SetItem(int iIndex, int pIndex)
{
	partyCommand[pIndex].agi = player[pIndex].agi.calc;
	partyCommand[pIndex].whoAmI = pIndex;
	partyCommand[pIndex].forEnemy = GData.GetItemPoint(iIndex, 7);
	partyCommand[pIndex].effectType[0] = GData.GetItemPoint(iIndex, 2);
	partyCommand[pIndex].effectPoint[0] = GData.GetItemPoint(iIndex, 4);
	partyCommand[pIndex].effectType[1] = GData.GetItemPoint(iIndex, 3);
	partyCommand[pIndex].effectPoint[1] = GData.GetItemPoint(iIndex, 5);
}

void BattleManager::SetEnemySkill(int index)
{
	enemyCommand.agi = enemy.agi.calc;
	enemyCommand.whoAmI = -1;
	enemyCommand.cost = GData.GetSkillPoint(index, 1);
	enemyCommand.forEnemy = GData.GetSkillPoint(index, 6);
	enemyCommand.referStatus = GData.GetSkillPoint(index, 3);
	enemyCommand.magnification = GData.GetSkillPoint(index, 4);
	enemyCommand.effectType[0] = GData.GetSkillPoint(index, 2);
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
		if (mKey[KEY_INPUT_UP] == 1) OpinionWindow[phase[1]-1]->ScrollUp();
		else if (mKey[KEY_INPUT_LEFT] == 1) OpinionWindow[phase[1]-1]->PageDown();
		else if (mKey[KEY_INPUT_DOWN] == 1) OpinionWindow[phase[1]-1]->ScrollDown();
		else if (mKey[KEY_INPUT_RIGHT] == 1) OpinionWindow[phase[1]-1]->PageUp();
		else if (mKey[KEY_INPUT_Z] == 1) {
			MessageWindow->AddMessage(OpinionWindow[phase[1]-1]->Enter() + "を選択");
			if (phase[1] == 1) {
				if (OpinionWindow[0]->Enter() == "攻撃") {
					partyCommand[phase[2]].type = 0;
					partyCommand[phase[2]].agi = player[phase[2]].agi.calc;
					partyCommand[phase[2]].whoAmI = phase[2];
					partyCommand[phase[2]].forEnemy = true;
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
					partyCommand[phase[2]].agi = player[phase[2]].agi.calc;
					partyCommand[phase[2]].whoAmI = phase[2];
					partyCommand[phase[2]].forEnemy = false;
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
					if (GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 6)) {
						partyCommand[phase[2]].target = -1;
						phase[1] = 4;
					}
					else if (GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 5)) {
						partyCommand[phase[2]].target = 4;
						phase[1] = 4;
					}
					else {
						LoadStatus();
						phase[1]++;
					}
				}
				else if (OpinionWindow[0]->Enter() == "道具") {
					SetItem(GData.ItemStringToNum(OpinionWindow[1]->Enter()), phase[2]);
					if (GData.GetItemPoint(GData.ItemStringToNum(OpinionWindow[1]->Enter()), 7)) {
						partyCommand[phase[2]].target = -1;
						phase[1] = 4;
					}
					else if (GData.GetItemPoint(GData.ItemStringToNum(OpinionWindow[1]->Enter()), 6)) {
						partyCommand[phase[2]].target = 4;
						phase[1] = 4;
					}
					else {
						LoadStatus();
						phase[1]++;
					}
				}
			}
		}
		break;
	case 3:
		if (mKey[KEY_INPUT_UP] == 1) OpinionWindow[1]->ScrollUp();
		else if (mKey[KEY_INPUT_DOWN] == 1) OpinionWindow[1]->ScrollDown();
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
	if (enemy.hp.base != 0) {
		int rand = GetRand(99);

		if ((double)enemy.hp.calc / enemy.hp.base > 0.8 && enemySkillSize[1] > 0) {
			if (rand < 50) {
				enemyCommand.type = 0;
				enemyCommand.whoAmI = -1;
				enemyCommand.agi = enemy.agi.calc;
				enemyCommand.forEnemy = false;
				enemyCommand.target = GetRand(3);
			}
			else {
				SetEnemySkill(enemySkill[1][GetRand(enemySkillSize[1])]);
			}
		}
		else if ((double)enemy.hp.calc / enemy.hp.base < 0.2 && enemySkillSize[2] > 0) {
			if (rand < 30) {
				enemyCommand.type = 0;
				enemyCommand.whoAmI = -1;
				enemyCommand.agi = enemy.agi.calc;
				enemyCommand.forEnemy = false;
				enemyCommand.target = GetRand(3);
			}
			else if (rand >= 30 && rand < 60) {
				enemyCommand.type = 3;
				enemyCommand.whoAmI = -1;
				enemyCommand.agi = enemy.agi.calc;
				enemyCommand.forEnemy = true;
			}
			else {
				SetEnemySkill(enemySkill[2][GetRand(enemySkillSize[2])]);
			}
		}
		else if ((double)enemy.mp.calc / enemy.mp.base < 0.2 && enemySkillSize[3] > 0) {
			if (rand < 50) {
				enemyCommand.type = 0;
				enemyCommand.whoAmI = -1;
				enemyCommand.agi = enemy.agi.calc;
				enemyCommand.forEnemy = false;
				enemyCommand.target = GetRand(3);
			}
			else {
				SetEnemySkill(enemySkill[3][GetRand(enemySkillSize[3])]);
			}
		}
		else if (enemySkillSize[0] > 0){
			if (rand < 50) {
				enemyCommand.type = 0;
				enemyCommand.whoAmI = -1;
				enemyCommand.agi = enemy.agi.calc;
				enemyCommand.forEnemy = false;
				enemyCommand.target = GetRand(3);
			}
			else {
				SetEnemySkill(enemySkill[0][GetRand(enemySkillSize[0])]);
			}
		}
		else {
			if (rand < 90) {
				enemyCommand.type = 0;
				enemyCommand.whoAmI = -1;
				enemyCommand.agi = enemy.agi.calc;
				enemyCommand.forEnemy = false;
				enemyCommand.target = GetRand(3);
			}
			else {
				enemyCommand.type = 3;
				enemyCommand.whoAmI = -1;
				enemyCommand.agi = enemy.agi.calc;
				enemyCommand.forEnemy = true;
			}
		}
	}
	phase[0]++;
}

void BattleManager::EffectCalc()
{
	
}

void BattleManager::Judgement()
{
}

void BattleManager::CommandReset(int num)
{
	if (num < 0) {
		enemyCommand.type = NULL;
		enemyCommand.agi = NULL;
		enemyCommand.whoAmI = NULL;
		enemyCommand.forEnemy = NULL;
		enemyCommand.magnification = NULL;
		enemyCommand.num = NULL;
		enemyCommand.effectType[0] = NULL;
		enemyCommand.effectPoint[0] = NULL;
		enemyCommand.effectType[1] = NULL;
		enemyCommand.effectPoint[1] = NULL;
		enemyCommand.referStatus = NULL;
		enemyCommand.target = NULL;
	}
	else {
		partyCommand[num].type = NULL;
		partyCommand[num].agi = NULL;
		partyCommand[num].whoAmI = NULL;
		partyCommand[num].forEnemy = NULL;
		partyCommand[num].magnification = NULL;
		partyCommand[num].num = NULL;
		partyCommand[num].effectType[0] = NULL;
		partyCommand[num].effectPoint[0] = NULL;
		partyCommand[num].effectType[1] = NULL;
		partyCommand[num].effectPoint[1] = NULL;
		partyCommand[num].referStatus = NULL;
		partyCommand[num].target = NULL;
	}
}

void BattleManager::Escape()
{
	GData.SceneBackRequest();
}

void BattleManager::CalcOrderReset()
{
	for (int i = -1; i < CHARACTER_SIZE; i++) {
		calcOrder[i + 1] = i;
	}
}
void BattleManager::SetCalcOrder()
{
	int index;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4 - i; j++) {
			if (calcOrder[j] == -1){
				if (enemyCommand.agi < partyCommand[calcOrder[j + 1]].agi) {
					index = calcOrder[j];
					calcOrder[j] = calcOrder[j + 1];
					calcOrder[j + 1] = index;
				}
			}
			else if (calcOrder[j + 1] == -1) {
				if (partyCommand[calcOrder[j]].agi < enemyCommand.agi) {
					index = calcOrder[j];
					calcOrder[j] = calcOrder[j + 1];
					calcOrder[j + 1] = index;
				}
			}
			else {
				if (partyCommand[calcOrder[j]].agi < partyCommand[calcOrder[j + 1]].agi) {
					index = calcOrder[j];
					calcOrder[j] = calcOrder[j + 1];
					calcOrder[j + 1] = index;
				}
			}
		}
	}
}

void BattleManager::KeyUpdata(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}
