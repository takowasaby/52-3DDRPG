#include "define.h"

GameOver::GameOver() :
	cursor(0),
	phase(0),
	bright(0)
{
	font[0] = 0;
	font[1] = 0;

	font[0] = CreateFontToHandle(-1, 25, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
	font[1] = CreateFontToHandle(-1, 100, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);

	bgm = LoadSoundMem("resource/sounds/BGM/scenario2/talk2.wav");
	SetDrawBright(bright, bright, bright);
}
GameOver::~GameOver()
{
	DeleteFontToHandle(font[0]);
	DeleteFontToHandle(font[1]);
	DeleteSoundMem(bgm);
}



bool GameOver::GameOverAll(int* mKey)
{
	DrawFormatStringToHandle(87, 120, GetColor(255, 255, 255), font[1], "GAME OVER");

	if (cursor == 0)	DrawFormatStringToHandle(200, 340, GetColor(255, 191, 0), font[0], "シナリオ選択へ");
	else				DrawFormatStringToHandle(200, 340, GetColor(255, 255, 255), font[0], "シナリオ選択へ");

	if (cursor == 1)	DrawFormatStringToHandle(200, 380, GetColor(255, 191, 0), font[0], "タイトルへ");
	else				DrawFormatStringToHandle(200, 380, GetColor(255, 255, 255), font[0], "タイトルへ");

	switch (phase) {
	case 0:
		if (bright < 255) {
			bright += 5;
			SetDrawBright(bright, bright, bright);
		}
		else {
			phase++;
		}
		break;
	case 1:
		if (mKey[KEY_INPUT_DOWN] == 1) {
			if (cursor == 0) cursor++;
		}
		else if (mKey[KEY_INPUT_UP] == 1) {
			if (cursor == 1) cursor--;
		}
		else if (mKey[KEY_INPUT_Z] == 1) {
			phase++;
		}
		break;
	case 2:
		if (bright > 0) {
			bright -= 5;
			SetDrawBright(bright, bright, bright);
		}
		else {
			GData.SceneRequest(1, 1 + cursor);
			SetDrawBright(255, 255, 255);
			return true;
		}
		break;
	}

	return false;
}
