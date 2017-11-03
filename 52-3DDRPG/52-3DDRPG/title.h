#pragma once

class Title_c {
private:
	int FontTitle;

	int NLGraph;
	int TitleGraph;
	
	int TempScreen;

	int Cursor = 300;
  int BGM;
	bool first = true;
	int bright = 0;

	void nowLoading(void);

public:
	Title_c();
	~Title_c();

	bool TitleScreen(int*);
};