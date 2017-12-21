#include "Define.h"

#include "define.h"

BattleManager::BattleManager()
	: isPause(false)
{
	for (int i = 0; i < CHARACTER_SIZE + 1; i++) {
		aPlayer[i].cost = 0;
		aPlayer[i].forParty = 0;
		aPlayer[i].name = "";
		aPlayer[i].target - 0;
		for(int j = 0; j < EFFECT_SIZE; j++) aPlayer[i].value[j] = 0;
	}

	for (int i = 0; i < CHARACTER_SIZE + 1; i++) {
		damageCut[i] = 1.0;
	}

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 4; j++) {
			enemySkill[j][i] = -1;
		}
	}

	for (int i = 0; i < 256; i++) {
		mKey[i] = 0;
	}

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
	OpinionWindow[0]->AddMessage("�U��");
	OpinionWindow[0]->AddMessage("�X�L��");
	OpinionWindow[0]->AddMessage("����");
	OpinionWindow[0]->AddMessage("�h��");
	OpinionWindow[1]->SetSize(304, 4);
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

	for (int i = 0; i < CHARACTER_SIZE + 1; i++) {
		commandAgi[i].who = i;
		commandAgi[i].agi = 0;
	}
	CommandAgiSort(0);

	GMusic.StopSound(GData.GetDungeonBgm());

	string str;
	str += "resource/sounds/BGM/scenario";
	str += to_string(GData.GetScenario());
	str += "/battle.wav";
	battleBgm = LoadSoundMem(str.c_str());
	ChangeVolumeSoundMem(64, battleBgm);

	GMusic.ReserveSound(battleBgm, DX_PLAYTYPE_LOOP);
}

BattleManager::~BattleManager()
{
}

