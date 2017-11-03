#pragma once

class TextBox;

const int MENU_MAP_UP = 65;
const int MENU_MAP_LEFT = 195;
const int MENU_MAP_SIZE = 12;

class Menu_c {
private:
	int depth;
	int mode, mscenario;
	int mdir, mx, my;
	int mwallType[MAP_SIZE_X][MAP_SIZE_Y] = {};
	int meventFlag[SCENARIO_SIZE][EVENT_SIZE] = {};
	int drawCount;
	unsigned int colorW, colorY;
	int xLeft, yUp;

	int windowH, windowW, menuScreen;

	int row, stringX, stringY;

	int itemType, soubiType;

	int charaNum[CHARACTER_SIZE];
	int itemNum[ITEM_SIZE];
	int soubiNum[SOUBI_SIZE];
	int skillNum[SKILL_SIZE];

	int chooseChara, chooseItem, chooseSoubi, chooseSkill;

	int YN, targetChara;

	int mKey[256];

	int cursorY = 20;
	const int cursorX = 10;
	const int limitUP = 20;
	const int limitDOWN = 140;

	typedef enum {
		map,
		status,
		soubi,
		item,
		scenario,
		save,
		option,
	}Mode;

	TextBox *textBox;

public:
	Menu_c();
	~Menu_c();

	void MenuAll();
	void DrawBack();
	void DrawLeft();
	void DrawRight();
	void DrawCursor();
	void CheckKey();

	void KeyUpdate(int Key[256]);
	void DrawGoal();

	void UseItem(int num, int target);
	void WearSoubi(int num, int target, int part);
	bool UseSkill(int num, int target, int user);

	void LoadWindow();
};
