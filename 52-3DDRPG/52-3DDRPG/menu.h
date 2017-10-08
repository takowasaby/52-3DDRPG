#pragma once

class Menu_c {
private:
	int depth;

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
