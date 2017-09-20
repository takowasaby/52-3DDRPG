#pragma once

class Fps_c;
class Event_c;

class Control_c {
private:
	int mode = 1;
	int event_scene = 0, title_scene = 2, game_scene = 0;
	Fps_c* fps;
	Event_c* events;
public:
	Control_c();		//コンストラクタ
	~Control_c();		//デストラクタ

	void All();
};

typedef enum {
	event,
	title,
	game,
}mode;

typedef enum {
	conversation,
	opening,
	ending,
}event_scene;

typedef enum {
	gameover,
	scenario,
	start,
	save_load,
	option,
}title_scene;

typedef enum {
	dungeon,
	room,
	battle,
	menu,
}game_scene;