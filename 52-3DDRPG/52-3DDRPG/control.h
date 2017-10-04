#pragma once

class Fps_c;
class Event_c;
class Title_c;
class Menu_c;
class Dungeon_c;
class Data_c;

class Control_c {
private:
<<<<<<< HEAD
	int mode = 0;
	int event_scene, title_scene, game_scene = 0;



	//Fps_c fps;



	Option_c* Option;
=======
	int mode;
	int event_scene, title_scene, game_scene;
	Fps_c* mFps;
	Event_c* mEvents;
	Title_c* mTitle;
	Menu_c* mMenu;
	Dungeon_c* mDungeon;
	Data_c* mData;

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
>>>>>>> master

public:
	Control_c();		//コンストラクタ
	~Control_c();		//デストラクタ

	void All();

<<<<<<< HEAD
	void SetMode(int ChangeTo);
	void SetTitle(int ChangeTo);
	void SetGame(int ChangeTo);
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
=======
	void UpdateKey(void);
};
>>>>>>> master
