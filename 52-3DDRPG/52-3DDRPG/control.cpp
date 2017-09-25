#include"define.h"

Control_c::Control_c() {
	Option = new Option_c;
}

Control_c::~Control_c() {
	delete Option;
}

void Control_c::All() {



	/*
	fps.Update();	//更新
	fps.Draw();	//fps表示
	*/



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
		case start:
			//タイトル画面

			/*when player jump into option from "TITLE", option_flag = false;
				Option->SetOptionFlag(false);
				title_scene = option;
			*/

			break;
		case save_load:
			//セーブ・ロード
			break;
		case option:
			//オプション
			Option->Main();
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

			/*when player jump into option from here, option_flag = true;
				Option->SetOptionFlag(false);
				mode = title;
				title_scene = option;
			*/

			break;
		}
		break;
	}



	/*
	fps.Wait();		//待機
	*/
	
	
}

void Control_c::SetMode(int ChangeTo)
{
	mode = ChangeTo;
}

void Control_c::SetTitle(int ChangeTo)
{
	title_scene = ChangeTo;
}

void Control_c::SetGame(int ChangeTo)
{
	game_scene = ChangeTo;
}
