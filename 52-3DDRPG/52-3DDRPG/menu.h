#pragma once

class Menu_c {
private:
	int depth;
	int mode = 0;
	int cursorY[5] = {20, -1, -1, -1, -1};
	//������[�x���Ƃ̃J�[�\����Y���W���i�[����
	const int cursorX[5] = {10, 150, 150, 310, 310};
	//������[�x���Ƃ̃J�[�\����X���W���i�[����
	const int limitUP[5] = {20, 20, 20, 20, 20};
	const int limitDOWN[5] = {140, 140, 140, 140, 140};
	//�J�[�\�����ړ��ł������A����

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
