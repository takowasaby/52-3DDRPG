#include "define.h"

Title_c::Title_c() {
	SetUseASyncLoadFlag(TRUE);
  AddFontResourceExA("resource/font/game_over.ttf", FR_PRIVATE, NULL);
	FontTitle = CreateFontToHandle("Game Over", 50, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
  BGM = LoadSoundMem("resource/sounds/BGM/title/Good52ndFriends.wav");
	NLGraph = LoadGraph("resource/NOW LOADING.png");
	TitleGraph = LoadGraph("resource/title.png");
	TempScreen = MakeScreen(640, 480, FALSE);
	SetUseASyncLoadFlag(FALSE);
}

Title_c::~Title_c() {
	DeleteFontToHandle(FontTitle);
  DeleteSoundMem(BGM);
	DeleteGraph(NLGraph);
	DeleteGraph(TitleGraph);
	DeleteGraph(TempScreen);
}

bool Title_c::TitleScreen(int* Key) {
	if (first == true) {
		first = false;
    ChangeVolumeSoundMem(128, BGM);
    PlaySoundMem(BGM, DX_PLAYTYPE_BACK);
	}

	if ((CheckHandleASyncLoad(FontTitle) != FALSE || CheckHandleASyncLoad(TitleGraph) != FALSE)) {
		nowLoading();
		return false;
	}

	if (end == false && bright < 255) {
		bright += 5;
		SetDrawBright(bright, bright, bright);
	}

  if (end == false) {
    DrawExtendGraph(0, 0, 641, 481, TitleGraph, FALSE);
    
    if (fade == 255) flag = true;
    else if (fade == 125) flag = false;

    if (flag) {
      fade -= 5;
      DrawFormatStringToHandle(160, 360, GetColor(fade, fade, fade), FontTitle, "PRESS ANY KEY");
    }
    else {
      fade += 5;
      DrawFormatStringToHandle(160, 360, GetColor(fade, fade, fade), FontTitle, "PRESS ANY KEY");
    }
  }

  if (end == false && (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1)) {
    GMusic.ReserveSound(GMusic.CommonSE[GMusic.DECISION], DX_PLAYTYPE_BACK);
    GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
    end = true;
  }

  if (end == true) {
    if (bright > 0) {
      bright -= 5;
      SetDrawBright(bright, bright, bright);
      ClearDrawScreen();
      DrawGraph(0, 0, TempScreen, FALSE);
      ScreenFlip();
      SetDrawBright(255, 255, 255);
    }
    else {
      GData.SceneRequest(1, 1);//シナリオ選択
      return true;
    }
  }

	return false;
}

void Title_c::nowLoading(void) {
	DrawGraph(0, 0, NLGraph, FALSE);
}