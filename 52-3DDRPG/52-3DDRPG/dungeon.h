#pragma once

class Data_c;

class Dungeon_c {
private:
	int x, y, dir;
	int mscenario, mstage;
	int mn, mnum, mfp, i, j;
	char fname[32];
	int input[MAP_SIZE_X * MAP_SIZE_Y];
	char inputc[MAP_SIZE_X * MAP_SIZE_Y];
	int wall[SCENARIO_SIZE][WALL_SIDE][WALL_TYPE];
	int back;
	char gname[32];
	int wallForDraw[10];
	Data_c *data;

	struct WallData_t {
		int Nwall = 1, Ewall = 1, Swall = 1, Wwall = 1;
		int type;
	};
	WallData_t wallData[MAP_SIZE_X][MAP_SIZE_Y];

public:
	Dungeon_c();
	Dungeon_c(Data_c *d);
	~Dungeon_c();
	void DungeonAll();
	void DataSet();
	void DataLoad(int scenario, int stage);
	void GraphLoad(int scenario, int stage);
	void SetData(Data_c *d);
	void BackDraw();
	void WallDrawSet();
	void WallDraw();
	void UIDraw();
	void MessageDraw();
	void WaitKey();
};