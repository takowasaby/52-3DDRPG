#pragma once

const int SCENARIO_HEIGHT = 96;

class Scenario_c {
private:
	int chooseScenario;
	int graph[2][5];
	char fname[64];
	int mKey[256];
	int bright;
	int tempScreen;
public:
	Scenario_c();
	~Scenario_c();

	void ScenarioAll();
	void Load();
	void Update();
	void Draw();
	void Reset();
	void KeyUpdate(int Key[256]);
};