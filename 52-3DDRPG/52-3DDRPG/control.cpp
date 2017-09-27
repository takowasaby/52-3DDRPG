#include "define.h"

Control_c::Control_c() :
mode(1),
event_scene(0),
title_scene(2),
game_scene(0)
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

	UpdateKey();	//キー入力の検知

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
			DrawFormatString(150, 100, GetColor(255, 255, 255), "シナリオ選択"); //デバッグ用
			break;
		case start: {
			//タイトル画面
			if (titleStart == false) { titleStart = true; Title = new Title_c; }
			titleEnd = Title->TitleScreen(Key, &title_scene);
			if (titleEnd == true) { titleEnd = false; delete Title; }
			}
			break;
		case save_load:
			//セーブ・ロード
			DrawFormatString(150, 100, GetColor(255, 255, 255), "セーブ･ロード"); //デバッグ用
			break;
		case option:
			//オプション
			DrawFormatString(150, 100, GetColor(255, 255, 255), "オプション"); //デバッグ用
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

void Control_c::UpdateKey(void)
{
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