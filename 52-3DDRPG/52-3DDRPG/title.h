#pragma once

class Title_c {
private:
	int FontTitle;
	int FontTitleMain;

	const int DECISION = 0;
	const int CANCEL = 1;
	const int CURSOR = 2;
	const int BUZZER = 3;

	int NLGraph;
	int TitleGraph;

	int Cursor = 300;
	char Key[256];
	int SE[4];
	bool first = false;

	void nowLoading(void);

public:
	Title_c();
	~Title_c();

	void TitleScreen(int*);
};