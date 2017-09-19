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
	DrawFormatString(40, 90, GetColor(255, 255, 255), "SE");
	DrawFormatString(40, 130, GetColor(255, 255, 255), "BattleMode");
	DrawFormatString(40, 170, GetColor(255, 255, 255), "WindowMode");
	DrawFormatString(40, 210, GetColor(255, 255, 255), "Back To Title");
}

void Option_c::CursorDraw()
{
	UpdateKey();
	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 210) {
			Cursor = Cursor + 40;
		}
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 50) {
			Cursor = Cursor - 40; 
		}
	}
}