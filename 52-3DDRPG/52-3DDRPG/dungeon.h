#pragma once

const int MAP_SIZE_X = 25;
const int MAP_SIZE_Y = 25;

class Dungeon_c {
private:
	int mscenario, mstage;
	int mn, mnum, mfp, i, j;
	char fname[10];
	int input[MAP_SIZE_X * MAP_SIZE_Y];
	char inputc[MAP_SIZE_X * MAP_SIZE_Y];

	struct WallData_t {
		int Nwall = 1, Ewall = 1, Swall = 1, Wwall = 1;
		int type;
	};
	WallData_t wallData[MAP_SIZE_X][MAP_SIZE_Y];

	Data_c data;

public:
	Dungeon_c();
	~Dungeon_c();
	void DungeonAll();
	void DataLoad(int scenario, int stage);
	void GraphLoad(int scenario, int stage);
	void BackDraw();
	void WallDraw();
	void UIDraw();
	void MessageDraw();
	void WaitKey();
};