#include "define.h"

Dungeon_c::Dungeon_c() :
	mscenario(0),
	mstage(0)
{
	// data.GetScenario();
	// date.GetStage();
	for (int i = 0; i < 10; i++) {
		wallForDraw[i] = 0;
	}

	DataLoad(mscenario, mstage);
	GraphLoad(mscenario, mstage);
}

Dungeon_c::Dungeon_c(Data_c* data) :
	mData(data)
{
}

Dungeon_c::~Dungeon_c()
{
//	delete mData;
}

void Dungeon_c::KeyUpdata(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}

void Dungeon_c::DungeonAll()
{
	DataSet();
	BackDraw();
	WallDraw();
	UIDraw();
	MessageDraw();
	WaitKey();
}

void Dungeon_c::DataSet()
{
	mscenario = mData->GetScenario(); 
	dir = mData->GetDir();
	x = mData->GetDungeonX();
	y = mData->GetDungeonY();
}

void Dungeon_c::DataLoad(int scenario, int stage)
{
	sprintf_s(fname, "resource/%d_%d.csv", scenario, stage);

	mfp = FileRead_open(fname);
	if (mfp == NULL) {
		printfDx("read error\n");
		return;
	}
	for (int i = 0; i < 1; i++)//最初の2行読み飛ばす
		while (FileRead_getc(mfp) != '\n');

	mn = 0, mnum = 0;
	while (1) {
		for (int i = 0; i<MAP_SIZE_X * MAP_SIZE_Y; i++) {
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

	for (int i = 0; i < MAP_SIZE_X - 1; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
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
				break;
			case 3:
				if (wallData[i + 1][j].type == 1) {
					wallData[i][j].Ewall = 2;
					wallData[i + 1][j].Wwall = 2;
				}
				break;
			case 4:
				if (wallData[i + 1][j].type == 1) {
					wallData[i][j].Ewall = 3;
					wallData[i + 1][j].Wwall = 3;
				}
				break;
			}
		}
	}

	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y - 1; j++) {
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
				break;
			case 3:
				if (wallData[i][j + 1].type == 1) {
					wallData[i][j].Swall = 2;
					wallData[i][j + 1].Nwall = 2;
				}
				break;
			case 4:
				if (wallData[i][j + 1].type == 1) {
					wallData[i][j].Swall = 3;
					wallData[i][j + 1].Nwall = 3;
				}
				break;
			}
		}
	}

	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			mData->SetWallType(i, j, wallData[i][j].type);
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
	mData = d;
}

void Dungeon_c::BackDraw()
{
	DrawGraph(0, 0, back, FALSE);
}

void Dungeon_c::WallDrawSet()
{
	//壁の有無を取得
	for (int i = 0; i <= MAP_SIZE_X; i++) {
		for (int j = 0; j <= MAP_SIZE_Y; j++) {
			if (x == i && y == j) {
				switch (dir) {
				case 0: wallForDraw[0] = wallData[i][j].Wwall;
					wallForDraw[1] = wallData[i][j].Ewall;
					wallForDraw[2] = wallData[i][j].Nwall;
					wallForDraw[3] = wallData[i][j - 1].Wwall;
					wallForDraw[4] = wallData[i][j - 1].Ewall;
					wallForDraw[5] = wallData[i][j - 1].Nwall;
					if (i - 1 >= 0) {
						wallForDraw[6] = wallData[i - 1][j].Nwall;
						wallForDraw[8] = wallData[i - 1][j - 1].Nwall;
					}
					if (i + 1 <= MAP_SIZE_X - 1) {
						wallForDraw[7] = wallData[i + 1][j].Nwall;
						wallForDraw[9] = wallData[i + 1][j - 1].Nwall;
					}
					break;

				case 1: wallForDraw[0] = wallData[i][j].Nwall;
					wallForDraw[1] = wallData[i][j].Swall;
					wallForDraw[2] = wallData[i][j].Ewall;
					wallForDraw[3] = wallData[i + 1][j].Nwall;
					wallForDraw[4] = wallData[i + 1][j].Swall;
					wallForDraw[5] = wallData[i + 1][j].Ewall;
					if (j - 1 <= MAP_SIZE_Y - 1) {
						wallForDraw[6] = wallData[i][j - 1].Ewall;
						wallForDraw[8] = wallData[i + 1][j - 1].Ewall;
					}
					if (j + 1 >= 0) {
						wallForDraw[7] = wallData[i][j + 1].Ewall;
						wallForDraw[9] = wallData[i + 1][j + 1].Ewall;
					}
					break;

				case 2: wallForDraw[0] = wallData[i][j].Ewall;
					wallForDraw[1] = wallData[i][j].Wwall;
					wallForDraw[2] = wallData[i][j].Swall;
					wallForDraw[3] = wallData[i][j + 1].Ewall;
					wallForDraw[4] = wallData[i][j + 1].Wwall;
					wallForDraw[5] = wallData[i][j + 1].Swall;
					if (i + 1 <= MAP_SIZE_X - 1) {
						wallForDraw[6] = wallData[i + 1][j].Swall;
						wallForDraw[8] = wallData[i + 1][j + 1].Swall;
					}
					if (i - 1 >= 0) {
						wallForDraw[7] = wallData[i - 1][j].Swall;
						wallForDraw[9] = wallData[i - 1][j + 1].Swall;
					}
					break;

				case 3: wallForDraw[0] = wallData[i][j].Swall;
					wallForDraw[1] = wallData[i][j].Nwall;
					wallForDraw[2] = wallData[i][j].Wwall;
					wallForDraw[3] = wallData[i - 1][j].Swall;
					wallForDraw[4] = wallData[i - 1][j].Nwall;
					wallForDraw[5] = wallData[i - 1][j].Wwall;
					if (j + 1 >= 0) {
						wallForDraw[6] = wallData[i][j + 1].Wwall;
						wallForDraw[8] = wallData[i - 1][j + 1].Wwall;
					}
					if (j - 1 <= MAP_SIZE_Y) {
						wallForDraw[7] = wallData[i][j - 1].Wwall;
						wallForDraw[9] = wallData[i - 1][j - 1].Wwall;
					}
					break;
				}
			}
		}
	}
}

