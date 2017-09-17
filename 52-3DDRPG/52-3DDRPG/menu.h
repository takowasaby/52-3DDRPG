#pragma once

class Menu_c {
private:
	int depth;
	int mode = 0;
	int cursorY[5] = {20, -1, -1, -1, -1};
	//左から深度ごとのカーソルのY座標を格納する
	const int cursorX[5] = {10, 150, 150, 310, 310};
	//左から深度ごとのカーソルのX座標を格納する
	const int limitUP[5] = {20, 20, 20, 20, 20};
	const int limitDOWN[5] = {140, 140, 140, 140, 140};
	//カーソルが移動できる上限、下限

public:
	Menu_c();
	~Menu_c();

	void MenuAll();
	void DrawBack();
	void DrawLeft();
	void DrawRight();
	void DrawCursor();
	void CheckKey();
};

typedef enum {
	map,
	status,
	soubi,
	item,
	library,
	save,
	option,
}mode;
