#pragma once

class GameOver {
private:
	const int DECISION = 0;
	const int CANCEL = 1;
	const int CURSOR = 2;
	const int BUZZER = 3;

	int bright;
	int cursor;
	int phase;

	int font[2];
	int SE[4];
	int bgm;

public:
	GameOver();
	~GameOver();

	bool GameOverAll(int* mKey);
};