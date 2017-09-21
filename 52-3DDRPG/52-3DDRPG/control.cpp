#include "define.h"

int Key[256];
void UpdateKey(void);

Control_c::Control_c()
{
	events = new Event_c;
	fps = new Fps_c;
	Title = new Title_c;
}

Control_c::~Control_c()
{
	delete events;
	delete fps;
	delete Title;
}

void Control_c::All() {

	UpdateKey();

	fps->Update();	//更新

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
			Title->TitleScreen(Key);
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

	fps->Draw();	//fps表示
	fps->Wait();	//待機
}

void UpdateKey(void) {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
}