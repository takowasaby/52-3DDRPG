#include "define.h"

Scenario_c::Scenario_c() :
chooseScenario(0),
first(true),
end(0),
bright(0),
tempScreen(0)
{
	Load();
	tempScreen = MakeScreen(640, 480, FALSE);
}
Scenario_c::~Scenario_c()
{
	for (int i = 0; i < SCENARIO_SIZE; i++) {
		DeleteGraph(graph[0][i]);
		DeleteGraph(graph[1][i]);
	}
  DeleteSoundMem(ScenarioBGM);
}

void Scenario_c::ScenarioAll()
{
	Draw();
	if (!first) Update();
}

void Scenario_c::SetEventList(EventList *el)
{
	eventlist = el;
}

void Scenario_c::Load()
{
	for (int i = 0; i < SCENARIO_SIZE; i++) {
		sprintf_s(fname, "resource/scenario/%d.png", i);
		graph[0][i] = LoadGraph(fname);
//		graph[1][i] = graph[0][i];
		sprintf_s(fname, "resource/scenario/0%d.png", i);
		graph[1][i] = LoadGraph(fname);
		GraphFilter(graph[1][i], DX_GRAPH_FILTER_MONO, 0, 0);
	}
	clear = LoadGraph("resource/picture/other/clear.png");
    ScenarioBGM = LoadSoundMem("resource/sounds/BGM/scenario select/SSelect.wav");
    ChangeVolumeSoundMem(128, ScenarioBGM);
}

void Scenario_c::Update()
{
  if (end == 0) {
    if (mKey[KEY_INPUT_Z] == 1 || mKey[KEY_INPUT_RETURN] == 1) {
      GMusic.ReserveSound(GMusic.CommonSE[GMusic.DECISION], DX_PLAYTYPE_BACK);
      GetDrawScreenGraph(0, 0, 640, 480, tempScreen);
      end = 1;
    }
    else if (mKey[KEY_INPUT_UP] == 1) {
      if (chooseScenario > 0) { GMusic.ReserveSound(GMusic.CommonSE[GMusic.CURSOR], DX_PLAYTYPE_BACK); chooseScenario--; }
    }
    else if (mKey[KEY_INPUT_DOWN] == 1) {
      if (chooseScenario < SCENARIO_SIZE - 1) { GMusic.ReserveSound(GMusic.CommonSE[GMusic.CURSOR], DX_PLAYTYPE_BACK); chooseScenario++; }
    }
    else if (mKey[KEY_INPUT_X] == 1) {
      GMusic.ReserveSound(GMusic.CommonSE[GMusic.CANCEL], DX_PLAYTYPE_BACK);
      GetDrawScreenGraph(0, 0, 640, 480, tempScreen);
      end = -1;
    }
  }

  else {
    if (bright > 0) {
      bright -= 5;
      SetDrawBright(bright, bright, bright);
      DrawGraph(0, 0, tempScreen, FALSE);
      SetDrawBright(255, 255, 255);
      return;
    }
    else if (end == 1) {
      GData.SetScenario(chooseScenario);
	  GData.CountStart();
      eventlist->setListFileName(chooseScenario);
      eventlist->readList();
      GData.SetEventFlag(1);
	  eventlist->SetFlagfromData(GData.GetScenario());
	  eventlist->Event(0);
      GData.SceneRequest(2, 0);
	  GData.SetStage(GData.GetStage());
      GMusic.StopSound(ScenarioBGM);
      Reset();
    }
    else {
      GData.SceneBackRequest();
      GMusic.StopSound(ScenarioBGM);
      Reset();
    }
  }
}

void Scenario_c::Draw()
{
  if (first == true) {
    if (bright < 255) {
      bright += 5;
      SetDrawBright(bright, bright, bright);
    }
    else {
      first = false;
      GMusic.ReserveSound(ScenarioBGM, DX_PLAYTYPE_LOOP);
    }
  }

  if (end == 0) {
    for (int i = 0; i < SCENARIO_SIZE; i++) {
      if (i == chooseScenario) DrawGraph(0, 96 * i, graph[0][i], TRUE);
      else DrawGraph(0, 96 * i, graph[1][i], TRUE);
	  if (GData.GetClearFlag(i)) DrawGraph(480, 96 * i, clear, TRUE);
    }
  }
}

void Scenario_c::Reset()
{
	chooseScenario = 0;
  bright = 0;
  first = true;
  end = 0;
}

void Scenario_c::KeyUpdate(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}
