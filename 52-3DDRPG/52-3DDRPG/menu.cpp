#include "define.h"

Menu_c::Menu_c()
{
}

Menu_c::Menu_c(Data_c * data, int * Key, int * mode, int * event_scene, int * title_scene, int * game_scene) :
	mData(data),
	mMode(mode),
	mEvent_scene(event_scene),
	mTitle_scene(title_scene),
	mGame_scene(game_scene)
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}

Menu_c::~Menu_c()
{
}

void Menu_c::MenuAll()
{
	DrawLeft();
	DrawRight();
	DrawCursor();
	CheckKey();
}

void Menu_c::DrawBack()
{
}

void Menu_c::DrawLeft()
{
	DrawFormatString(20, 20, GetColor(255, 255, 255), "マップ");
	DrawFormatString(20, 40, GetColor(255, 255, 255), "ステータス");
	DrawFormatString(20, 60, GetColor(255, 255, 255), "装備");
	DrawFormatString(20, 80, GetColor(255, 255, 255), "アイテム");
	DrawFormatString(20, 100, GetColor(255, 255, 255), "ライブラリ");
	DrawFormatString(20, 120, GetColor(255, 255, 255), "セーブ");
	DrawFormatString(20, 140, GetColor(255, 255, 255), "オプション");
	DrawFormatString(20, 160, GetColor(255, 255, 255), "プレイ時間");
	DrawFormatString(20, 200, GetColor(255, 255, 255), "現在のシナリオ");
}

void Menu_c::DrawRight()
{
	int count = 0;

	switch (depth) {
	case 0:
		switch (mode) {
		case map:
			mscenario = mData->GetScenario();
			mdir = mData->GetDir();
			mx = mData->GetDungeonX();
			my = mData->GetDungeonY();

			int xLeft, yUp, size;
			DrawBox(487, 327, 633, 473, 0, TRUE);

			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 25; j++) {
					xLeft =  + j * 16;
					yUp =  + i * 16;
					size = 14;

					switch (wallData[mx - 4 + j][my - 4 + i].type) {
					case 1: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 255, 255), TRUE);	break;
					case 2: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(255, 0, 0), TRUE);		break;
					case 3: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 255, 0), TRUE);		break;
					case 4: DrawBox(xLeft, yUp, xLeft + size, yUp + size, GetColor(0, 0, 255), TRUE);		break;
					}
				}
			}

			switch (mdir) {
			case 0:	DrawTriangle(553, 407, 560, 393, 567, 407, GetColor(255, 255, 0), TRUE); break;
			case 1: DrawTriangle(553, 393, 567, 400, 553, 407, GetColor(255, 255, 0), TRUE); break;
			case 2: DrawTriangle(553, 393, 567, 393, 560, 407, GetColor(255, 255, 0), TRUE); break;
			case 3: DrawTriangle(567, 393, 553, 400, 567, 407, GetColor(255, 255, 0), TRUE); break;
			}
			break;
		case status:
			break;
		case soubi:
			break;
		case item:
			DrawFormatString(320, 20, GetColor(255, 255, 255), "消耗品");
			DrawFormatString(480, 20, GetColor(255, 255, 255), "だいじなもの");
			break;
		case library:
			break;
		case save:
			break;
		case option:
			break;
		}
		break;
	case 1:
		switch (mode) {
		case map:
			break;
		case status:
			break;
		case soubi:
			break;
		case item:
			DrawFormatString(320, 20, GetColor(255, 255, 255), "消耗品");
			DrawFormatString(480, 20, GetColor(255, 255, 255), "だいじなもの");
			break;
		case library:
			break;
		case save:
			break;
		case option:
			break;
		}
		break;
	case 2:
		switch (mode) {
		case map:
			break;
		case status:
			break;
		case soubi:
			break;
		case item:
			DrawFormatString(320, 20, GetColor(255, 255, 255), "消耗品");
			DrawFormatString(480, 20, GetColor(255, 255, 255), "だいじなもの");

			for (int i = 0; i < ITEM_SIZE; i++) {
				if (mData->GetItemFlag(i) >= 1) {
					if (count < 40) {
						DrawFormatString(((count / 20) + 1) * 160, ((count % 20) + 1) * 20 + 20, GetColor(255, 255, 255), "%s" ,mData->GetItemText(i, 0));
						count++;
					}
				}
			}
			break;
		case library:
			break;
		case save:
			break;
		case option:
			break;
		}
		break;
	case 3:
	case 4:
	}
}

void Menu_c::DrawCursor()
{
	for (int i = 0; i < 5; i++) {
		if (cursorY[i] != -1) {
			DrawTriangle(cursorX[i] - 5, cursorY[i] - 3, cursorX[i] + 5, cursorY[i], cursorX[i] - 5, cursorY[i] + 3, GetColor(255, 255, 255), TRUE);
		}
	}
}

void Menu_c::CheckKey()
{
	if (mKey[KEY_INPUT_DOWN] == 1) {
		switch (depth) {
		case 0:
			if (cursorY[0] != limitDOWN[0]) {
				cursorY[0] += 20;
				mode++;
			}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		}
	}
	else if (mKey[KEY_INPUT_UP] == 1) {
		switch (depth) {
		case 0:
			if (cursorY[0] != limitUP[0]) {
				cursorY[0] -= 20;
				mode--;
			}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		}
	}
	else if (mKey[KEY_INPUT_Z] == 1) {
		if (depth != 4) depth++;
	}
	else if (mKey[KEY_INPUT_X] == 1) {
		if (depth != 0) depth--;
	}
}
