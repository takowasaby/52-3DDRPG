#include "define.h"

Dungeon_c::Dungeon_c()
{
}

Dungeon_c::~Dungeon_c()
{
}

void Dungeon_c::DungeonAll()
{
	mscenario = data.GetScenario();
	mstage = 0; //date.GetStage();
	DataLoad(mscenario, mstage);
	WallSet();
	GraphLoad(mscenario, mstage);
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
	for (i = 0; i < 1; i++)//�ŏ���2�s�ǂݔ�΂�
		while (FileRead_getc(mfp) != '\n');

	mn = 0, mnum = 0;
	while (1) {
		for (i = 0; i<MAP_SIZE_X * MAP_SIZE_Y; i++) {
			inputc[i] = input[i] = FileRead_getc(mfp);//1�����擾����
			if (inputc[i] == '/') {//�X���b�V���������
				while (FileRead_getc(mfp) != '\n');//���s�܂Ń��[�v
				i = -1;//�J�E���^���ŏ��ɖ߂���
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//�J���}�����s�Ȃ�
				inputc[i] = '\0';//�����܂ł𕶎���Ƃ�
				break;
			}
			if (input[i] == EOF) {//�t�@�C���̏I���Ȃ�
				goto EXFILE;//�I��
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

}

void Dungeon_c::BackDraw()
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
