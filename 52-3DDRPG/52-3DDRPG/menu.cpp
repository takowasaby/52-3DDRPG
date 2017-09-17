#include "define.h"

Menu_c::Menu_c()
{
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
	DrawFormatString(20, 200, GetColor(255, 255, 255), "シナリオ");
}

void Menu_c::DrawRight()
{
	switch (mode) {
	case map:
		break;
	case status:
		break;
	case soubi:
		break;
	case item:
		break;
	case library:
		break;
	case save:
		break;
	case option:
		break;
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
	UpdateKey();
	if (Key[KEY_INPUT_DOWN] == 1) {
		switch(depth){
		case 0: 
			if (cursorY[0] != limitDOWN[0]) {
				cursorY[0] += 20;
			}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		}
	}	else if (Key[KEY_INPUT_UP] == 1) {
		switch (depth) {
		case 0:
			if (cursorY[0] != limitUP[0]) {
				cursorY[0] -= 20;
			}
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		}
	}	else if (Key[KEY_INPUT_Z] == 1) {
		if (depth != 4) depth++;
	}	else if (Key[KEY_INPUT_X] == 1) {
		if (depth != 0) depth--;
	}
}
