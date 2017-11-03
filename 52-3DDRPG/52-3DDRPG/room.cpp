#include"define.h"

Room_c::Room_c() :
	mscenario(0),
	mstage(3),
	mroom(0)
{
	// data.GetScenario();
	// data.stage();
	// date.Getroom();

	DataLoad(mscenario, mstage, mroom);
	GraphLoad(mscenario);

}

Room_c::Room_c(Data_c* data, int * mode, int * event_scene, int * title_scene, int * game_scene) :
	mData(data),
	mMode(mode),
	mEvent_scene(event_scene),
	mTitle_scene(title_scene),
	mGame_scene(game_scene)
{

}

Room_c::~Room_c()
{
	//delete mData;
}

void Room_c::KeyUpdate(int Key[256])
{
	for (int i = 0; i < 256; i++) {
		mKey[i] = Key[i];
	}
}

void Room_c::RoomAll() 
{
	mroom = GData.GetRoom();
	RoomDraw();
	WaitKey();
}

void Room_c::DataLoad(int scenario, int stage, int room)
{
	sprintf_s(fname, "resource/csv/scenario%d/room/room%d-%d-%d.csv", scenario, scenario, stage, room);

	mfp = FileRead_open(fname);
	if (mfp == NULL) {
		printfDx("read error\n");
		return;
	}

	/*for (i = 0; i<1; i++)//最初の2行読み飛ばす
	while (FileRead_getc(mfp) != '\n');*/

	datay = 0, datax = 0;
	roomsizex = 0, roomsizey = 0;
	while (1) {
		for (int i = 0; i < 32; i++) {
			inputc[i] = input[i] = FileRead_getc(mfp);//1文字取得する
			if (inputc[i] == '/') {//スラッシュがあれば
				while (FileRead_getc(mfp) != '\n');//改行までループ
				i = -1;//カウンタを最初に戻して
				continue;
			}
			if (input[i] == ',' || input[i] == '\n') {//カンマか改行なら
				if (input[i] == '\n')cflag = true;
				inputc[i] = '\0';//そこまでを文字列とし
				break;
			}
			if (input[i] == EOF) {//ファイルの終わりなら]
				roomsizey = datay--;
				goto EXFILE1;//終了
			}
		}
		roomData[datax][datay].type = atoi(inputc) % 100;
		roomData[datax][datay].event = abs(atoi(inputc) / 100);
		datax++;
		if (cflag == true) {
			roomsizex = datax--;
			datax = 0;
			datay++;
			cflag = false;
		}

	}

EXFILE1:
	FileRead_close(mfp);
}

void Room_c::GraphLoad(int scenario)
{
	sprintf_s(gname, "resource/picture/scenario%d/room/wall.png", scenario);
	wall = LoadGraph(gname);

	sprintf_s(gname, "resource/picture/scenario%d/room/floor.png", scenario);
	floor = LoadGraph(gname);

	sprintf_s(gname, "resource/picture/scenario%d/room/select.png", scenario);
	select = LoadGraph(gname);

	for (int j = 0; j < roomsizey; j++) {
		for (int i = 0; i < roomsizex; i++) {
			if(roomData[i][j].type > 0){
				sprintf_s(gname, "resource/picture/scenario%d/room/%d.png", scenario, roomData[i][j].type);
				furniture[roomData[i][j].type] = LoadGraph(gname);
				GetGraphSize(furniture[roomData[i][j].type], &gx, &gy);
				furniturehight[roomData[i][j].type] = gy * ROOM_RATIO;
			}
		}
	}
}

