#include "define.h"

Title_c::Title_c() {
	SetUseASyncLoadFlag(TRUE);
	FontTitle = CreateFontToHandle(NULL, 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT, 3);
	FontTitleMain = CreateFontToHandle(NULL, 24, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
	SE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
	SE[CANCEL] = LoadSoundMem("resource/sounds/SE/common/Cancel2.ogg");
	SE[CURSOR] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
	SE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
	NLGraph = LoadGraph("resource/NOW LOADING.png");
	TitleGraph = LoadGraph("resource/title.jpg");
	TempScreen = MakeScreen(640, 480, FALSE);
	SetUseASyncLoadFlag(FALSE);
}

Title_c::~Title_c() {
	DeleteFontToHandle(FontTitle);
	DeleteFontToHandle(FontTitleMain);
	DeleteSoundMem(SE[DECISION]);
	DeleteSoundMem(SE[CANCEL]);
	DeleteSoundMem(SE[CURSOR]);
	DeleteSoundMem(SE[BUZZER]);
	DeleteGraph(NLGraph);
	DeleteGraph(TitleGraph);
	DeleteGraph(TempScreen);
}

bool Title_c::TitleScreen(int* Key, int* title_scene) {
	if (first == true) {
		first = false;
		for (int i = 0; i < 4; i++) {
			ChangeVolumeSoundMem(128, SE[i]);
		}
		while (!ProcessMessage() && (CheckHandleASyncLoad(FontTitle) != FALSE || CheckHandleASyncLoad(FontTitleMain) != FALSE || CheckHandleASyncLoad(TitleGraph) != FALSE)) {
			nowLoading();
			Sleep(1);
		}
	}

	if (bright < 255) {
		bright = bright + 5;
		SetDrawBright(bright, bright, bright);
	}

	DrawGraph(0, 0, TitleGraph, FALSE);
	DrawFormatStringToHandle(150, 100, GetColor(255, 255, 255), FontTitle, "タイトル");
	DrawFormatStringToHandle(230, 300, GetColor(255, 255, 255), FontTitleMain, "ニューゲーム");
	DrawFormatStringToHandle(230, 330, GetColor(255, 255, 255), FontTitleMain, "コンティニュー");
	DrawFormatStringToHandle(230, 360, GetColor(255, 255, 255), FontTitleMain, "オプション");

	DrawFormatStringToHandle(200, Cursor, GetColor(255, 255, 255), FontTitleMain, "●");

	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 360) { Cursor = Cursor + 30; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 300) { Cursor = Cursor - 30; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
		if (Cursor == 300) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			*title_scene = 1; //ニューゲーム(シナリオ選択)
			return true;
		}
		else if (Cursor == 330) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			*title_scene = 3; //コンティニュー(セーブ･ロード)
			return true;
		}
		else {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
			do {
				bright = bright - 5;
				SetDrawBright(bright, bright, bright);
				ClearDrawScreen();
				DrawGraph(0, 0, TempScreen, FALSE);
				ScreenFlip();
			} while (bright > 0);
			SetDrawBright(255, 255, 255);
			*title_scene = 4; //オプション
			return true;
		}
	}
	return false;
}

void Title_c::nowLoading(void) {
	ClearDrawScreen();
	DrawGraph(0, 0, NLGraph, FALSE);
	ScreenFlip();
}