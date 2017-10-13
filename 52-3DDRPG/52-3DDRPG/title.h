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
	
	int TempScreen;

	int Cursor = 300;
	int SE[4];
	bool first = true;
	int bright = 0;

	void nowLoading(void);

public:
	Title_c();
	~Title_c();

	bool TitleScreen(int*, int*);
};