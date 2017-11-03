#pragma once

const int SCENARIO_HEIGHT = 96;

class EventList;

class Scenario_c {
private:
	int chooseScenario;
	int graph[2][5];
	char fname[64];
	int mKey[256];
	int bright;
	int tempScreen;
	EventList *eventlist;
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