void Dungeon_c::WallDraw()
{
	for (int i = WALL_SIDE - 1; i >= 0; i--) {
		for (int j = 0; j < WALL_TYPE; j++) {
			if (wallForDraw[i] == j + 1) DrawGraph(0, 0, wall[mscenario][i][j], TRUE);
		}
	}
}

void Dungeon_c::UIDraw()
{
	int xLeft, yUp, size;
	DrawBox(487, 327, 633, 473, 0, TRUE);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			xLeft = 489 + j * 16;
			yUp = 329 + i * 16;
			size = 14;

			if (x - 4 + j >= 0 && y - 4 + i >= 0 && x - 4 + j < 25 && y - 4 + i < 25) {
				switch (wallData[x - 4 + j][y - 4 + i].type) {
				case 1: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 255, 255), TRUE);	break;
				case 2: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 0, 0), TRUE);		break;
				case 3: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 255, 0), TRUE);		break;
				case 4: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 0, 255), TRUE);		break;
				}
			}
		}
	}

	switch (dir) {
	case 0:	DrawTriangle(553, 407, 560, 393, 567, 407, GetColor(255, 255, 0), TRUE); break;
	case 1: DrawTriangle(553, 393, 567, 400, 553, 407, GetColor(255, 255, 0), TRUE); break;
	case 2: DrawTriangle(553, 393, 567, 393, 560, 407, GetColor(255, 255, 0), TRUE); break;
	case 3: DrawTriangle(567, 393, 553, 400, 567, 407, GetColor(255, 255, 0), TRUE); break;
	}
}

void Dungeon_c::MessageDraw()
{
}

void Dungeon_c::WaitKey()
{
	if (mKey[KEY_INPUT_DOWN] == 1) {
		switch (dir) {
		case 0:
			if (wallData[x][y].Swall == 0) y++;
			break;
		case 1:
			if (wallData[x][y].Wwall == 0) x--;
			break;
		case 2:
			if (wallData[x][y].Nwall == 0) y--;
			break;
		case 3:
			if (wallData[x][y].Ewall == 0) x++;
			break;
		}
		WallDrawSet();
	}
	else if (mKey[KEY_INPUT_UP] == 1) {
		switch (dir) {
		case 0:
			if (wallData[x][y].Nwall == 0) y--;
			break;
		case 1:
			if (wallData[x][y].Ewall == 0) x++;
			break;
		case 2:
			if (wallData[x][y].Swall == 0) y++;
			break;
		case 3:
			if (wallData[x][y].Wwall == 0) x--;
			break;
		}
		WallDrawSet();
	}
	else if (mKey[KEY_INPUT_RIGHT] == 1 && mKey[KEY_INPUT_LSHIFT] >= 1) {
		switch (dir) {
		case 0:
			if (wallData[x][y].Ewall == 0) x++;
			break;
		case 1:
			if (wallData[x][y].Swall == 0) y++;
			break;
		case 2:
			if (wallData[x][y].Wwall == 0) x--;
			break;
		case 3:
			if (wallData[x][y].Nwall == 0) y--;
			break;
		}
		WallDrawSet();
	}
	else if (mKey[KEY_INPUT_LEFT] == 1 && mKey[KEY_INPUT_LSHIFT] >= 1) {
		switch (dir) {
		case 0:
			if (wallData[x][y].Wwall == 0) x--;
			break;
		case 1:
			if (wallData[x][y].Nwall == 0) y--;
			break;
		case 2:
			if (wallData[x][y].Ewall == 0) x++;
			break;
		case 3:
			if (wallData[x][y].Swall == 0) y++;
			break;
		}
		WallDrawSet();
	}
	else if (mKey[KEY_INPUT_LEFT] == 1) {
		if (dir == 0) dir = 4;
		dir--;
		WallDrawSet();
	}
	else if (mKey[KEY_INPUT_RIGHT] == 1) {
		if (dir == 3) dir = -1;
		dir++;
		WallDrawSet();
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		switch (dir) {
		case 0:
			if (wallData[x][y].Nwall == 2) printfDx("open!");
			break;
		case 1:
			if (wallData[x][y].Ewall == 2) printfDx("open!");
			break;
		case 2:
			if (wallData[x][y].Swall == 2) printfDx("open!");
			break;
		case 3:
			if (wallData[x][y].Wwall == 2) printfDx("open!");
			break;
		}
	}
	else if (mKey[KEY_INPUT_C] == 1) {
	}

	mData->SetDungeonX(x);
	mData->SetDungeonY(y);
	mData->SetDir(dir);
}
