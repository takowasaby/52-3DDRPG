#include "define.h"

Title_c::Title_c() {
	SetUseASyncLoadFlag(TRUE);
	FontTitle = CreateFontToHandle(NULL, 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT, 3);
	FontTitleMain = CreateFontToHandle(NULL, 24, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
	SE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
	SE[CANCEL] = LoadSoundMem("resource/sounds/SE/common/Cancel2.ogg");
	SE[CURSOR] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
	SE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
	TitleGraph = LoadGraph("resource/title.jpg");
	SetUseASyncLoadFlag(FALSE);
}

Title_c::~Title_c() {
	DeleteFontToHandle(FontTitle);
	DeleteFontToHandle(FontTitleMain);
	DeleteSoundMem(SE[DECISION]);
	DeleteSoundMem(SE[CANCEL]);
	DeleteSoundMem(SE[CURSOR]);
	DeleteSoundMem(SE[BUZZER]);
	DeleteGraph(TitleGraph);
}

bool Title_c::TitleScreen(int* Key) {
	nowLoading();
	for (int i = 0; i < 4; i++) {
		ChangeVolumeSoundMem(128, SE[i]);
	}
	while (CheckHandleASyncLoad(FontTitle) != FALSE || CheckHandleASyncLoad(FontTitleMain) != FALSE || CheckHandleASyncLoad(TitleGraph) != FALSE) {
		ProcessMessage();
		Sleep(1);
	}

	DrawGraph(0, 0, TitleGraph, FALSE);
	DrawFormatStringToHandle(150, 100, GetColor(255, 255, 255), FontTitle, "�^�C�g��");
	DrawFormatStringToHandle(230, 300, GetColor(255, 255, 255), FontTitleMain, "�j���[�Q�[��");
	DrawFormatStringToHandle(230, 330, GetColor(255, 255, 255), FontTitleMain, "�R���e�B�j���[");
	DrawFormatStringToHandle(230, 360, GetColor(255, 255, 255), FontTitleMain, "�I�v�V����");

	DrawFormatStringToHandle(200, Cursor, GetColor(255, 255, 255), FontTitleMain, "��");

	if (Key[KEY_INPUT_DOWN] == 1) {
		if (Cursor != 360) { Cursor = Cursor + 30; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_UP] == 1) {
		if (Cursor != 300) { Cursor = Cursor - 30; PlaySoundMem(SE[CURSOR], DX_PLAYTYPE_BACK); }
	}
	else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
		if (Cursor == 300) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); /*Scene�J��-->�j���[�Q�[��*/; return true; }
		else if (Cursor == 330) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); /*Scene�J��-->�R���e�B�j���[*/; return true; }
		else { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); /*Scene�J��-->�I�v�V����*/; return true; }
	}
}

void Title_c::nowLoading(void) {
	ClearDrawScreen();
	NLGraph = LoadGraph("resource/NOW LOADING.png");
	DrawGraph(0, 0, NLGraph, FALSE);
	ScreenFlip();
	DeleteGraph(NLGraph);
}