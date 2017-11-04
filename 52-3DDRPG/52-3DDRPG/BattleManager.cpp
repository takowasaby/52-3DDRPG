#include "Define.h"

#include "define.h"

BattleManager::BattleManager()
	: isPause(false)
{
	for (int i = 0; i < 3; i++) phase[i] = 0;
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		PlayerWindow[i] = new TextBox();
		PlayerWindow[i]->SetWindowMode(logMode);
		PlayerWindow[i]->SetSize(160, 3);
		PlayerWindow[i]->SetPositon(PlayerWindow[i]->GetWidth() * i, 0);
	}


	for (int i = 0; i < OPINIONWINDOW_NUM; i++) {
		OpinionWindow[i] = new TextBox();
		OpinionWindow[i]->SetWindowMode(pageMode);
	}
	OpinionWindow[0]->SetSize(200, 4);
	OpinionWindow[0]->SetPositon(0, 480 - OpinionWindow[0]->GetHeight() - 20);
	OpinionWindow[0]->AddMessage("攻撃");
	OpinionWindow[0]->AddMessage("スキル");
	OpinionWindow[0]->AddMessage("道具");
	OpinionWindow[0]->AddMessage("防御");
	OpinionWindow[1]->SetSize(300, 4);
	OpinionWindow[1]->SetPositon(OpinionWindow[0]->GetWidth(), 480 - OpinionWindow[0]->GetHeight() - 20);
	OpinionWindow[2]->SetSize(640 - OpinionWindow[0]->GetWidth() - OpinionWindow[1]->GetWidth(), 4);
	OpinionWindow[2]->SetPositon(OpinionWindow[0]->GetWidth() + OpinionWindow[1]->GetWidth(), 480 - OpinionWindow[0]->GetHeight() - 20);
	
	MessageWindow = new TextBox();
	MessageWindow->SetWindowMode(logMode);
	MessageWindow->SetSize(640, 6);
	MessageWindow->SetPositon(0, 480 - MessageWindow->GetHeight() - 100);

	for (int i = 0; i < CHARACTER_SIZE; i++) {
		LoadPlayer(i);
	}
	LoadEnemy();
}

BattleManager::~BattleManager()
{
}

bool BattleManager::Update()
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
	case 5:
		ToNextTurn();
		break;
	case 6://勝利
		return BattleEnd(true);
		break;
	case 7://敗北
		return BattleEnd(false);
		break;
	default:
		break;
	}
	return 0;
}

void BattleManager::Draw()
{
	//Debug
	clsDx();
	/*for (int i = 0; i < CHARACTER_SIZE; i++) {
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
	printfDx("Phase[2] = %d\n", phase[2]);*/

	for (int i = 0; i < CHARACTER_SIZE; i++) {
		PlayerWindow[i]->ClearMessage();
		PlayerWindow[i]->AddMessage(player[i].name);
		PlayerWindow[i]->AddMessage("HP : " + to_string(player[i].hp.calc) + " / " + to_string(player[i].hp.base));
		PlayerWindow[i]->AddMessage("MP : " + to_string(player[i].mp.calc) + " / " + to_string(player[i].mp.base));
		PlayerWindow[i]->Draw();
	}
	for (int i = 0; i < OPINIONWINDOW_NUM; i++) OpinionWindow[i]->Draw();
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

	player[index].state[0] = 0;
	for (int i = 0; i < SKILL_CODE_SIZE; i++) player[index].skillCode[i] = (int)GetRand(1);
	*/
	player[index] = GData.GetCharacterData(index);
}

void BattleManager::LoadEnemy()
{
	//for Debug
	/*
	enemy.name = "ENEMY";
	enemy.flag = true;
	enemy.hp.base = GetRand(5000) + 5000;
	enemy.hp.calc = enemy.hp.base;
	enemy.mp.base = GetRand(500) + 499;
	enemy.mp.calc = enemy.mp.base;
	enemy.str.base = GetRand(500) + 499;
	enemy.str.calc = enemy.str.base;
	enemy.vit.base = GetRand(500) + 499;
	enemy.vit.calc = enemy.vit.base;
	enemy.agi.base = GetRand(500) + 499;
	enemy.agi.calc = enemy.agi.base;
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
		enemySkillSize[i] = (int)enemySkill[i].size();
	}

	enemy.intel.calc = enemy.intel.base;
	for (int i = 0; i < SKILL_CODE_SIZE; i++) enemy.skillCode[i] = (int)GetRand(1);
	*/
	enemy = GData.GetCharacterData(GData.GetStage() + CHARACTER_SIZE);
}