bool BattleManager::Update()
{
	/*
	switch (phase[0])
	{
	case 0:
		BattleInitialize();
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
	case 5:
		ToNextTurn();
		break;
	case 6://����
		return BattleEnd(true);
		break;
	case 7://�s�k
		return BattleEnd(false);
		break;
	default:
		break;
	}
	return 0;
	*/
	switch (phase[0])
	{
	case 0:
		BattleInitialize();
		break;
	case 1://�v���C���[�̍s���I��
		PlayerSelection();
		break;
	case 2://�G�̍s���I��
		EnemySelection();
		break;
	case 3://�_���[�W�v�Z
		CalcManager();
		break;
	case 4:
		ToNextTurn();
		break;
	case 5://����
		return BattleEnd(true);
		break;
	case 6://�s�k
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
	//clsDx();
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
	*/
	//printfDx("[E] %-8s HP:%4d/%4d MP:%4d/%4d ( %3d %3d %3d %3d )\n"
	//	, enemy.name.c_str(), enemy.hp.calc, enemy.hp.base
	//	, enemy.mp.calc, enemy.mp.base, enemy.str.calc
	//	, enemy.vit.calc, enemy.agi.calc, enemy.intel.calc);
	/*
	printfDx("[E] %-8s HP:%4d/%4d MP:%4d/%4d ( %3d %3d %3d %3d )\n"
		, GData.enemy[1].name.c_str(), GData.enemy[1].hp.calc, GData.enemy[1].hp.base
		, GData.enemy[1].mp.calc, GData.enemy[1].mp.base, GData.enemy[1].str.calc
		, GData.enemy[1].vit.calc, GData.enemy[1].agi.calc, GData.enemy[1].intel.calc);
	/*
	printfDx("Phase[0] = %d\t", phase[0]);
	printfDx("Phase[1] = %d\t", phase[1]);
	printfDx("Phase[2] = %d\n", phase[2]);*/
	DrawExtendGraph(240, 60, 401, 301, enemy.image, TRUE);

	for (int i = 0; i < CHARACTER_SIZE; i++) {
		if (player[i].flag == 1) {
			PlayerWindow[i]->ClearMessage();
			PlayerWindow[i]->AddMessage(player[i].name);
			PlayerWindow[i]->AddMessage("HP : " + to_string(player[i].hp.calc) + " / " + to_string(player[i].hp.base));
			PlayerWindow[i]->AddMessage("MP : " + to_string(player[i].mp.calc) + " / " + to_string(player[i].mp.base));
			PlayerWindow[i]->Draw();
		}
	}
	for (int i = 0; i < OPINIONWINDOW_NUM; i++) OpinionWindow[i]->Draw();
	MessageWindow->Draw();

	//printfDx("%d,%d,%d,%d,%d\n", commandAgi[0].who, commandAgi[1].who, commandAgi[2].who, commandAgi[3].who, commandAgi[4].who);
	//printfDx("%d,%d,%d,%d,%d", commandAgi[0].agi, commandAgi[1].agi, commandAgi[2].agi, commandAgi[3].agi, commandAgi[4].agi);
}

int BattleManager::SkillMeasure(int index)
{
	for (int i = 0; i < 16; i++) {
		if(enemySkill[index][i] == -1) return i;
	}
	return 0;
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
	player[index] = GData.GetCharacter(index);
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
	for (int i = 0; i < ENEMY_SKILL_SIZE; i++) {
		enemySkillSize[i] = (int)enemySkill[i].size();
	}

	enemy.intel.calc = enemy.intel.base;
	for (int i = 0; i < SKILL_CODE_SIZE; i++) enemy.skillCode[i] = (int)GetRand(1);
	*/
	enemy = GData.GetEnemy(GData.GetStage());
	for (int i = 0; i < SKILL_SIZE; i++) {
		if (enemy.skillCode[i]) {
			switch (GData.GetSkillPoint(i, 2)) {
			case 0:
				for (int j = 0; j < 16; j++) {
					if (enemySkill[0][j] == -1) enemySkill[0][j] = i; break;
				}
				break;
			case 1:
				for (int j = 0; j < 16; j++) {
					if (enemySkill[1][j] == -1) enemySkill[1][j] = i; break;
				}
				break;
			case 2:
				for (int j = 0; j < 16; j++) {
					if (enemySkill[2][j] == -1) enemySkill[2][j] = i; break;
				}
				break;
			case 3:
				for (int j = 0; j < 16; j++) {
					if (enemySkill[3][j] == -1) enemySkill[3][j] = i; break;
				}
				break;
			case 4:
				for (int j = 0; j < 16; j++) {
					if (enemySkill[3][j] == -1) enemySkill[3][j] = i; break;
				}
				break;
			case 5:
				for (int j = 0; j < 16; j++) {
					if (enemySkill[3][j] == -1) enemySkill[3][j] = i; break;
				}
				break;
			case 6:
				for (int j = 0; j < 16; j++) {
					if (enemySkill[3][j] == -1) enemySkill[3][j] = i; break;
				}
				break;
			case 7:
				break;
			}
		}
	}
	/*
	string str = "";
	str += "resource/picture/scenario";
	str += to_string(GData.GetScenario());
	str += "/character/enemy";
	str += to_string(GData.GetStage());
	str += ".png";
	enemy.image = LoadGraph(str.c_str());
	
//	enemy.image = LoadGraph("resource/picture/scenario0/character/enemy0.png");
	if (enemy.image == -1) {
		printfDx("enemy image read error");
	}
	*/
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
			//OpinionWindow[1]->AddMessage(GData.GetItemText(i, 0) + " �~ " + to_string(GData.GetItemPoint(i, 8)));
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
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].str.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
		break;
	case 1:
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].vit.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
		break;
	case 2:
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].agi.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
		break;
	case 3:
		aPlayer[pIndex].value[GData.GetSkillPoint(sIndex, 2)] = player[pIndex].intel.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
		break;
	}
}

