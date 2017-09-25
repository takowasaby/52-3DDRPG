#pragma once

class Option_c {
private:
	bool option_flag;

	int BGMVol,BGMLv , SEVol, SELv ,BattleType;
	bool WindowMode;

	int Cursor;

	Control_c* control;
public:
	Option_c();
	~Option_c();

	void Main();
	void BackDraw();
	void ItemDraw();
	void CursorDraw();

	int GetBGMvol();
	int GetSEVol();
	int GetBattleType();
	bool GetWindowMode();

	void SetOptionFlag(bool flag);
};