void BattleManager::LoadSkill(int index)
{
	for (int i = 0; i < SKILL_SIZE; i++) {
		if (player[index].skillCode[i]) {
			OpinionWindow[1]->AddMessage(GData.GetSkillText(i, 0));
		}
	}
}

void BattleManager::LoadItem()
{
	for (int i = 0; i < ITEM_TYPE_NUM; i++) {
		if (GData.GetItemPoint(i, 1) == 0 && GData.GetItemPoint(i, 8) != 0) {
			//OpinionWindow[1]->AddMessage(GData.GetItemText(i, 0) + " × " + to_string(GData.GetItemPoint(i, 8)));
			OpinionWindow[1]->AddMessage(GData.GetItemText(i, 0));
		}
	}
}

void BattleManager::LoadSoubi(int)
{
	
}

void BattleManager::SetSkill(int sIndex, int pIndex, int tIndex)
{
	aPlayer[pIndex].name = GData.GetSkillText(sIndex, 0);
	aPlayer[pIndex].cost = GData.GetSkillPoint(sIndex, 1);
	aPlayer[pIndex].target = tIndex;
	switch (GData.GetSkillPoint(sIndex, 3)) {
	case 0:
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].str.calc * (GData.GetSkillPoint(sIndex, 4));
		break;
	case 1:
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].vit.calc * (GData.GetSkillPoint(sIndex, 4));
		break;
	case 2:
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].agi.calc * (GData.GetSkillPoint(sIndex, 4));
		break;
	case 3:
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].intel.calc * (GData.GetSkillPoint(sIndex, 4));
		break;
	}
}

void BattleManager::SetItem(int iIndex, int pIndex, int tIndex)
{
	aPlayer[pIndex].name = GData.GetItemText(iIndex, 0);
	aPlayer[pIndex].cost = 0;
	aPlayer[pIndex].target = tIndex;

	if (GData.GetItemPoint(iIndex, 2) >= 0) aPlayer[pIndex].value[GData.GetItemPoint(iIndex, 2)] = GData.GetItemPoint(iIndex, 4);
	if (GData.GetItemPoint(iIndex, 3) >= 0) aPlayer[pIndex].value[GData.GetItemPoint(iIndex, 3)] = GData.GetItemPoint(iIndex, 5);

	GData.SetItemPoint(iIndex, 8, GData.GetItemPoint(iIndex, 8) - 1);
}

