#include "define.h"

Option_c::Option_c() :
	Cursor(50),
	BGMLv(3),
	SELv(3),
	BattleType(2),
	WindowMode(true)
{
	//mData = new Data_c;
}

Option_c::~Option_c()
{
	//delete mData;
}

bool Option_c::Main(int* Key)
{

	BackDraw();
	ItemDraw();

	return CursorDraw(Key);
}

void Option_c::BackDraw()
{
}

void Option_c::ItemDraw()
{
	DrawFormatString(240, 20, GetColor(255, 255, 255), "OPTION");

	DrawFormatString(40, 50, GetColor(255, 255, 255), "BGM");
	DrawFormatString(120, 50, GetColor(255, 255, 255), "%d", BGMLv);
	DrawBox(140, 45, 140 + 100 * double(BGMLv) / 5, 55, GetColor(255, 255, 0), true);

	DrawFormatString(40, 90, GetColor(255, 255, 255), "SE");
	DrawFormatString(120, 90, GetColor(255, 255, 255), "%d", SELv);
	DrawBox(140, 85, 140 + 100 * double(SELv) / 5, 95, GetColor(255, 255, 0), true);

	DrawFormatString(40, 130, GetColor(255, 255, 255), "BattleMode");
	DrawFormatString(160, 130, GetColor(255, 255, 255), "%d", BattleType);
	switch (BattleType) {
	case 0:
		DrawFormatString(200, 130, GetColor(255, 255, 255), "NONE");
		break;
	case 1:
		DrawFormatString(200, 130, GetColor(255, 255, 255), "EASY");
		break;
	case 2:
		DrawFormatString(200, 130, GetColor(255, 255, 255), "NORMAL");
		break;
	case 3:
		DrawFormatString(200, 130, GetColor(255, 255, 255), "HARD");
		break;
	}

	DrawFormatString(40, 170, GetColor(255, 255, 255), "WindowMode");
	if (WindowMode == false) {
		DrawFormatString(170, 170, GetColor(255, 255, 255), "WINDOW");
	}
	else {
		DrawFormatString(170, 170, GetColor(255, 255, 255), "FULL");
	}

	DrawFormatString(40, 210, GetColor(255, 255, 255), "Back");
}


bool Option_c::CursorDraw(int* Key)
{
	DrawFormatString(10, Cursor, GetColor(255, 255, 255), "->");


	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 210) Cursor += 40;
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 50) Cursor -= 40;
	}

	else if (Key[KEY_INPUT_RIGHT] == 1) {
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
	else if (Key[KEY_INPUT_LEFT] == 1) {
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

	BGMVol = 255 * BGMLv / 5;	//mData->BGMVol =
	SEVol = 255 * SELv / 5;		//mData->SEVol =

	// Back or CANCEL_KEY
	if ((Key[KEY_INPUT_Z] == 1 && Cursor == 210) || Key[KEY_INPUT_X] == 1) {
		//if player jump from "title"
		if (option_flag == false)
		{
			//mode = title
			//title_scene = start

			return true;
		}

		//if player jump from "menu"
		else
		{
			//mode = game
			//game_scene = menu

			return true;
		}
	}
	return false;
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

void Option_c::SetOptionFlag(bool* flag)
{
	option_flag = flag;
}
