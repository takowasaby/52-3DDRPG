#include "define.h"

Title_c::Title_c() {
	SetUseASyncLoadFlag(TRUE);
  AddFontResourceExA("resource/font/game_over.ttf", FR_PRIVATE, NULL);
	FontTitle = CreateFontToHandle("Game Over", 50, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
  TitleBGM = LoadSoundMem("resource/sounds/BGM/title/Good52ndFriends.wav");
	NLGraph = LoadGraph("resource/NOW LOADING.png");
	TitleGraph = LoadGraph("resource/title.png");
	TempScreen = MakeScreen(640, 480, FALSE);
	SetUseASyncLoadFlag(FALSE);
}

Title_c::~Title_c() {
	DeleteFontToHandle(FontTitle);
  DeleteSoundMem(TitleBGM);
	DeleteGraph(NLGraph);
	DeleteGraph(TitleGraph);
	DeleteGraph(TempScreen);
}

bool Title_c::TitleScreen(int* Key) {
  if (first == true) {
    if ((CheckHandleASyncLoad(FontTitle) != FALSE || CheckHandleASyncLoad(TitleBGM) != FALSE || CheckHandleASyncLoad(TitleGraph) != FALSE)) {
      nowLoading();
      return false;
    }
    first = false;
    ChangeVolumeSoundMem(128, TitleBGM);
    GMusic.ReserveSound(TitleBGM, DX_PLAYTYPE_LOOP);
  }

  if (end == false) {
    if (bright < 255) {
      bright += 5;
      SetDrawBright(bright, bright, bright);
    }

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

    if (CheckHitKeyAll() != 0) {
      GMusic.ReserveSound(GMusic.CommonSE[GMusic.DECISION], DX_PLAYTYPE_BACK);
      GetDrawScreenGraph(0, 0, 640, 480, TempScreen);
      end = true;
    }
  }

  else {
    if (bright > 0) {
      bright -= 5;
      SetDrawBright(bright, bright, bright);
      DrawGraph(0, 0, TempScreen, FALSE);
      SetDrawBright(255, 255, 255);
    }
    else {
      GMusic.StopSound(TitleBGM);
      GData.SceneRequest(1, 4);//シナリオ選択
      return true;
    }
  }

	return false;
}

void Title_c::nowLoading(void) {
	DrawGraph(0, 0, NLGraph, FALSE);
}