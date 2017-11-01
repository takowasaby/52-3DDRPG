#include "define.h"

Data_c::Data_c() :
	scenario(0),
	stage(0),
	dir(0),
	room(-1),
	dungeonX(1),
	dungeonY(3),
	playCount(0),
	BMode(0),
	BScene(0),
	EventCallFlag(0)
{
	controlMode = 1;
	eventScene = 0;
	titleScene = 2;
	gameScene = 3;

	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			wallType[i][j] = 0;
		}
	}
	for (int i = 0; i < SCENARIO_SIZE; i++) {
		for (int j = 0; j < STAGE_SIZE; j++) {
			for (int k = 0; k < MAP_SIZE_X; k++) {
				for (int l = 0; l < MAP_SIZE_Y; l++) {
					mapFlag[i][j][k][l] = 0;
				}
			}
		}
	}
	for (int i = 0; i < SCENARIO_SIZE; i++) {
		for (int j = 0; j < EVENT_SIZE; j++) {
			eventFlag[i][j] = 0;
			GoalText[i][j] = "";
		}
	}
}
/*
Data_c::Data_c(int * mode, int * event_scene, int * title_scene, int * game_scene) :
controlMode(mode),
eventScene(event_scene),
titleScene(title_scene),
gameScene(game_scene)
{
Data_c();
}
*/
Data_c::~Data_c()
{
}

void Data_c::LoadAll(int s)
{
	ItemLoad(s);
	GoalLoad(s);
	SoubiLoad(s);
	SkillLoad(s);
	CharacterLoad(s);
}
void Data_c::DeleteAll()
{
	for (int i = 0; i < CHARACTER_SIZE; i++) {
		character[i].num = -1;
		character[i].name = "";
		character[i].flag = 0;
		character[i].soubi[0] = -1;
		character[i].soubi[1] = -1;
		character[i].hp.base = 0;
		character[i].hp.calc = 0;
		character[i].mp.base = 0;
		character[i].mp.calc = 0;
		character[i].str.base = 0;
		character[i].str.calc = 0;
		character[i].vit.base = 0;
		character[i].vit.calc = 0;
		character[i].agi.base = 0;
		character[i].agi.calc = 0;
		character[i].intel.base = 0;
		character[i].intel.calc = 0;
		for (int j = 0; j < SKILL_SIZE; j++) {
			character[i].skillCode[j] = 0;
		}
		for (int j = 0; j < STATE_SIZE; j++) {
			character[i].state[j] = 0;
		}
		character[i].image = 0;
	}
	for (int i = 0; i < SKILL_SIZE; i++) {
		skill[i].num = -1;
		skill[i].name = "";
		skill[i].target = -1;
		skill[i].mp = 0;
		skill[i].effect = -1;
		skill[i].status = -1;
		skill[i].magnification = 0;
		skill[i].area = -1;
		skill[i].explain = "";
	}
	for (int i = 0; i < ITEM_SIZE; i++) {
		item[i].num = -1;
		item[i].name = "";
		item[i].flag = 0;
		item[i].target = -1;
		item[i].type = -1;
		item[i].effect1 = -1;
		item[i].point1 = -1;
		item[i].effect2 = -1;
		item[i].point2 = -1;
		item[i].area = -1;
		item[i].explain = "";
	}
	for (int i = 0; i < SOUBI_SIZE; i++) {
		soubi[i].num = -1;
		soubi[i].name = "";
		soubi[i].flag = 0;
		soubi[i].type = -1;
		soubi[i].effect = -1;
		soubi[i].point = -1;
		soubi[i].area = -1;
		soubi[i].explain = "";
	}
}
void Data_c::GoalLoad(int s)
{
	int n, i, fp;
	char fname[32];
	int input[64];
	char inputc[64];

	sprintf_s(fname, "resource/goal_%d.csv", s);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
//		printfDx("read error\n");
		return;
	}

	n = 0;
	while (1) {
		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		GoalText[s][n] = inputc;
		n++;
	}
