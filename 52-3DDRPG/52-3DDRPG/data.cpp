#include "define.h"

Data_c::Data_c()
{
}
Data_c::~Data_c()
{
}

void Data_c::LoadAll(int scenario)
{
	ItemLoad(scenario);
	SoubiLoad(scenario);
	SkillLoad(scenario);
	CharacterLoad(scenario);
}
void Data_c::ItemLoad(int scenario)
{
	int n, num, i, fp;
	char fname[32];
	int input[64];
	char inputc[64];

	sprintf_s(fname, "resource/item_%d.csv", scenario);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i<1; i++)//最初の2行読み飛ばす
		while (FileRead_getc(fp) != '\n');

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
		case 0: item[n].num = atoi(inputc);			break;
		case 1: strcpy_s(item[n].name, inputc);		break;
		case 2: item[n].type = atoi(inputc);		break;
		case 3: item[n].effect1 = atoi(inputc);		break;
		case 4: item[n].point1 = atoi(inputc);		break;
		case 5: item[n].area = atoi(inputc);		break;
		case 6: item[n].effect2 = atoi(inputc);		break;
		case 7: item[n].point2 = atoi(inputc);		break;
		case 8: strcpy_s(item[n].explain, inputc);	break;
		}
		num++;
		if (num == 9) {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}
void Data_c::SoubiLoad(int scenario)
{
	int n, num, i, fp;
	char fname[32];
	int input[64];
	char inputc[64];

	sprintf_s(fname, "resource/soubi_%d.csv", scenario);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i<1; i++)//最初の2行読み飛ばす
		while (FileRead_getc(fp) != '\n');

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
		case 0: soubi[n].num = atoi(inputc);		break;
		case 1: strcpy_s(soubi[n].name, inputc);	break;
		case 2: soubi[n].type = atoi(inputc);		break;
		case 3: soubi[n].effect = atoi(inputc);		break;
		case 4: soubi[n].point = atoi(inputc);		break;
		case 5: soubi[n].area = atoi(inputc);		break;
		case 6: strcpy_s(soubi[n].explain, inputc);	break;
		}
		num++;
		if (num == 7) {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}
void Data_c::SkillLoad(int scenario)
{
	int n, num, i, fp;
	char fname[32];
	int input[64];
	char inputc[64];

	sprintf_s(fname, "resource/skill_%d.csv", scenario);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i<1; i++)//最初の2行読み飛ばす
		while (FileRead_getc(fp) != '\n');

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
		case 0: skill[n].num = atoi(inputc);			break;
		case 1: strcpy_s(skill[n].name, inputc);		break;
		case 2: skill[n].MP = atoi(inputc);				break;
		case 3: skill[n].effect = atoi(inputc);			break;
		case 4: skill[n].status = atoi(inputc);			break;
		case 5: skill[n].magnification = atof(inputc);	break;
		case 6: skill[n].area = atoi(inputc);			break;
		case 7: strcpy_s(skill[n].explain, inputc);		break;
		}
		num++;
		if (num == 8) {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);
}
void Data_c::CharacterLoad(int scenario)
{
	int n, num, i, fp;
	char fname[32];
	int input[64];
	char inputc[64];

	sprintf_s(fname, "resource/character_%d.csv", scenario);

	fp = FileRead_open(fname);//ファイル読み込み
	if (fp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i<1; i++)//最初の2行読み飛ばす
		while (FileRead_getc(fp) != '\n');

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
		case 0:		strcpy_s(character[n].name, inputc);				break;
		case 1:		character[n].HPMAX = atoi(inputc);					break;
		case 2:		character[n].MPMAX = atoi(inputc);					break;
		case 3:		character[n].STR = atoi(inputc);					break;
		case 4:		character[n].VIT = atoi(inputc);					break;
		case 5:		character[n].AGI = atoi(inputc);					break;
		case 6:		character[n].INT = atoi(inputc);					break;
		default:	character[n].skillCode[num - 7] = atoi(inputc);		break;
		}
		num++;
		if (num == 15) {
			num = 0;
			n++;
		}
	}
EXFILE:
	FileRead_close(fp);

	char gname[64];

	for (int i = 0; i < CHARACTER_SIZE; i++) {
		sprintf_s(gname, "resource/%d_chara%d.png", scenario, i);
		character[i].Image = LoadGraph(gname);
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
	}
	return 0;
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
	}
	return 0;
}
string Data_c::GetSoubiText(int num, int sort)
{
	switch (sort) {
	case 0:
		return string(soubi[num].name);
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
		return skill[num].MP;
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
	}
	return 0;
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
int Data_c::GetCharacterPoint(int num, int sort)
{
	switch (sort) {
	case 0:
		return character[num].HPMAX;
		break;
	case 1:
		return character[num].MPMAX;
		break;
	case 2:
		return character[num].HP;
		break;
	case 3:
		return character[num].MP;
		break;
	case 4:
		return character[num].STR;
		break;
	case 5:
		return character[num].VIT;
		break;
	case 6:
		return character[num].AGI;
		break;
	case 7:
		return character[num].INT;
		break;
	case 8:
		return character[num].Image;
		break;
	}
	return 0;
}
int Data_c::GetCharacterSkillCode(int num, int order)
{
	return character[num].skillCode[order];
}
string Data_c::GetCharacterName(int num)
{
	return string(character[num].name);
}

int Data_c::GetScenario()
{
	return scenario;
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


void Data_c::SetScenario(int i)
{
	scenario = i;
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