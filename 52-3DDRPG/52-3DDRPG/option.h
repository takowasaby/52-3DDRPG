#pragma once

class Option_c {
private:
	int BGMVol, SEVol, BattleType, KeyConfig;
	int Cursor;
public:
	Option_c();
	~Option_c();

	void Main();
	void BackDraw();
	void ItemDraw();
	void CursorDraw();
};
