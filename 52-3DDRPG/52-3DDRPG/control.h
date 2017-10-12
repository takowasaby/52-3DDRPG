#pragma once

class Fps_c;
class Event_c;
class Title_c;
class Menu_c;
class Dungeon_c;
class Data_c;
class SaveLoad_c;
class Option_c;

class Control_c {
private:
	int mode;
	int event_scene, title_scene, game_scene;
	Fps_c* mFps;
	Event_c* mEvents;
	Title_c* mTitle;
	Menu_c* mMenu;
	Dungeon_c* mDungeon;
	Data_c* mData;
	SaveLoad_c* mSaveLoad;
	Option_c* mOption;

	int Key[256];

	int *CharX, *CharY, Status[10];//仮置き用

	bool titleStart = false;
	bool titleEnd = false;

	bool SaveLoadStart = false;
	bool SaveLoadEnd = false;

	bool optionStart = false;
	bool optionEnd = false;

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
		save,
		load,
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

	bool All();
	void UpdateKey(void);
};