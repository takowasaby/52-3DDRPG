#pragma once

class Control_c {
private:
	int mode = 0;
	int event_scene, title_scene, game_scene = 0;



	//Fps_c fps;



public:
	Control_c();		//�R���X�g���N�^
	~Control_c();		//�f�X�g���N�^

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