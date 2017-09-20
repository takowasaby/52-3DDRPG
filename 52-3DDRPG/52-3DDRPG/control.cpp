#include"define.h"


Control_c::Control_c()
{
	events = new Event_c;
	fps = new Fps_c;
}

Control_c::~Control_c()
{
	delete events;
	delete fps;
}

void Control_c::All() {

	fps->Update();	//更新
	fps->Draw();		//fps表示

	switch (mode) {
	case event:
		switch (event_scene) {
		case conversation:
			//立ち絵会話
			break;
		case opening:
			//オープニング
			break;
		case ending:
			//エンディング
			break;
		}
		break;

	case title:
		switch (title_scene) {
		case gameover:
			//ゲームオーバー
			break;
		case scenario: 
			//シナリオ選択画面
			break;
<<<<<<< HEAD
		case start: {
			//繧ｿ繧､繝医Ν逕ｻ髱｢
			Title_c Title;
			Title.TitleScreen();
			delete &Title;
			}
=======
		case start:
			//タイトル画面
>>>>>>> bd5f51902cb6046e6702accc1f660e09dcb273e7
			break;
		case save_load:
			//セーブ・ロード
			break;
		case option:
			//オプション
			break;
		}
		break;

	case game:
		switch (game_scene) {
		case dungeon:
			//ダンジョン探索
			break;
		case room:
			//部屋探索
			break;
		case battle:
			//バトル
			break;
		case menu:
			//メニュー
			break;
		}
		break;
	}

	fps->Wait();		//待機
}