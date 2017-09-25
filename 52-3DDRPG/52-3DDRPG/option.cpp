#include "define.h"

Option_c::Option_c()
{
	Cursor = 50;

	control = new Control_c;
}

Option_c::~Option_c()
{
	delete &control;
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
	DrawBox(140,45,140+100*BGMVol/5,55,GetColor(255,255,0),true);

	DrawFormatString(40, 90, GetColor(255, 255, 255), "SE");
	DrawFormatString(120, 90, GetColor(255, 255, 255), "%d", SEVol);
	DrawBox(140, 85, 140 + 100 * SEVol / 5, 95, GetColor(255, 255, 0), true);

	DrawFormatString(40, 130, GetColor(255, 255, 255), "BattleMode");
	DrawFormatString(120, 130, GetColor(255, 255, 255), "%d", BattleType);
	switch (BattleType) {
	case 0:
		DrawFormatString(140, 130, GetColor(255, 255, 255), "NONE");
	case 1:
		DrawFormatString(140, 130, GetColor(255, 255, 255), "EASY");
	case 2:
		DrawFormatString(140, 130, GetColor(255, 255, 255), "NORMAL");
	case 3:
		DrawFormatString(140, 130, GetColor(255, 255, 255), "HARD");
	}

	DrawFormatString(40, 170, GetColor(255, 255, 255), "WindowMode");
	if (WindowMode == false) {
		DrawFormatString(120, 50, GetColor(255, 255, 255), "WINDOW");
	}
	else {
		DrawFormatString(120, 50, GetColor(255, 255, 255), "FULL");
	}

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

	// Back or CANCEL_KEY
	if ((Key[KEY_INPUT_Z] == 1 && Cursor == 210) || Key[KEY_INPUT_X] == 1) {
		//if player jump from "title"
		if(option_flag == false)
		{
			control->SetMode(1);	//mode = title
			control->SetTitle(2);	//title_scene = start
		}

		//if player jump from "menu"
		else 
		{
			control->SetMode(2);	//mode = game
			control->SetGame(3);	//game_scene = menu
		}
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
