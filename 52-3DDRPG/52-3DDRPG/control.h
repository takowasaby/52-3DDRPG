#pragma once

class Fps_c;
class Event_c;
class Title_c;

class Control_c {
private:
	int mode;
	int event_scene, title_scene, game_scene;
	Fps_c* fps;
	Event_c* events;
	Title_c* Title;

	int Key[256];

	bool titleStart = false;
	bool titleEnd = false;

	typedef enum {
		event,
		title,
		game,
	}Mode;

	typedef enum {
		conversation,
		opening,
		ending,
	}Event_scene;

	typedef enum {
		gameover,
		scenario,
		start,
		save_load,
		option,
	}Title_scene;

	typedef enum {
		dungeon,
		room,
		battle,
		menu,
	}Game_scene;

public:
	Control_c();		//コンストラクタ
	~Control_c();		//デストラクタ

	void All();

	void UpdateKey(void);
};