#pragma once

class GameOver {
private:
	int bright;
	int cursor;
	int phase;

	int font[2];
	int bgm;

public:
	GameOver();
	~GameOver();

	bool GameOverAll(int* mKey);
};