void BattleManager::SetTarget(int forParty)
{
	if (forParty == 1) {
		OpinionWindow[2]->AddMessage(enemy.name);
	}
	else if (forParty == 0) {
		for (int i = 0; i < CHARACTER_SIZE; i++) OpinionWindow[2]->AddMessage(player[i].name);
	}
	else OpinionWindow[2]->AddMessage("全体");
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
		if (player[phase[2]].state[0] == 1) {
			phase[1] = 4;
			break;
		}
		MessageWindow->AddMessage(player[phase[2]].name + "はどうする？");
		OpinionWindow[0]->Activate();
		OpinionWindow[1]->InActivate();
		phase[1]++;
		break;
	case 1:
	case 2:
	case 3:
		//キー入力で操作
		if (mKey[KEY_INPUT_W] == 1) OpinionWindow[phase[1]-1]->ScrollUp();
		else if (mKey[KEY_INPUT_A] == 1) OpinionWindow[phase[1]-1]->PageDown();
		else if (mKey[KEY_INPUT_S] == 1) OpinionWindow[phase[1]-1]->ScrollDown();
		else if (mKey[KEY_INPUT_D] == 1) OpinionWindow[phase[1]-1]->PageUp();
		else if (mKey[KEY_INPUT_Z] == 1) {
			if (phase[1] == 1) {
				if (OpinionWindow[0]->Enter() == "攻撃") {
					aPlayer[phase[2]].commandType = skill;
					aPlayer[phase[2]].name = "攻撃";
					aPlayer[phase[2]].cost = 0;
					aPlayer[phase[2]].forParty = false;
					aPlayer[phase[2]].value[attack] = GetRand(600);
					phase[1]+=2;
				}
				else if (OpinionWindow[0]->Enter() == "スキル") LoadSkill(phase[2]);
				else if (OpinionWindow[0]->Enter() == "道具") LoadItem();
				else if (OpinionWindow[0]->Enter() == "防御") {
					aPlayer[phase[2]].commandType = defence;
					aPlayer[phase[2]].name = "防御";
					aPlayer[phase[2]].cost = 0;
					aPlayer[phase[2]].forParty = false;
					phase[1] += 2;
				}
				OpinionWindow[0]->InActivate();
				OpinionWindow[1]->Activate();
			}
			else if (phase[1] == 2) {
				if (OpinionWindow[0]->Enter() == "スキル") {
					aPlayer[phase[2]].commandType = skill;
					if (GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 6) == 0) aPlayer[phase[2]].forParty = true;
					else aPlayer[phase[2]].forParty = false;
					SetTarget(GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 6));
				}
				else if (OpinionWindow[0]->Enter() == "道具") {
					aPlayer[phase[2]].commandType = item;
					if (GData.GetItemPoint(GData.ItemStringToNum(OpinionWindow[1]->Enter()), 7) == 0) aPlayer[phase[2]].forParty = true;
					else aPlayer[phase[2]].forParty = false;
					SetTarget(GData.GetItemPoint(GData.ItemStringToNum(OpinionWindow[1]->Enter()), 7));
				}
				OpinionWindow[1]->InActivate();
				OpinionWindow[2]->Activate();
			}
			else if (phase[1] == 3) {
				if (OpinionWindow[0]->Enter() == "スキル") {
					SetSkill(GData.SkillStringToNum(OpinionWindow[1]->Enter()), phase[2], TargetNameToNum(OpinionWindow[2]->Enter()));
				}
				else if (OpinionWindow[0]->Enter() == "道具") {
					SetItem(GData.ItemStringToNum(OpinionWindow[1]->Enter()), phase[2], TargetNameToNum(OpinionWindow[2]->Enter()));
				}
			}
			phase[1]++;
		}
		else if (mKey[KEY_INPUT_X] == 1) {
			if (phase[1] == 1 && phase[2] > 0) {
				MessageWindow->ClearMessage();
				OpinionWindow[1]->Reset();
				phase[2]--;
				phase[1] = 0;
			}
			else if (phase[1] > 1) {
				OpinionWindow[phase[1]-1]->Reset();
				OpinionWindow[phase[1] - 2]->Activate();
				OpinionWindow[phase[1] - 1]->InActivate();
				phase[1]--;
			}
		}
		break;
	case 4:
		MessageWindow->ClearMessage();
		OpinionWindow[1]->Reset();
		OpinionWindow[2]->Reset();
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
	aEnemy.name = "BOSS_ATTACK";
	aEnemy.forParty = false;
	aEnemy.target = GetRand(CHARACTER_SIZE-1);
	aEnemy.value[attack] = GetRand(600);
	for (int i = 1; i < 7; i++) if (GetRand(100) > 50) aEnemy.value[i] = GetRand(100);
	phase[0]++;
}

