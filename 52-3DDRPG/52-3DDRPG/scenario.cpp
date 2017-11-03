#include "define.h"

Scenario_c::Scenario_c() :
chooseScenario(0),
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
}

void Scenario_c::ScenarioAll()
{
	Draw();
	Update();
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
}

void Scenario_c::Update()
{
	if (mKey[KEY_INPUT_Z] == 1) {
		GetDrawScreenGraph(0, 0, 640, 480, tempScreen);
		do {
			bright = bright - 5;
			SetDrawBright(bright, bright, bright);
			ClearDrawScreen();
			DrawGraph(0, 0, tempScreen, FALSE);
			ScreenFlip();
		} while (bright > 0);
		SetDrawBright(255, 255, 255);

		Reset();
		GData.SetScenario(chooseScenario);
		eventlist->setListFileName(chooseScenario);
		eventlist->readList();
		GData.SetEventFlag(1);
		GData.SceneRequest(0, 0);
	}
	else if (mKey[KEY_INPUT_UP] == 1) {
		if (chooseScenario > 0) chooseScenario--;
	}
	else if (mKey[KEY_INPUT_DOWN] == 1) {
		if (chooseScenario < SCENARIO_SIZE - 1) chooseScenario++;
	}
	else if (mKey[KEY_INPUT_X] == 1) {
		GetDrawScreenGraph(0, 0, 640, 480, tempScreen);
		do {
			bright = bright - 5;
			SetDrawBright(bright, bright, bright);
			ClearDrawScreen();
			DrawGraph(0, 0, tempScreen, FALSE);
			ScreenFlip();
		} while (bright > 0);
		SetDrawBright(255, 255, 255);

		Reset();
		GData.SceneBackRequest();
	}
}
void Scenario_c::Draw()
{
	if (bright < 255) {
		bright = bright + 5;
		SetDrawBright(bright, bright, bright);
	}

	for (int i = 0; i < SCENARIO_SIZE; i++) {
		if (i == chooseScenario) DrawGraph(0, 96 * i, graph[0][i], TRUE);
		else DrawGraph(0, 96 * i, graph[1][i], TRUE);
	}
}

void Scenario_c::Reset()
{
	chooseScenario = 0;
	bright = 0;
}

void Scenario_c::KeyUpdate(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}
