#pragma once

class Data_c;

class Option_c {
private:
	bool option_flag;

	int BGMVol, BGMLv, SEVol, SELv, BattleType;
	bool WindowMode;

	int Cursor;

	//Data_c* mData;
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
