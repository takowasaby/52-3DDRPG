<<<<<<< HEAD
#pragma once

class option_c {
private:
	int BGMVol, SEVol, BattleType, KeyConfig;
public:
	bool WinMode;
	void Ini();
	void main();
	void backdraw();
	void itemdraw();
	void configdraw();
	void cursol();
	void Fin();
};
=======
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

	bool Main(int* Key, int* mode, int* title_scene, int* game_scene);

	void BackDraw();
	void ItemDraw();

	bool CursorDraw(int* Key, int* mode, int* title_scene, int* game_scene);

	int GetBGMvol();
	int GetSEVol();
	int GetBattleType();
	bool GetWindowMode();

	void SetOptionFlag(bool* flag);
};
>>>>>>> 4ecee024daaa0dbf9e67bad410c6577604f6d556
