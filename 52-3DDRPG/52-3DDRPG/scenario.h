#pragma once

const int SCENARIO_HEIGHT = 96;

class EventList;

class Scenario_c {
private:
	EventList *eventlist;
	int chooseScenario;
	int graph[2][5];
	int clear;
	char fname[64];
	int mKey[256];
    bool first;
    int end;
	int bright;
	int tempScreen;
    int ScenarioBGM;
public:
	Scenario_c();
	~Scenario_c();

	void ScenarioAll();
	void SetEventList(EventList*);
	void Load();
	void Update();
	void Draw();
	void Reset();
	void KeyUpdate(int Key[256]);
};