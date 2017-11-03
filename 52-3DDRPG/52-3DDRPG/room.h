#pragma once

class Data_c;

class Room_c {
private:
	int mscenario, mstage, mroom;
	int datay, datax, mfp;
	int roomsizex, roomsizey;
	int enumx, enumy, etc;
	int wall, floor, door;
	int doorx[5], doory[5];
	int selectx = 0, selecty = 0;
	int scrollx = 0, scrolly = 0;
	int select;
	bool cflag = false;
	Data_c *mData;
	char gname[32];
	char fname[32];
	int gx, gy;
	int furniture[ROOM_FURNITURE_MAX];
	int furniturehight[ROOM_FURNITURE_MAX];
	int input[32];
	char inputc[32];

	int* mMode;
	int* mEvent_scene;
	int* mTitle_scene;
	int* mGame_scene;
	int mKey[256];

	struct RoomData_t {
		int type;
		int event;
	};
	RoomData_t roomData[ROOM_MAXSIZE_X][ROOM_MAXSIZE_Y];

	EventList *eventlist;

public:
	Room_c();
	Room_c(Data_c* data, int* mode, int* event_scene, int* title_scene, int* game_scene);
	~Room_c();
	void KeyUpdate(int Key[256]);
	void RoomAll();
	void DataLoad(int scenario, int stage, int room);
	void GraphLoad(int scenario);
	void SetEventList(EventList *e);
	void RoomDraw();
	void WaitKey();
	void SetData(Data_c *d);
	void MessageDraw();

};