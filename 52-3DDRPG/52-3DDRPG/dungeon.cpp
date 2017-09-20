#include "define.h"

Dungeon_c::Dungeon_c() :
	mscenario(0),
	mstage(0)
{
	// data.GetScenario();
	//date.GetStage();

	DataLoad(mscenario, mstage);
	GraphLoad(mscenario, mstage);
}

Dungeon_c::Dungeon_c(Data_c *d) :
	data(d)
{

}

Dungeon_c::~Dungeon_c()
{
}

void Dungeon_c::DungeonAll()
{
	BackDraw();
	WallDraw();
	UIDraw();
	MessageDraw();
	WaitKey();
}

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
		for (i = 0; i<MAP_SIZE_X * MAP_SIZE_Y; i++) {
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
		wallData[mnum][mn % MAP_SIZE_X].type = atoi(inputc);
		mnum++;
		if (mnum == MAP_SIZE_X) {
			mnum = 0;
			mn++;
		}
	}
EXFILE:
	FileRead_close(mfp);

	for (i = 0; i < MAP_SIZE_X - 1; i++) {
		for (j = 0; j < MAP_SIZE_Y; j++) {
			switch (wallData[i][j].type) {
			case 1:
				switch (wallData[i + 1][j].type) {
				case 1:
					wallData[i][j].Ewall = 0;
					wallData[i + 1][j].Wwall = 0;
					break;
				case 3:
					wallData[i][j].Ewall = 2;
					wallData[i + 1][j].Wwall = 2;
					break;
				case 4:
					wallData[i][j].Ewall = 3;
					wallData[i + 1][j].Wwall = 3;
					break;
				}
			case 3:
				if (wallData[i + 1][j].type == 1) {
					wallData[i][j].Ewall = 2;
					wallData[i + 1][j].Wwall = 2;
				}
			case 4:
				if (wallData[i + 1][j].type == 1) {
					wallData[i][j].Ewall = 3;
					wallData[i + 1][j].Wwall = 3;
				}
			}
		}
	}

	for (i = 0; i < MAP_SIZE_X; i++) {
		for (j = 0; j < MAP_SIZE_Y - 1; j++) {
			switch (wallData[i][j].type) {
			case 1:
				switch (wallData[i][j + 1].type) {
				case 1:
					wallData[i][j].Swall = 0;
					wallData[i][j + 1].Nwall = 0;
					break;
				case 3:
					wallData[i][j].Swall = 2;
					wallData[i][j + 1].Nwall = 2;
					break;
				case 4:
					wallData[i][j].Swall = 3;
					wallData[i][j + 1].Nwall = 3;
					break;
				}
			case 3:
				if (wallData[i][j + 1].type == 1) {
					wallData[i][j].Swall = 2;
					wallData[i][j + 1].Nwall = 2;
				}
			case 4:
				if (wallData[i][j + 1].type == 1) {
					wallData[i][j].Swall = 3;
					wallData[i][j + 1].Nwall = 3;
				}
			}
		}
	}
}

void Dungeon_c::GraphLoad(int scenario, int stage)
{
	sprintf_s(gname, "resource/%d.png", scenario);
	back = LoadGraph(gname);

	for (int i = 0; i < WALL_SIDE; i++) {
		for (int j = 0; j < WALL_TYPE; j++) {
			sprintf_s(gname, "resource/%d_%d_%d.png", scenario, i, j);
			wall[scenario][i][j] = LoadGraph(gname);
		}
	}
}

void Dungeon_c::SetData(Data_c *d)
{
	data = d;
}

void Dungeon_c::BackDraw()
{
	DrawGraph(0, 0, back, FALSE);
}

void Dungeon_c::WallDraw()
{

}

void Dungeon_c::UIDraw()
{
}

void Dungeon_c::MessageDraw()
{
}

void Dungeon_c::WaitKey()
{
}