void BattleManager::SetEnemySkill(int sIndex, int tIndex)
{
	aPlayer[4].name = GData.GetSkillText(sIndex, 0);
	aPlayer[4].cost = GData.GetSkillPoint(sIndex, 1);
	aPlayer[4].target = tIndex;
	switch (GData.GetSkillPoint(sIndex, 3)) {
	case 0:
		aPlayer[4].value[GData.GetSkillPoint(sIndex, 2)] = enemy.str.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
		break;
	case 1:
		aPlayer[4].value[GData.GetSkillPoint(sIndex, 2)] = enemy.vit.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
		break;
	case 2:
		aPlayer[4].value[GData.GetSkillPoint(sIndex, 2)] = enemy.agi.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
		break;
	case 3:
		aPlayer[4].value[GData.GetSkillPoint(sIndex, 2)] = enemy.intel.calc * (GData.GetSkillPoint(sIndex, 4) / 100);
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
	else OpinionWindow[2]->AddMessage("�S��");
}

void BattleManager::BattleInitialize()
{
	if (!isPause) {
		isPause = true;
		MessageWindow->AddMessage("�G�����ꂽ!!!");
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
		if (player[phase[2]].state[0] == 1 || player[phase[2]].flag == 0) {
			phase[1] = 4;
			break;
		}
		MessageWindow->AddMessage(player[phase[2]].name + "�͂ǂ�����H");
		OpinionWindow[0]->Activate();
		OpinionWindow[1]->InActivate();
		phase[1]++;
		break;
	case 1:
	case 2:
	case 3:
		//�L�[���͂ő���
		if (mKey[KEY_INPUT_UP] == 1) OpinionWindow[phase[1]-1]->ScrollUp();
		else if (mKey[KEY_INPUT_LEFT] == 1) OpinionWindow[phase[1]-1]->PageDown();
		else if (mKey[KEY_INPUT_DOWN] == 1) OpinionWindow[phase[1]-1]->ScrollDown();
		else if (mKey[KEY_INPUT_RIGHT] == 1) OpinionWindow[phase[1]-1]->PageUp();
		else if (mKey[KEY_INPUT_Z] == 1) {
			if (phase[1] == 1) {
				if (OpinionWindow[0]->Enter() == "�U��") {
					aPlayer[phase[2]].commandType = skill;
					aPlayer[phase[2]].name = "�U��";
					aPlayer[phase[2]].cost = 0;
					aPlayer[phase[2]].forParty = false;
					aPlayer[phase[2]].value[attack] = player[phase[2]].str.calc;
					phase[1]+=2;
				}
				else if (OpinionWindow[0]->Enter() == "�X�L��") LoadSkill(phase[2]);
				else if (OpinionWindow[0]->Enter() == "����") LoadItem();
				else if (OpinionWindow[0]->Enter() == "�h��") {
					aPlayer[phase[2]].commandType = defence;
					aPlayer[phase[2]].name = "�h��";
					aPlayer[phase[2]].cost = 0;
					aPlayer[phase[2]].forParty = false;
					phase[1] += 2;
				}
				OpinionWindow[0]->InActivate();
				OpinionWindow[1]->Activate();
			}
			else if (phase[1] == 2) {
				if (OpinionWindow[0]->Enter() == "�X�L��") {
					aPlayer[phase[2]].commandType = skill;
					if (GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 6) == 0) aPlayer[phase[2]].forParty = true;
					else aPlayer[phase[2]].forParty = false;
					SetTarget(GData.GetSkillPoint(GData.SkillStringToNum(OpinionWindow[1]->Enter()), 6));
				}
				else if (OpinionWindow[0]->Enter() == "����") {
					aPlayer[phase[2]].commandType = item;
					if (GData.GetItemPoint(GData.ItemStringToNum(OpinionWindow[1]->Enter()), 7) == 0) aPlayer[phase[2]].forParty = true;
					else aPlayer[phase[2]].forParty = false;
					SetTarget(GData.GetItemPoint(GData.ItemStringToNum(OpinionWindow[1]->Enter()), 7));
				}
				OpinionWindow[1]->InActivate();
				OpinionWindow[2]->Activate();
			}
			else if (phase[1] == 3) {
				if (OpinionWindow[0]->Enter() == "�X�L��") {
					SetSkill(GData.SkillStringToNum(OpinionWindow[1]->Enter()), phase[2], TargetNameToNum(OpinionWindow[2]->Enter()));
				}
				else if (OpinionWindow[0]->Enter() == "����") {
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
	/*for debug
	aPlayer[4].name = "BOSS_ATTACK";
	aPlayer[4].forParty = false;
	aPlayer[4].target = GetRand(CHARACTER_SIZE-1);
	aPlayer[4].value[attack] = GetRand(600);
	for (int i = 1; i < 7; i++) if (GetRand(100) > 50) aPlayer[4].value[i] = GetRand(100);
	phase[0]++;
	*/

	int rand[3] = {};
	rand[0] = GetRand(99);
	while (1) {
		rand[2] = GetRand(3);
		if (player[rand[2]].flag && player[rand[2]].state[0] == 0) break;
	}
	switch (enemy.operate) {
	case 0:
		if (rand[0] < 50 && SkillMeasure(0) != 0) {
			rand[1] = GetRand(SkillMeasure(0) - 1);
			aPlayer[4].forParty = true;
			SetEnemySkill(enemySkill[0][rand[1]], rand[2]);
		}
		else {
			aPlayer[4].commandType = skill;
			aPlayer[4].name = "�U��";
			aPlayer[4].cost = 0;
			aPlayer[4].forParty = true;
			aPlayer[4].target = rand[2];
			aPlayer[4].value[attack] = enemy.str.calc;
		}
		break;
	case 1:
		if (rand[0] < 20 && SkillMeasure(3) != 0) {
			rand[1] = GetRand(SkillMeasure(3) - 1);
			aPlayer[4].forParty = false;
			SetEnemySkill(enemySkill[3][rand[1]], rand[2]);
		}
		else if(rand[0] < 50){
			aPlayer[4].commandType = defence;
			aPlayer[4].name = "�h��";
			aPlayer[4].cost = 0;
			aPlayer[4].forParty = false;
		} 
		else {
			aPlayer[4].commandType = skill;
			aPlayer[4].name = "�U��";
			aPlayer[4].cost = 0;
			aPlayer[4].forParty = true;
			aPlayer[4].target = rand[2];
			aPlayer[4].value[attack] = enemy.str.calc;
		}
		break;
	case 2:
		if ((double) enemy.hp.calc / enemy.hp.base < 0.3 && SkillMeasure(1) != 0) {
			rand[1] = GetRand(SkillMeasure(1) - 1);
			aPlayer[4].forParty = false;
			SetEnemySkill(enemySkill[1][rand[1]], rand[2]);
		}
		else if (rand[0] < 20) {
			aPlayer[4].commandType = defence;
			aPlayer[4].name = "�h��";
			aPlayer[4].cost = 0;
			aPlayer[4].forParty = false;
		}
		else {
			aPlayer[4].commandType = skill;
			aPlayer[4].name = "�U��";
			aPlayer[4].cost = 0;
			aPlayer[4].forParty = true;
			aPlayer[4].target = rand[2];
			aPlayer[4].value[attack] = enemy.str.calc;
		}
		break;
	case 3:
		if ((double)enemy.hp.calc / enemy.hp.base < 0.3 && SkillMeasure(1) != 0) {
			rand[1] = GetRand(SkillMeasure(1) - 1);
			aPlayer[4].forParty = false;
			SetEnemySkill(enemySkill[1][rand[1]], rand[2]);
		}
		else if (rand[0] < 20 && SkillMeasure(3) != 0) {
			rand[1] = GetRand(SkillMeasure(3) - 1);
			aPlayer[4].forParty = false;
			SetEnemySkill(enemySkill[3][rand[1]], rand[2]);
		}
		else if (rand[0] < 40) {
			aPlayer[4].commandType = defence;
			aPlayer[4].name = "�h��";
			aPlayer[4].cost = 0;
			aPlayer[4].forParty = false;
		}
		else {
			aPlayer[4].commandType = skill;
			aPlayer[4].name = "�U��";
			aPlayer[4].cost = 0;
			aPlayer[4].forParty = true;
			aPlayer[4].target = rand[2];
			aPlayer[4].value[attack] = enemy.str.calc;
		}
		break;
	}
	phase[0]++;
}

void BattleManager::CalcManager()
{
	if (commandAgi[phase[2]].who == CHARACTER_SIZE) {
		if (EnemyCalc()) CommandAgiSort(phase[2]);
		//printfDx("P ");
	}
	else if(commandAgi[phase[2]].who != CHARACTER_SIZE){
		if (PlayerCalc(commandAgi[phase[2]].who)) CommandAgiSort(phase[2]);
	}
}

bool asc(const CommandAgi& right, const CommandAgi& left) {
	return left.agi == right.agi ? (left.who < right.who) : (left.agi < right.agi);
}

void BattleManager::CommandAgiSort(int index)
{
	for (int i = 0; i < CHARACTER_SIZE + 1; i++) {
		if (0 <= commandAgi[i].who < CHARACTER_SIZE) {
			commandAgi[i].agi = player[commandAgi[i].who].agi.calc;
		}
		else {
			commandAgi[i].agi = enemy.agi.calc;
		}
	}
	commandAgi[CHARACTER_SIZE].agi = enemy.agi.calc;

	sort(&commandAgi[index], &commandAgi[CHARACTER_SIZE + 1], asc);
}

bool BattleManager::PlayerCalc(int index)
{
	//printfDx("P ");
	switch (phase[1]) {
	case 0:
		if (player[index].state[0] == 1 || aPlayer[index].name == "" || player[index].flag == 0) {
			if (phase[2] == CHARACTER_SIZE) {
				phase[2] = 0;
				phase[0]++;
				return 0;
				for (int i = 0; i < CHARACTER_SIZE + 1; i++) {
					damageCut[i] = 1.0;
				}
			}
			else {
				phase[2]++;
				return 0;
			}
			break;
		}
		//���b�Z�[�W�\��
		if (aPlayer[index].commandType == item) MessageWindow->AddMessage(player[index].name + "��" + aPlayer[index].name + "���g����");
		else if (aPlayer[index].commandType == defence) {
			MessageWindow->AddMessage(player[index].name + "�͐g�\���Ă���");
			damageCut[index] = 0.5;
		}
		else MessageWindow->AddMessage(player[index].name + "��" + aPlayer[index].name);

		player[index].mp.calc -= aPlayer[index].cost;

		if (aPlayer[index].value[attack] > 0) {
			//�U������
			enemy.hp.calc -= aPlayer[index].value[attack] * damageCut[CHARACTER_SIZE];
			if (enemy.hp.calc < 0) {
				enemy.hp.calc = 0;
				phase[0] = 5;
			}

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(enemy.name + "��" + to_string((int) (aPlayer[index].value[attack] * damageCut[CHARACTER_SIZE])) + "�̃_���[�W�I�I");
		}
		if (aPlayer[index].value[healHp] > 0) {
			if (player[aPlayer[index].target].state[0] == 1) {
				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͎���ł���c");
			}
			else {
				//HP�񕜏���
				player[aPlayer[index].target].hp.calc += aPlayer[index].value[healHp];
				if (player[aPlayer[index].target].hp.calc > player[aPlayer[index].target].hp.base) player[aPlayer[index].target].hp.calc = player[aPlayer[index].target].hp.base;

				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "��" + to_string(aPlayer[index].value[healHp]) + "��HP�񕜁I�I");
			}
		}
		if (aPlayer[index].value[healMp] > 0) {
			if (player[aPlayer[index].target].state[0] == 1) {
				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͎���ł���c");
			}
			else {
				//MP�񕜏���
				player[aPlayer[index].target].mp.calc += aPlayer[index].value[healMp];
				if (player[aPlayer[index].target].mp.calc > player[aPlayer[index].target].mp.base) player[aPlayer[index].target].mp.calc = player[aPlayer[index].target].mp.base;

				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "��" + to_string(aPlayer[index].value[healMp]) + "��MP�񕜁I�I");
			}
		}
		if (aPlayer[index].value[buffStr] > 0) {
			if (player[aPlayer[index].target].state[0] == 1) {
				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͎���ł���c");
			}
			else {
				//�o�t����
				player[aPlayer[index].target].str.calc *= (double)aPlayer[index].value[buffStr] / 100 + 1;

				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�̍U���͂��㏸�I");
			}
		}
		if (aPlayer[index].value[buffVit] > 0) {
			if (player[aPlayer[index].target].state[0] == 1) {
				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͎���ł���c");
			}
			else {
				//�o�t����
				player[aPlayer[index].target].vit.calc *= (double)aPlayer[index].value[buffVit] / 100 + 1;

				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�̐����͂��㏸�I");
			}
		}
		if (aPlayer[index].value[buffAgi] > 0) {
			if (player[aPlayer[index].target].state[0] == 1) {
				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͎���ł���c");
			}
			else {
				//�o�t����
				player[aPlayer[index].target].agi.calc *= (double)aPlayer[index].value[buffAgi] / 100 + 1;

				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�̑f�������㏸�I");
			}
		}
		if (aPlayer[index].value[buffInt] > 0) {
			if (player[aPlayer[index].target].state[0] == 1) {
				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͎���ł���c");
			}
			else {
				//�o�t����
				player[aPlayer[index].target].intel.calc *= (double)aPlayer[index].value[buffInt] / 100 + 1;

				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�̌������㏸�I");
			}
		}
		if (aPlayer[index].value[reviv] > 0) {
			//�h������
			if (player[aPlayer[index].target].state[0] == 1) {
				if (GetRand(100) <= aPlayer[index].value[reviv]) {
					player[aPlayer[index].target].hp.calc += player[aPlayer[index].target].hp.base / 2;
					player[aPlayer[index].target].state[0] = 0;

					//���b�Z�[�W�\��
					MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͑��𐁂��Ԃ����I");
				}
				else {
					//���b�Z�[�W�\��
					MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͑��𐁂��Ԃ��Ȃ������c");
				}
			}
			else {
				//���b�Z�[�W�\��
				MessageWindow->AddMessage(player[aPlayer[index].target].name + "�͐����Ă���");
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
			if (phase[2] > CHARACTER_SIZE) {
				phase[2] = 0;
				phase[0]++;
				for (int i = 0; i < CHARACTER_SIZE + 1; i++) {
					damageCut[i] = 1.0;
				}
			}
			return 1;
		}
	}
	return 0;
}

bool BattleManager::EnemyCalc()
{
	if (!isPause) {
		isPause = true;
		//���b�Z�[�W�\��
		if (aPlayer[4].commandType == defence) {
			MessageWindow->AddMessage(enemy.name + "�͐g�\���Ă���");
			damageCut[4] = 0.5;
		}
		else {
			MessageWindow->AddMessage(enemy.name + "��" + aPlayer[4].name);
		}

		if (aPlayer[4].value[attack] > 0) {
			//�U������
			if (aPlayer[aPlayer[4].target].commandType == defence) player[aPlayer[4].target].hp.calc -= aPlayer[4].value[attack] / 2;
			else player[aPlayer[4].target].hp.calc -= aPlayer[4].value[attack] * damageCut[aPlayer[4].target];

			if (player[aPlayer[4].target].hp.calc <= 0) {
				player[aPlayer[4].target].hp.calc = 0;
				player[aPlayer[4].target].state[0] = 1;
			}
			if ((player[0].state[0] == 1 ||  player[0].flag == 0)
				&& (player[1].state[0] == 1 || player[1].flag == 0)
				&& (player[2].state[0] == 1 || player[2].flag == 0)
				&& (player[3].state[0] == 1 || player[3].flag == 0)) {
				phase[0] = 6;
				return 0;
			}

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(player[aPlayer[4].target].name + "��" + to_string((int)(aPlayer[4].value[attack] * damageCut[aPlayer[4].target])) + "�̃_���[�W�I�I");
		}
		if (aPlayer[4].value[healHp] > 0) {
			//HP�񕜏���
			enemy.hp.calc += aPlayer[4].value[healHp];
			if (enemy.hp.calc > enemy.hp.base) enemy.hp.calc = enemy.hp.base;

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(enemy.name + "��" + to_string(aPlayer[4].value[healHp]) + "��HP�񕜁I�I");
		}
		if (aPlayer[4].value[healMp] > 0) {
			//MP�񕜏���
			enemy.mp.calc += aPlayer[4].value[healMp];
			if (enemy.mp.calc >enemy.mp.base) enemy.mp.calc = enemy.mp.base;

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(enemy.name + "��" + to_string(aPlayer[4].value[healMp]) + "��MP�񕜁I�I");
		}
		if (aPlayer[4].value[buffStr] > 0) {
			//�o�t����
			enemy.str.calc *= (double)aPlayer[4].value[buffStr] / 100 + 1;

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(enemy.name + "�̍U���͂��㏸�I");
		}
		if (aPlayer[4].value[buffVit] > 0) {
			//�o�t����
			enemy.vit.calc *= (double)aPlayer[4].value[buffVit] / 100 + 1;

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(enemy.name + "�̐����͂��㏸�I");
		}
		if (aPlayer[4].value[buffAgi] > 0) {
			//�o�t����
			enemy.agi.calc *= (double)aPlayer[4].value[buffAgi] / 100 + 1;

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(enemy.name + "�̑f�������㏸�I");
		}
		if (aPlayer[4].value[buffInt] > 0) {
			//�o�t����
			enemy.intel.calc *= (double)aPlayer[4].value[buffInt] / 100 + 1;

			//���b�Z�[�W�\��
			MessageWindow->AddMessage(enemy.name + "�̌������㏸�I");
		}
		//if (aPlayer[4].value[reviv] > 0) {
		//	//�h������
		//	if (enemy.state[0]) {
		//		if (GetRand(100) <= aPlayer[4].value[reviv]) {
		//			enemy.hp.calc += enemy.hp.base / 2;

		//			//���b�Z�[�W�\��
		//			MessageWindow->AddMessage(enemy.name + "�͑��𐁂��Ԃ����I");
		//		}
		//		else {
		//			//���b�Z�[�W�\��
		//			MessageWindow->AddMessage(enemy.name + "�͑��𐁂��Ԃ��Ȃ������c");
		//		}
		//	}
		//	else {
		//		//���b�Z�[�W�\��
		//		MessageWindow->AddMessage(enemy.name + "�͐����Ă���");
		//	}
		//}
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		MessageWindow->ClearMessage();
		isPause = false;
		if (phase[2] != CHARACTER_SIZE) phase[2]++;
		else {
			phase[2] = 0;
			phase[0]++;
		}
		return 1;
	}
	return 0;
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
	aPlayer[4].cost = 0;
	aPlayer[4].forParty = false;
	aPlayer[4].name = "";
	aPlayer[4].target = 0;
	for (int j = 0; j < 8; j++) aPlayer[4].value[j] = 0;

	phase[0] = 1;
}

bool BattleManager::BattleEnd(bool isWin)
{
	if (isWin) {
		//��������
		if (!isPause) {
			isPause = true;
			MessageWindow->ClearMessage();
			MessageWindow->AddMessage(enemy.name + "��|�����I�I�I");
		}
		else if (mKey[KEY_INPUT_Z] == 1) {
			for (int i = 0; i < CHARACTER_SIZE; i++) GData.SetCharacterData(i, player[i]);
			GData.SceneBackRequest();
//			GData.SceneRequest(1, 2);
			GMusic.StopSound(battleBgm);
			GMusic.ReserveSound(GData.GetDungeonBgm(), DX_PLAYTYPE_LOOP);
			return 1;
		}
	}
	else {
		//�s�k����
		if (!isPause) {
			isPause = true;
			MessageWindow->ClearMessage();
			MessageWindow->AddMessage("�p�[�e�B�[�͑S�ł����c");
		}
		else if (mKey[KEY_INPUT_Z] == 1) {
			GData.SceneRequest(1, 2);
			GMusic.StopSound(battleBgm);
			GMusic.ReserveSound(GData.GetDungeonBgm(), DX_PLAYTYPE_LOOP);
			return 1;
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
