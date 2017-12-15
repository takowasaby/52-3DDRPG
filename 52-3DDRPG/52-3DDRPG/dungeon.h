#pragma once

class TextBox;
class EventList;

class Dungeon_c {
private:
	int x, y, dir;
	int mscenario, mstage;
	int mn, mnum, mfp;
	char fname[32];
	int input[MAP_SIZE_X * MAP_SIZE_Y];
	char inputc[MAP_SIZE_X * MAP_SIZE_Y];
	int wall[SCENARIO_SIZE][WALL_SIDE][WALL_TYPE];
	struct eventNum{
		int num;
		int condition;
	};
	eventNum eventNum[MAP_SIZE_X][MAP_SIZE_Y];
	int back;
	char gname[64];
	int wallForDraw[10];

	int walk, run, decision, bgm;

	int* mMode;
	int* mEvent_scene;
	int* mTitle_scene;
	int* mGame_scene;
	int mKey[256];

	struct WallData_t {
		int Nwall = 1, Ewall = 1, Swall = 1, Wwall = 1;
		int type;
	};
	WallData_t wallData[MAP_SIZE_X][MAP_SIZE_Y];

	TextBox *textBox;
	EventList *eventList;

public:
	Dungeon_c();
	Dungeon_c(Data_c* data, int* mode, int* event_scene, int* title_scene, int* game_scene);
	~Dungeon_c();
	void KeyUpdate(int Key[256]);
	void DungeonAll();

	void DataSet();
	void DataLoad(int scenario, int stage);
	void GraphLoad(int scenario, int stage);
	void GraphDelete();

	void SetEventList(EventList *e);
	void BackDraw();
	void WallDrawSet();
	void WallDraw();
	void UIDraw();
	void MessageDraw();
	void WaitKey();
};