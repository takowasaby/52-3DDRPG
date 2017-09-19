#pragma once

class Option_c {
private:
	int BGMVol,BGMLv , SEVol, SELv ,BattleType;
	bool WindowMode;

	int Cursor;
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
};