void Room_c::RoomDraw()
{
	for (int i = 0; i < roomsizex; i++) {
		DrawExtendGraph(
			ROOM_POINT_X - scrollx - ROOM_WALL_SIZE_X - (ROOM_SHIFT_SIZE_X * i),
			ROOM_POINT_Y - scrolly - ROOM_WALL_SIZE_Y + (ROOM_SHIFT_SIZE_Y * i), 
			ROOM_POINT_X - scrollx - ROOM_SHIFT_SIZE_X * i, 
			ROOM_POINT_Y - scrolly + ROOM_SHIFT_SIZE_Y * i, 
			wall, true);
	}
	for (int i = 0; i < roomsizey; i++) {
		DrawExtendGraph(
			ROOM_POINT_X - scrollx + ROOM_WALL_SIZE_X + (ROOM_SHIFT_SIZE_X * i),
			ROOM_POINT_Y - scrolly - ROOM_WALL_SIZE_Y + (ROOM_SHIFT_SIZE_Y * i),		
			ROOM_POINT_X - scrollx + (ROOM_SHIFT_SIZE_X * i),
			ROOM_POINT_Y - scrolly + (ROOM_SHIFT_SIZE_Y * i),
			wall, true);
	}

	for (int j = 0; j < roomsizey; j++) {
		for (int i = 0; i < roomsizex; i++) {
			DrawExtendGraph(
				ROOM_POINT_X - scrollx - ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * i) + (ROOM_FLOOR_HALFSIZE_X * j),
				ROOM_POINT_Y - scrolly + ROOM_SHIFT_SIZE_Y * (i - 1) + (ROOM_FLOOR_HALFSIZE_Y * j),
				ROOM_POINT_X - scrollx + ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * i) + (ROOM_FLOOR_HALFSIZE_X * j),
				ROOM_POINT_Y - scrolly + ROOM_FLOOR_SIZE_Y + (ROOM_SHIFT_SIZE_Y * (i - 1) + (ROOM_FLOOR_HALFSIZE_Y * j)),
				floor, true);
		}
	}

	for (int j = 0; j < roomsizey; j++) {
		for (int i = 0; i < roomsizex; i++) {
			if (roomData[roomsizex - i - 1][j].type > 0)
				DrawExtendGraph(
					ROOM_POINT_X - scrollx - ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * i) + (ROOM_FLOOR_HALFSIZE_X * j),
					ROOM_POINT_Y - scrolly + ROOM_FLOOR_SIZE_Y - furniturehight[roomData[roomsizex - i - 1][j].type] + ROOM_SHIFT_SIZE_Y * (i - 1) + (ROOM_FLOOR_HALFSIZE_Y * j),
					ROOM_POINT_X - scrollx + ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * i) + (ROOM_FLOOR_HALFSIZE_X * j),
					ROOM_POINT_Y - scrolly + ROOM_FLOOR_SIZE_Y + ROOM_SHIFT_SIZE_Y * (i - 1) + (ROOM_FLOOR_HALFSIZE_Y * j),
					furniture[roomData[roomsizex - i - 1][j].type], true);
			else if (roomData[roomsizex - i - 1][j].type < 0)					
				DrawExtendGraph(
					ROOM_POINT_X - scrollx+ ROOM_FURNITURE_LENGTH - ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * i) + (ROOM_FLOOR_HALFSIZE_X * j),
					ROOM_POINT_Y - scrolly + ROOM_FLOOR_SIZE_Y - furniturehight[abs(roomData[roomsizex - i - 1][j].type)] + ROOM_SHIFT_SIZE_Y * (i - 1) + (ROOM_FLOOR_HALFSIZE_Y * j),
					ROOM_POINT_X - scrollx-ROOM_FURNITURE_LENGTH + ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * i) + (ROOM_FLOOR_HALFSIZE_X * j),
					ROOM_POINT_Y - scrolly + ROOM_FLOOR_SIZE_Y + ROOM_SHIFT_SIZE_Y * (i - 1) + (ROOM_FLOOR_HALFSIZE_Y * j),
					furniture[abs(roomData[roomsizex - i - 1][j].type)], true);
		}
	}

	DrawExtendGraph(
		ROOM_POINT_X - scrollx - ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * (roomsizex - selectx - 1)) + (ROOM_FLOOR_HALFSIZE_X * selecty),
		ROOM_POINT_Y - scrolly + ROOM_FLOOR_SIZE_Y - ROOM_SELECT_SIZE_Y + ROOM_SHIFT_SIZE_Y * (roomsizex - selectx - 1) + (ROOM_FLOOR_HALFSIZE_Y * selecty)- ROOM_FLOOR_HALFSIZE_Y,
		ROOM_POINT_X - scrollx + ROOM_FLOOR_HALFSIZE_X - (ROOM_SHIFT_SIZE_X * (roomsizex - selectx - 1)) + (ROOM_FLOOR_HALFSIZE_X * selecty),
		ROOM_POINT_Y - scrolly + ROOM_FLOOR_SIZE_Y + ROOM_SHIFT_SIZE_Y * (roomsizex - selectx - 1) + (ROOM_FLOOR_HALFSIZE_Y * selecty)- ROOM_FLOOR_HALFSIZE_Y,
		select, true);
	

}

