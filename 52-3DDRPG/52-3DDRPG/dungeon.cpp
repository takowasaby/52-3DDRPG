#include "dungeon.h"

void Dungeon_c::DataLoad(int scenario, int stage)
{
	sprintf_s(fname, "%d_%d", scenario, stage);

	mfp = FileRead_open(fname);
	if (mfp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (i = 0; i < 1; i++)//最初の2行読み飛ばす
		while (FileRead_getc(mfp) != '\n');

	mn = 0, mnum = 0;
	while (1) {
		for (i = 0; i<ROOM_MAX_X * ROOM_MAX_Y; i++) {
			inputc[i] = input[i] = FileRead_getc(mfp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(mfp) != '\n');//改行までループ
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
		wallData[mnum][mn % ROOM_MAX_X].type = atoi(inputc);
		mnum++;
		if (mnum == ROOM_MAX_X) {
			mnum = 0;
			mn++;
		}
	}
EXFILE:
	FileRead_close(mfp);
}

void Dungeon_c::WallSet()
{
	for (i = 0; i < ROOM_MAX_X - 1; i++) {
		for (j = 0; j < ROOM_MAX_Y; j++) {
			switch (wallData[i][j].type) {
			case 0: 
				switch (wallData[i + 1][j].type) {
				case 0: 
					wallData[i][j].Ewall = 0;
					wallData[i + 1][j].Wwall = 0;
					break;
				case 1: break;
				case 2: break;
				case 3: break;
				case 4: break;
				}
				break;
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			}
		}
	}
}
