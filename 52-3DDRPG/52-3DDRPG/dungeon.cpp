#include "dungeon.h"

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
		for (i = 0; i<ROOM_MAX_X * ROOM_MAX_Y; i++) {
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
