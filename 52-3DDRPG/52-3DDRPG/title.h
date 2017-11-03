#pragma once

class Title_c {
private:
	int FontTitle;

	int NLGraph;
	int TitleGraph;
	
	int TempScreen;

	int Cursor = 300;
  int TitleBGM;
	bool first = true;
  bool end = false;
  bool flag = true;
	int bright = 0;
  int fade = 255;

	void nowLoading(void);

public:
	Title_c();
	~Title_c();

	bool TitleScreen(int*);
};