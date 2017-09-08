#pragma once

#include "define.h"

class Dungeon_c {
private:
	int mn, mnum, mfp, i, j;
	char fname[10];
	int input[ROOM_MAX_X * ROOM_MAX_Y];
	char inputc[ROOM_MAX_X * ROOM_MAX_Y];

	struct WallData_t {
		int Nwall = 0, Ewall = 0, Swall = 0, Wwall = 0;
		int type;
	};
	WallData_t wallData[ROOM_MAX_X][ROOM_MAX_Y];

	int wallV[ROOM_MAX_X - 1][ROOM_MAX_Y];
	int wallH[ROOM_MAX_X][ROOM_MAX_Y - 1];

public:
	void DataLoad(int scenario, int stage);
	void WallSet();
};