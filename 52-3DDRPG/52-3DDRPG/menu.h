#pragma once

class Menu_c {
private:
	int depth;
<<<<<<< HEAD
=======
	int mode = 0;
	int mscenario, mdir, mx, my;
	int mwallType[MAP_SIZE_X][MAP_SIZE_Y];
	int meventFlag[SCENARIO_SIZE][EVENT_SIZE];
	int drawCount;

	int itemType;
	int soubiType;

	int charaNum[CHARACTER_SIZE];
	int itemNum[ITEM_SIZE];
	int soubiNum[SOUBI_SIZE];
	int skillNum[SKILL_SIZE];

	int chooseChara;
	int chooseItem;
	int chooseSoubi;
	int chooseSkill;

	int YN;

	int targetChara;

	int mKey[256];
	int* mMode;
	int* mEvent_scene;
	int* mTitle_scene;
	int* mGame_scene;

	int cursorY = 20;
	const int cursorX = 10;
	const int limitUP = 20;
	const int limitDOWN = 140;

	typedef enum {
		map,
		status,
		soubi,
		item,
		library,
		save,
		option,
	}Mode;
>>>>>>> data

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
