#pragma once

const int MENU_MAP_LEFT = 199;
const int MENU_MAP_UP = 59;

class Data_c;

class Menu_c {
private:
	int depth;
	int mode = 0;
	int mscenario, mdir, mx, my;
	int mwallType[MAP_SIZE_X][MAP_SIZE_Y];

	Data_c* mData;
	int mKey[256];
	int* mMode;
	int* mEvent_scene;
	int* mTitle_scene;
	int* mGame_scene;

	int cursorY[5] = { 20, -1, -1, -1, -1 };
	const int cursorX[5] = { 10, 150, 150, 310, 310 };
	const int limitUP[5] = { 20, 20, 20, 20, 20 };
	const int limitDOWN[5] = { 140, 140, 140, 140, 140 };

	typedef enum {
		map,
		status,
		soubi,
		item,
		library,
		save,
		option,
	}Mode;

public:
	Menu_c();
	Menu_c(Data_c* data, int* mode, int* event_scene, int* title_scene, int* game_scene);
	~Menu_c();

	void KeyUpdata(int Key[256]);
	void MenuAll();
	void DrawBack();
	void DrawLeft();
	void DrawRight();
	void DrawCursor();
	void CheckKey();
};