void BattleManager::PlayerCalc()
{
	switch (phase[1]) {
	case 0:
		if (player[phase[2]].state[0] == 1 || aPlayer[phase[2]].name == "") {
			phase[2]++;
			break;
		}
		//メッセージ表示
		if (aPlayer[phase[2]].commandType == item) MessageWindow->AddMessage(player[phase[2]].name + "は" + aPlayer[phase[2]].name + "を使った");
		else if (aPlayer[phase[2]].commandType == defence) MessageWindow->AddMessage(player[phase[2]].name + "は身構えている");
		else MessageWindow->AddMessage(player[phase[2]].name + "の" + aPlayer[phase[2]].name);

		player[phase[2]].mp.calc -= aPlayer[phase[2]].cost;

		if (aPlayer[phase[2]].value[attack] > 0) {
			//攻撃処理
			enemy.hp.calc -= aPlayer[phase[2]].value[attack];
			if (enemy.hp.calc < 0) {
				enemy.hp.calc = 0;
				phase[0] = 6;
			}

			//メッセージ表示
			MessageWindow->AddMessage(enemy.name + "に" + to_string(aPlayer[phase[2]].value[attack]) + "のダメージ！！");
		}
		if (aPlayer[phase[2]].value[healHp] > 0) {
			if (player[aPlayer[phase[2]].target].state[0] == 1) {
				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は死んでいる…");
			}
			else {
				//HP回復処理
				player[aPlayer[phase[2]].target].hp.calc += aPlayer[phase[2]].value[healHp];
				if (player[aPlayer[phase[2]].target].hp.calc > player[aPlayer[phase[2]].target].hp.base) player[aPlayer[phase[2]].target].hp.calc = player[aPlayer[phase[2]].target].hp.base;

				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は" + to_string(aPlayer[phase[2]].value[healHp]) + "のHP回復！！");
			}
		}
		if (aPlayer[phase[2]].value[healMp] > 0) {
			if (player[aPlayer[phase[2]].target].state[0] == 1) {
				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は死んでいる…");
			}
			else {
				//MP回復処理
				player[aPlayer[phase[2]].target].mp.calc += aPlayer[phase[2]].value[healMp];
				if (player[aPlayer[phase[2]].target].mp.calc > player[aPlayer[phase[2]].target].mp.base) player[aPlayer[phase[2]].target].mp.calc = player[aPlayer[phase[2]].target].mp.base;

				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は" + to_string(aPlayer[phase[2]].value[healMp]) + "のMP回復！！");
			}
		}
		if (aPlayer[phase[2]].value[buffStr] > 0) {
			if (player[aPlayer[phase[2]].target].state[0] == 1) {
				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は死んでいる…");
			}
			else {
				//バフ処理
				player[aPlayer[phase[2]].target].str.calc *= (double)aPlayer[phase[2]].value[buffStr] / 100 + 1;

				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "の攻撃力が上昇！");
			}
		}
		if (aPlayer[phase[2]].value[buffVit] > 0) {
			if (player[aPlayer[phase[2]].target].state[0] == 1) {
				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は死んでいる…");
			}
			else {
				//バフ処理
				player[aPlayer[phase[2]].target].vit.calc *= (double)aPlayer[phase[2]].value[buffVit] / 100 + 1;

				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "の生命力が上昇！");
			}
		}
		if (aPlayer[phase[2]].value[buffAgi] > 0) {
			if (player[aPlayer[phase[2]].target].state[0] == 1) {
				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は死んでいる…");
			}
			else {
				//バフ処理
				player[aPlayer[phase[2]].target].agi.calc *= (double)aPlayer[phase[2]].value[buffAgi] / 100 + 1;

				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "の素早さが上昇！");
			}
		}
		if (aPlayer[phase[2]].value[buffInt] > 0) {
			if (player[aPlayer[phase[2]].target].state[0] == 1) {
				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は死んでいる…");
			}
			else {
				//バフ処理
				player[aPlayer[phase[2]].target].intel.calc *= (double)aPlayer[phase[2]].value[buffInt] / 100 + 1;

				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "の賢さが上昇！");
			}
		}
		if (aPlayer[phase[2]].value[reviv] > 0) {
			//蘇生処理
			if (player[aPlayer[phase[2]].target].state[0] == 1) {
				if (GetRand(100) <= aPlayer[phase[2]].value[reviv]) {
					player[aPlayer[phase[2]].target].hp.calc += player[aPlayer[phase[2]].target].hp.base / 2;
					player[aPlayer[phase[2]].target].state[0] = 0;

					//メッセージ表示
					MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は息を吹き返した！");
				}
				else {
					//メッセージ表示
					MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は息を吹き返さなかった…");
				}
			}
			else {
				//メッセージ表示
				MessageWindow->AddMessage(player[aPlayer[phase[2]].target].name + "は生きている");
			}
		}
		phase[1]++;
		break;
	case 1:
		if (!isPause) {
			isPause = true;
		}
		else if (mKey[KEY_INPUT_Z] == 1) {
			MessageWindow->ClearMessage();
			isPause = false;
			phase[2]++;
			phase[1] = 0;
			if (phase[2] >= CHARACTER_SIZE) {
				phase[2] = 0;
				phase[0]++;
			}
		}
	}
}