EXFILE:
	FileRead_close(fp);
}
void Data_c::ItemLoad(int s)
{
	int n, num, i, fp;
	char fname[32];
	int input[512];
	char inputc[512];
	int dataNum = 0;

	sprintf_s(fname, "resource/data/item_%d.csv", s);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<512; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		switch (num) {
		case 0:
			item[n].num = atoi(inputc);
			dataNum = atoi(inputc);	
			break;
		case 1: item[n].name = inputc;				break;
		case 2: item[n].type = atoi(inputc);		break;
		case 3:
			item[n].effect1 = atoi(inputc);		
			if (atoi(inputc) >= 1) {
				item[n].target = 0;
			}
			else {
				item[n].target = 1;
			}
			break;
		case 4: item[n].point1 = atoi(inputc);		break;
		case 5: item[n].area = atoi(inputc);		break;
		case 6: item[n].effect2 = atoi(inputc);		break;
		case 7: item[n].point2 = atoi(inputc);		break;
		case 8: item[n].explain = inputc;			break;
		}
		//
		item[n].flag = 1;
		//
		num++;
		if (input[i] == '\n') {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}
void Data_c::SoubiLoad(int s)
{
	int n, num, i, fp;
	char fname[32];
	int input[512];
	char inputc[512];
	int dataNum;

	sprintf_s(fname, "resource/data/soubi_%d.csv", s);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<512; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		switch (num) {
		case 0:
			item[n].num = atoi(inputc);
			dataNum = atoi(inputc);
			break;
		case 1: soubi[n].name = inputc;				break;
		case 2: soubi[n].type = atoi(inputc);		break;
		case 3: soubi[n].effect = atoi(inputc);		break;
		case 4: soubi[n].point = atoi(inputc);		break;
		case 5: soubi[n].area = atoi(inputc);		break;
		case 6: soubi[n].explain = inputc;			break;
		}
		//
		soubi[n].flag = 1;
		//
		num++;
		if (input[i] == '\n') {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}
void Data_c::SkillLoad(int s)
{
	int n, num, i, fp;
	char fname[32];
	int input[512];
	char inputc[512];
	int dataNum;

	sprintf_s(fname, "resource/data/skill_%d.csv", s);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<512; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		switch (num) {
		case 0:
			item[n].num = atoi(inputc);
			dataNum = atoi(inputc);
			break;
		case 1: skill[n].name = inputc;					break;
		case 2: skill[n].mp = atoi(inputc);				break;
		case 3:
			skill[n].effect = atoi(inputc);	
			if (atoi(inputc) >= 1) {
				skill[n].target = 0;
			}
			else {
				skill[n].target = 1;
			}
			break;
		case 4: skill[n].status = atoi(inputc);			break;
		case 5: skill[n].magnification = atof(inputc);	break;
		case 6: skill[n].area = atoi(inputc);			break;
		case 7: skill[n].explain = inputc;				break;
		}
		num++;
		if (input[i] == '\n') {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}
void Data_c::CharacterLoad(int s)
{
	int n, num, i, fp;
	char fname[32];
	int input[64];
	char inputc[64];

	sprintf_s(fname, "resource/data/character_%d.csv", s);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}

	n = 0, num = 0;
	while (1) {
		for (i = 0; i<64; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(fp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら
				goto EXFILE;//終了
			}
		}
		switch (num) {
		case 0:
			item[n].num = num;
			character[n].name = inputc;							
			break;
		case 1:		
			character[n].hp.base = atoi(inputc);
			character[n].hp.calc = atoi(inputc); 
			break;
		case 2:		
			character[n].mp.base = atoi(inputc);
			character[n].mp.calc = atoi(inputc);
			break;
		case 3:		
			character[n].str.base = atoi(inputc);
			character[n].str.calc = atoi(inputc);
			break;
		case 4:		
			character[n].vit.base = atoi(inputc);
			character[n].vit.calc = atoi(inputc);
			break;
		case 5:		
			character[n].agi.base = atoi(inputc);
			character[n].agi.calc = atoi(inputc);
			break;
		case 6:		
			character[n].intel.base = atoi(inputc);
			character[n].intel.calc = atoi(inputc);
			break;
		default:	
			if (atoi(inputc) != -1) {
				character[n].skillCode[atoi(inputc)] = 1;
			}
			break;
		}
		//
		character[n].flag = 1;
		//
		num++;
		if (input[i] == '\n') {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);

	char gname[64];

	for (int i = 0; i < CHARACTER_SIZE; i++) {
		sprintf_s(gname, "resource/picture/%d/%d.png", scenario, i);
		character[i].image = LoadGraph(gname);
	}
}

int Data_c::GetItemFlag(int num)
{
	return item[num].flag;
}
int Data_c::GetSoubiFlag(int num)
{
	return soubi[num].flag;
}
int Data_c::GetCharacterFlag(int num)
{
	return character[num].flag;
}

int Data_c::GetItemPoint(int num, int sort)
{
	map<string, int>::iterator itr;

	switch (sort) {
	case 0:
		return item[num].num;
		break;
	case 1:
		return item[num].type;
		break;
	case 2:
		return item[num].effect1;
		break;
	case 3:
		return item[num].effect2;
		break;
	case 4:
		return item[num].point1;
		break;
	case 5:
		return item[num].point2;
		break;
	case 6:
		return item[num].area;
		break;
	case 7:
		return item[num].target;
		break;
	case 8:
		return item[num].flag;
		break;
	}

	return 0;
}
void Data_c::SetItemPoint(int num, int sort, int point)
{
	switch (sort) {
	case 0:
		item[num].num = point;
		break;
	case 1:
		item[num].type = point;
		break;
	case 2:
		item[num].effect1 = point;
		break;
	case 3:
		item[num].effect2 = point;
		break;
	case 4:
		item[num].point1 = point;
		break;
	case 5:
		item[num].point2 = point;
		break;
	case 6:
		item[num].area = point;
		break;
	case 7:
		item[num].target = point;
		break;
	case 8:
		item[num].flag = point;
		break;
	}
}
string Data_c::GetItemText(int num, int sort)
{
	switch (sort) {
	case 0:
		return string(item[num].name);
		break;
	case 1:
		return string(item[num].explain);
		break;
	}
	return 0;
}
int Data_c::ItemStringToNum(string name)
{
	for (int i = 0; i < ITEM_SIZE; i++) {
		if (name == item[i].name) {
			return i;
		}
	}
	return -1;
}

int Data_c::GetSoubiPoint(int num, int sort)
{
	switch (sort) {
	case 0:
		return soubi[num].num;
		break;
	case 1:
		return soubi[num].type;
		break;
	case 2:
		return soubi[num].effect;
		break;
	case 3:
		return soubi[num].point;
		break;
	case 4:
		return soubi[num].area;
		break;
	case 5:
		return soubi[num].flag;
		break;
	}
	return 0;
}
void Data_c::SetSoubiPoint(int num, int sort, int point)
{
	switch (sort) {
	case 0:
		soubi[num].num = point;
		break;
	case 1:
		soubi[num].type = point;
		break;
	case 2:
		soubi[num].effect = point;
		break;
	case 3:
		soubi[num].point = point;
		break;
	case 4:
		soubi[num].area = point;
		break;
	case 5:
		soubi[num].flag = point;
		break;
	}
}
string Data_c::GetSoubiText(int num, int sort)
{
	switch (sort) {
	case 0:
		return soubi[num].name;
		break;
	case 1:
		return string(soubi[num].explain);
		break;
	}
	return 0;
}

int Data_c::GetSkillPoint(int num, int sort)
{
	switch (sort) {
	case 0:
		return skill[num].num;
		break;
	case 1:
		return skill[num].mp;
		break;
	case 2:
		return skill[num].effect;
		break;
	case 3:
		return skill[num].status;
		break;
	case 4:
		return skill[num].magnification;
		break;
	case 5:
		return skill[num].area;
		break;
	case 6:
		return skill[num].target;
		break;
	}
	return 0;
}
void Data_c::SetSkillPoint(int num, int sort, int point)
{
	switch (sort) {
	case 0:
		skill[num].num = point;
		break;
	case 1:
		skill[num].mp = point;
		break;
	case 2:
		skill[num].effect = point;
		break;
	case 3:
		skill[num].status = point;
		break;
	case 4:
		skill[num].magnification = point;
		break;
	case 5:
		skill[num].area = point;
		break;
	case 6:
		skill[num].target = point;
		break;
	}
}
string Data_c::GetSkillText(int num, int sort)
{
	switch (sort) {
	case 0:
		return string(skill[num].name);
		break;
	case 1:
		return string(skill[num].explain);
		break;
	}
	return 0;
}
int Data_c::SkillStringToNum(string name)
{
	for (int i = 0; i < SKILL_SIZE; i++) {
		if (name == skill[i].name) {
			return i;
		}
	}
	return -1;
}

int Data_c::GetCharacterStatus(int num, int sort, int value)
{
	switch (sort) {
	case 0:
		if (value == 0) return character[num].hp.base;
		else return character[num].hp.calc;
		break;
	case 1:
		if (value == 0) return character[num].mp.base;
		else return character[num].mp.calc;
		break;
	case 2:
		if (value == 0) return character[num].str.base;
		else return character[num].str.calc;
		break;
	case 3:
		if (value == 0) return character[num].vit.base;
		else return character[num].vit.calc;
		break;
	case 4:
		if (value == 0) return character[num].agi.base;
		else return character[num].agi.calc;
		break;
	case 5:
		if (value == 0) return character[num].intel.base;
		else return character[num].intel.calc;
		break;
	}
	return 0;
}
void Data_c::SetCharacterStatus(int num, int sort, int point, int value)
{
	switch (sort) {
	case 0:
		if (value == 0) character[num].hp.base = point;
		else character[num].hp.calc = point;
		if (point == 0) character[num].state[0] = 1;
		break;
	case 1:
		if (value == 0) character[num].mp.base = point;
		else character[num].mp.calc = point;
		break;
	case 2:
		if (value == 0) character[num].str.base = point;
		else character[num].str.calc = point;
		break;
	case 3:
		if (value == 0) character[num].vit.base = point;
		else character[num].vit.calc = point;
		break;
	case 4:
		if (value == 0) character[num].agi.base = point;
		else character[num].agi.calc = point;
		break;
	case 5:
		if (value == 0) character[num].intel.base = point;
		else character[num].intel.calc = point;
		break;
	}
}
int Data_c::GetCharacterImage(int num)
{
	return character[num].image;
}
int Data_c::GetCharacterSoubi(int num, int type)
{
	return character[num].soubi[type];
}
void Data_c::SetCharacterSoubi(int num, int type, int soubiNum)
{
	for (int i = 0; i < 6; i++) {
		if (i == soubi[character[num].soubi[type]].effect) {
			SetCharacterStatus(num, i, GetCharacterStatus(num, i, 0), 1);
		}
	}
	character[num].soubi[type] = soubiNum;
	for (int i = 0; i < 6; i++) {
		if (i == soubi[soubiNum].effect) {
			SetCharacterStatus(num, i, GetCharacterStatus(num, i, 0) + soubi[soubiNum].point, 1);
		}
	}
}
bool Data_c::GetCharacterState(int num, int state)
{
	return character[num].state[state];
}
void Data_c::ChangeCharacterState(int num, int state)
{
	if (character[num].state[state] == TRUE) character[num].state[state] = FALSE;
	else character[num].state[state] = TRUE;
}
void Data_c::SetCharacterSkillCode(int num, int skillNum, int flag)
{
	character[num].skillCode[skillNum] = flag;
}
int Data_c::GetCharacterSkillCode(int num, int skillNum)
{
	return character[num].skillCode[skillNum];
}
string Data_c::GetCharacterName(int num)
{
	return string(character[num].name);
}

characterData Data_c::GetCharacter(int num)
{
	return character[num];
}

int Data_c::GetScenario()
{
	return scenario;
}
int Data_c::GetStage()
{
	return stage;
}
int Data_c::GetDungeonX()
{
	return dungeonX;
}
int Data_c::GetDungeonY()
{
	return dungeonY;
}

int Data_c::GetDir()
{
	return dir;
}

int Data_c::GetEventFlag()
{
	return EventCallFlag;
}

int Data_c::GetRoom()
{
	return room;
}

void Data_c::SetScenario(int i)
{
	GData.DeleteAll();
	GData.LoadAll(i);
	scenario = i;
}
void Data_c::SetStage(int i)
{
	stage = i;
}
void Data_c::SetDungeonX(int i)
{
	dungeonX = i;
}
void Data_c::SetDungeonY(int i)
{
	dungeonY = i;
}

void Data_c::SetDir(int i)
{
	dir = i;
}

void Data_c::SetEventFlag(int i)
{
	EventCallFlag = i;
}

void Data_c::SetRoom(int i)
{
	room = i;
}

int Data_c::GetMapFlag(int scenario, int stage, int x, int y)
{
	return mapFlag[scenario][stage][x][y];
}
int Data_c::GetEventFlag(int scenario, int num)
{
	return eventFlag[scenario][num];
}
int Data_c::GetPlayCount()
{
	return playCount;
}

int Data_c::GetWallType(int x, int y)
{
	return wallType[x][y];
}

void Data_c::SetMapFlag(int scenario, int stage, int x, int y, int i)
{
	mapFlag[scenario][stage][x][y] = i;
}
void Data_c::SetEventFlag(int scenario, int num, int i)
{
	eventFlag[scenario][num] = i;
}
void Data_c::SetPlayCount(int i)
{
	playCount = i;
}
void Data_c::AddPlayCount()
{
	playCount++;
}
void Data_c::SetWallType(int x, int y, int type)
{
	wallType[x][y] = type;
}

void Data_c::SceneRequest(int m, int s)
{
	if (EventCallFlag == 0) {
		BMode = controlMode;
		controlMode = m;
		switch (m) {
		case 0:
			BScene = eventScene;
			eventScene = s;
			break;
		case 1:
			BScene = titleScene;
			titleScene = s;
			break;
		case 2:
			BScene = gameScene;
			gameScene = s;
			break;
		}
	}
}
void Data_c::SceneBackRequest()
{
	if (EventCallFlag == 0) {
		controlMode = BMode;
		switch (BMode) {
		case 0:
			eventScene = BScene;
			break;
		case 1:
			titleScene = BScene;
			break;
		case 2:
			gameScene = BScene;
			break;
		}
	}
}

int Data_c::GetMode()
{
	return controlMode;
}
int Data_c::GetScene(int mode)
{
	switch (mode) {
	case 0: return eventScene; break;
	case 1: return titleScene; break;
	case 2: return gameScene; break;
	}
}

void Data_c::CalcItemFlag(int num, int vary)
{
	if (item[num].flag + vary >= ITEM_FLAG_MAX) {
		item[num].flag = ITEM_FLAG_MAX;
	}
	else if (item[num].flag + vary <= 0) {
		item[num].flag = 0;
	}
	else {
		item[num].flag += vary;
	}
}
void Data_c::CalcSoubiFlag(int num, int vary)
{
	if (soubi[num].flag + vary >= SOUBI_FLAG_MAX) {
		soubi[num].flag = SOUBI_FLAG_MAX;
	}
	else if (soubi[num].flag + vary <= 0) {
		soubi[num].flag = 0;
	}
	else {
		soubi[num].flag += vary;
	}
}
void Data_c::SetCharacterFlag(int num, int vary)
{
	character[num].flag = vary;
}

string Data_c::GetGoalText(int s, int num)
{
	return GoalText[s][num];
}
