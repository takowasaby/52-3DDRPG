#include "define.h"

Option_c::Option_c()
{
	Cursor = 50;
}

Option_c::~Option_c()
{
}

void Option_c::Main()
{
	void BackDraw();
	void ItemDraw();
	void CursorDraw();
}

void Option_c::BackDraw()
{
}

void Option_c::ItemDraw()
{
	//仮置き項目
	DrawFormatString(240, 20, GetColor(255, 255, 255), "OPTION");

	DrawFormatString(40, 50, GetColor(255, 255, 255), "BGM");
	DrawFormatString(120, 50, GetColor(255, 255, 255), "%d",BGMVol);

	DrawFormatString(40, 90, GetColor(255, 255, 255), "SE");
	DrawFormatString(120, 90, GetColor(255, 255, 255), "%d", SEVol);

	DrawFormatString(40, 130, GetColor(255, 255, 255), "BattleMode");
	DrawFormatString(120, 130, GetColor(255, 255, 255), "%d", BattleType);

	DrawFormatString(40, 170, GetColor(255, 255, 255), "WindowMode");
	DrawFormatString(120, 50, GetColor(255, 255, 255), "WINDOW");

	DrawFormatString(40, 210, GetColor(255, 255, 255), "Back");
}

void Option_c::CursorDraw()
{
	DrawFormatString(40, Cursor, GetColor(255, 255, 255), "->");

	//UpdateKey();
	if (Key[KEY_INPUT_DOWN] == 1) {
			if(Cursor != 210) Cursor += 40;
	}
	if (Key[KEY_INPUT_UP] == 1) {
			if(Cursor != 50) Cursor -= 40;
	}

	if (Key[KEY_INPUT_RIGHT] == 1) {
		switch (Cursor) {
		case 50:
			if (BGMLv != 5) {
				BGMLv += 1;
			}
			break;
		case 90:
			if (SELv != 5) {
				SELv += 1;
			}
			break;
		case 130:
			if (BattleType != 3) {
				BattleType += 1;
			}
			break;
		case 170:
			if (WindowMode != false) {
				WindowMode = false;
			}
			break;
		}
	}
	if (Key[KEY_INPUT_LEFT]==1) {
		switch (Cursor) {
		case 50:
			if (BGMLv != 0) {
				BGMLv -= 1;
			}
			break;
		case 90:
			if (SELv != 0) {
				SELv -= 1;
			}
			break;
		case 130:
			if (BattleType != 0) {
				BattleType -= 1;
			}
			break;
		case 170:
			if (WindowMode != true) {
				WindowMode = true;
			}
			break;
		}
	}

	if (Key[KEY_INPUT_Z] == 1 && Cursor == 210) {
		//mode = game (control.cpp)
	}

	BGMVol = 255 * BGMLv / 5;
	SEVol = 255 * SELv / 5;
}

int Option_c::GetBGMvol()
{
	return BGMVol;
}

int Option_c::GetSEVol()
{
	return SEVol;
}

int Option_c::GetBattleType()
{
	return BattleType;
}

bool Option_c::GetWindowMode()
{
	return WindowMode;
}