void BattleManager::EnemyCalc()
{
	if (!isPause) {
		isPause = true;
		//メッセージ表示
		MessageWindow->AddMessage(enemy.name + "の" + aEnemy.name);

		if (aEnemy.value[attack] > 0) {
			//攻撃処理
			if (aPlayer[aEnemy.target].commandType == defence) player[aEnemy.target].hp.calc -= aEnemy.value[attack] / 2;
			else player[aEnemy.target].hp.calc -= aEnemy.value[attack];

			if (player[aEnemy.target].hp.calc <= 0) {
				player[aEnemy.target].hp.calc = 0;
				player[aEnemy.target].state[0] = 1;
			}
			if (player[0].state[0] == 1 && player[1].state[0] == 1 && player[2].state[0] == 1 && player[3].state[0] == 1) {
				phase[0] = 7;
				return;
			}

			//メッセージ表示
			MessageWindow->AddMessage(player[aEnemy.target].name + "に" + to_string(aEnemy.value[attack]) + "のダメージ！！");
		}
		if (aEnemy.value[healHp] > 0) {
			//HP回復処理
			enemy.hp.calc += aEnemy.value[healHp];
			if (enemy.hp.calc > enemy.hp.base) enemy.hp.calc = enemy.hp.base;

			//メッセージ表示
			MessageWindow->AddMessage(enemy.name + "は" + to_string(aEnemy.value[healHp]) + "のHP回復！！");
		}
		if (aEnemy.value[healMp] > 0) {
			//MP回復処理
			enemy.mp.calc += aEnemy.value[healMp];
			if (enemy.mp.calc >enemy.mp.base) enemy.mp.calc = enemy.mp.base;

			//メッセージ表示
			MessageWindow->AddMessage(enemy.name + "は" + to_string(aEnemy.value[healMp]) + "のMP回復！！");
		}
		if (aEnemy.value[buffStr] > 0) {
			//バフ処理
			enemy.str.calc *= (double)aEnemy.value[buffStr] / 100 + 1;

			//メッセージ表示
			MessageWindow->AddMessage(enemy.name + "の攻撃力が上昇！");
		}
		if (aEnemy.value[buffVit] > 0) {
			//バフ処理
			enemy.vit.calc *= (double)aEnemy.value[buffVit] / 100 + 1;

			//メッセージ表示
			MessageWindow->AddMessage(enemy.name + "の生命力が上昇！");
		}
		if (aEnemy.value[buffAgi] > 0) {
			//バフ処理
			enemy.agi.calc *= (double)aEnemy.value[buffAgi] / 100 + 1;

			//メッセージ表示
			MessageWindow->AddMessage(enemy.name + "の素早さが上昇！");
		}
		if (aEnemy.value[buffInt] > 0) {
			//バフ処理
			enemy.intel.calc *= (double)aEnemy.value[buffInt] / 100 + 1;

			//メッセージ表示
			MessageWindow->AddMessage(enemy.name + "の賢さが上昇！");
		}
		//if (aEnemy.value[reviv] > 0) {
		//	//蘇生処理
		//	if (enemy.state[0]) {
		//		if (GetRand(100) <= aEnemy.value[reviv]) {
		//			enemy.hp.calc += enemy.hp.base / 2;

		//			//メッセージ表示
		//			MessageWindow->AddMessage(enemy.name + "は息を吹き返した！");
		//		}
		//		else {
		//			//メッセージ表示
		//			MessageWindow->AddMessage(enemy.name + "は息を吹き返さなかった…");
		//		}
		//	}
		//	else {
		//		//メッセージ表示
		//		MessageWindow->AddMessage(enemy.name + "は生きている");
		//	}
		//}
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		MessageWindow->ClearMessage();
		isPause = false;
		phase[0]++;
	}
}

void BattleManager::ToNextTurn()
{
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		aPlayer[i].cost = 0;
		aPlayer[i].forParty = false;
		aPlayer[i].name = "";
		aPlayer[i].target = 0;
		for (int j = 0; j < 8; j++) aPlayer[i].value[j] = 0;
	}
	aEnemy.cost = 0;
	aEnemy.forParty = false;
	aEnemy.name = "";
	aEnemy.target = 0;
	for (int j = 0; j < 8; j++) aEnemy.value[j] = 0;

	phase[0] = 1;
}

bool BattleManager::BattleEnd(bool isWin)
{
	if (isWin) {
		//勝利処理
		if (!isPause) {
			isPause = true;
			MessageWindow->ClearMessage();
			MessageWindow->AddMessage(enemy.name + "を倒した！！！");
		}
		else if (mKey[KEY_INPUT_Z] == 1) {
			return 1;
			for (int i = 0; i < CHARACTER_SIZE; i++) GData.SetCharacterData(i, player[i]);
			GData.SceneBackRequest();
		}
	}
	else {
		//敗北処理
		if (!isPause) {
			isPause = true;
			MessageWindow->ClearMessage();
			MessageWindow->AddMessage("パーティーは全滅した…");
		}
		else if (mKey[KEY_INPUT_Z] == 1) {
			return 1;
			GData.SceneRequest(1, 2);
		}
	}
	return 0;
}

void BattleManager::Infomation()
{
	
}

int BattleManager::TargetNameToNum(string tName)
{
	if (tName == enemy.name) return 0;
	else {
		for (int i = 0; i < CHARACTER_SIZE; i++) if (tName == player[i].name) return i;
	}
}

void BattleManager::KeyUpdata(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}

int BattleManager::SkillStringToNumForDebug(string skillName) {
	for (int i = 0; i < SKILL_CODE_SIZE; i++) {
		if (skillName == "SkillCode[" + to_string(i) + "]") return i;
	}
	return -1;
}

int BattleManager::GetSkillPointForDebug(int num, int sort)
{
	switch (sort) {
	case 6:
		if (num == 0) return 1;
		else return 0;
	default:
		return -1;
	}
}