void Room_c::WaitKey() {
	if (mKey[KEY_INPUT_C] >= 1) {
		if (mKey[KEY_INPUT_DOWN] == 1) {
			scrolly += 50;
			if (ROOM_POINT_Y + ROOM_FLOOR_HALFSIZE_Y*(roomsizey + roomsizex) - scrolly < 0)scrolly = ROOM_POINT_Y + ROOM_FLOOR_HALFSIZE_Y*(roomsizey + roomsizex) - 30;
		}
		else if (mKey[KEY_INPUT_UP] == 1) {
			scrolly -= 50;
			if (480 - ROOM_POINT_Y + ROOM_WALL_SIZE_Y + scrolly < 0)scrolly = -(480 - ROOM_POINT_Y + ROOM_WALL_SIZE_Y) + 30;
		}
		else if (mKey[KEY_INPUT_LEFT] == 1) {
			scrollx -= 50;
			if (640 - ROOM_POINT_X + ROOM_FLOOR_HALFSIZE_X * roomsizex + scrollx < 0)scrollx = -(640 - ROOM_POINT_X + ROOM_FLOOR_HALFSIZE_X * roomsizex) + 30;
		}
		else if (mKey[KEY_INPUT_RIGHT] == 1) {
			scrollx += 50;
			if (ROOM_POINT_X + ROOM_FLOOR_HALFSIZE_X * roomsizey - scrollx < 0)scrollx = ROOM_POINT_X + (ROOM_FLOOR_HALFSIZE_X * roomsizey) - 30;
		}
	}
	else if (mKey[KEY_INPUT_DOWN] == 1) {
		selecty++;
		if (selecty >= roomsizey)selecty = roomsizey - 1;
	}
	else if (mKey[KEY_INPUT_UP] == 1) {
		selecty--;
		if (selecty < 0)selecty = 0;
	}
	else if (mKey[KEY_INPUT_LEFT] == 1) { 
		selectx--;
		if (selectx < 0)selectx = 0;
	}
	else if (mKey[KEY_INPUT_RIGHT] == 1) { 
		selectx++; 
		if (selectx >= roomsizex)selectx = roomsizex - 1;
	}
	else if (mKey[KEY_INPUT_Z] == 1){
		//	printfDx("Room(%d,%d)has been selected Type:%d\nExecute event #%d\n", selectx, selecty, roomData[selectx][selecty].type, roomData[selectx][selecty].event);//Z決定時に動作するアクションをここに書く
		eventlist->Event(roomData[selectx][selecty].event);
	}
	else if (mKey[KEY_INPUT_D] == 1)printfDx("%d", abs(roomData[0][4].type));
}

void Room_c::SetEventList(EventList *e)
{
	eventlist = e;
}

void Room_c::SetData(Data_c *d)
{
	mData = d;
}

void Room_c::MessageDraw()
{
}