#include "define.h"

Title_c::Title_c() {
	SetUseASyncLoadFlag(TRUE);
  AddFontResourceExA("resource/font/game_over.ttf", FR_PRIVATE, NULL);
	FontTitleMain = CreateFontToHandle("Game Over", 24, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
  BGM = LoadSoundMem("resource/sounds/BGM/title.wav");
	NLGraph = LoadGraph("resource/NOW LOADING.png");
	TitleGraph = LoadGraph("resource/title.png");
	TempScreen = MakeScreen(640, 480, FALSE);
	SetUseASyncLoadFlag(FALSE);
}

Title_c::~Title_c() {
	DeleteFontToHandle(FontTitle);
	DeleteFontToHandle(FontTitleMain);
  DeleteSoundMem(BGM);
	DeleteGraph(NLGraph);
	DeleteGraph(TitleGraph);
	DeleteGraph(TempScreen);
}

bool Title_c::TitleScreen(int* Key) {
	if (first == true) {
		first = false;
    ChangeVolumeSoundMem(128, BGM);
    PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
	}

	if ((CheckHandleASyncLoad(FontTitle) != FALSE || CheckHandleASyncLoad(FontTitleMain) != FALSE || CheckHandleASyncLoad(TitleGraph) != FALSE)) {
		nowLoading();
		return false;
	}

	if (bright < 255) {
		bright = bright + 5;
		SetDrawBright(bright, bright, bright);
	}

	DrawExtendGraph(0, 0, 641, 481, TitleGraph, FALSE);
	DrawFormatStringToHandle(230, 360, GetColor(255, 255, 255), FontTitleMain, "PRESS ANY KEY");

	DrawFormatStringToHandle(200, Cursor, GetColor(255, 255, 255), FontTitleMain, "●");

	if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
		GMusic.ReserveSound(GMusic.CommonSE[GMusic.DECISION], DX_PLAYTYPE_BACK);
		GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
		do {
			bright = bright - 5;
			SetDrawBright(bright, bright, bright);
			ClearDrawScreen();
			DrawGraph(0, 0, TempScreen, FALSE);
			ScreenFlip();
		} while (bright > 0);
		SetDrawBright(255, 255, 255);
		bright = 0;
		GData.SceneRequest(1, 1);//シナリオ選択
		return true;
	}
	return false;
}

void Title_c::nowLoading(void) {
	DrawGraph(0, 0, NLGraph, FALSE);
}