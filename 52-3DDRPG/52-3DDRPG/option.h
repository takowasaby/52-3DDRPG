#pragma once

class Control_c;

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

	bool Main(int* Key);
	
	void BackDraw();
	void ItemDraw();
	
	bool CursorDraw(int* Key);

	int GetBGMvol();
	int GetSEVol();
	int GetBattleType();
	bool GetWindowMode();

	void SetOptionFlag(bool* flag);
};
