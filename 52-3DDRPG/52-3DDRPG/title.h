#pragma once

class Title_c {
private:
	int FontTitle;
	int FontTitleMain;

	int SE[4];
	const int DECISION = 0;
	const int CANCEL = 1;
	const int CURSOR = 2;
	const int BUZZER = 3;

	int TitleGraph;

	int Cursor = 300;

public:
	Title_c();
	~Title_c();

	void TitleScreen();
};