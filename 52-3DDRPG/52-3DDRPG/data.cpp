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
		case 0: item[n].num = atoi(inputc);		break;
		case 1: strcpy(item[n].name, inputc);	break;
		case 2: item[n].type = atoi(inputc);	break;
		case 3: item[n].effect1 = atoi(inputc);	break;
		case 4: item[n].point1 = atoi(inputc);	break;
		case 5: item[n].area = atoi(inputc);	break;
		case 6: item[n].effect2 = atoi(inputc);	break;
		case 7: item[n].point2 = atoi(inputc);	break;
		case 8: strcpy(item[n].explain, inputc);break;
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
		case 1: strcpy(soubi[n].name, inputc);		break;
		case 2: soubi[n].type = atoi(inputc);		break;
		case 3: soubi[n].effect = atoi(inputc);		break;
		case 4: soubi[n].point = atoi(inputc);		break;
		case 5: soubi[n].area = atoi(inputc);		break;
		case 6: strcpy(soubi[n].explain, inputc);	break;
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
		case 1: strcpy(skill[n].name, inputc);			break;
		case 2: skill[n].MP = atoi(inputc);				break;
		case 3: skill[n].effect = atoi(inputc);			break;
		case 4: skill[n].status = atoi(inputc);			break;
		case 5: skill[n].magnification = atof(inputc);	break;
		case 6: skill[n].area = atoi(inputc);			break;
		case 7: strcpy(skill[n].explain, inputc);		break;
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
		case 0:		strcpy(character[n].name, inputc);					break;
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
}

int Data_c::GetItemFlag(int num)
{
	return 0;
}

int Data_c::GetSoubiFlag(int num)
{
	return 0;
}

int Data_c::GetSkillFlag(int num)
{
	return 0;
}

int Data_c::GetCharacterFlag(int num)
{
	return 0;
}

void Data_c::CalcItemFlag(int num, int vary)
{
}

void Data_c::CalcSoubiFlag(int num, int vary)
{
}

void Data_c::CalcSkillFlag(int num, int vary)
{
}

void Data_c::CalcCharacterFlag(int num, int vary)
{
}

int Data_c::GetItemPoint(int num, int sort)
{
	return 0;
}

string Data_c::GetItemText(int num, int sort)
{
	return string();
}

int Data_c::GetSoubiPoint(int num, int sort)
{
	return 0;
}

string Data_c::GetSoubiText(int num, int sort)
{
	return string();
}

int Data_c::GetSkillPoint(int num, int sort)
{
	return 0;
}

string Data_c::GetSkillText(int num, int sort)
{
	return string();
}

int Data_c::GetCharacterPoint(int num, int sort)
{
	return 0;
}

string Data_c::GetCharacterText(int num, int sort)
{
	return string();
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
