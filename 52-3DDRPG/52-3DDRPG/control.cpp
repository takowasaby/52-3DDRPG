#include "define.h"

<<<<<<< HEAD
Control_c::Control_c() {
	Option = new Option_c;
}

Control_c::~Control_c() {
	delete Option;
=======
Control_c::Control_c() :
mode(1),
event_scene(0),
title_scene(2),
game_scene(0)
{
	mEvents = new Event_c;
	mFps = new Fps_c;
	mMenu = new Menu_c(mData, &mode, &event_scene, &title_scene, &game_scene);
	mDungeon = new Dungeon_c(mData, &mode, &event_scene, &title_scene, &game_scene);
	mData = new Data_c;
}

Control_c::~Control_c()
{
	delete mEvents;
	delete mFps;
	delete mTitle;
	delete mMenu;
	delete mDungeon;
	delete mData;
>>>>>>> master
}

void Control_c::All() {

<<<<<<< HEAD


	/*
	fps.Update();	//譖ｴ譁ｰ
	fps.Draw();	//fps陦ｨ遉ｺ
	*/


=======
	UpdateKey();	//キー入力の検知

	mFps->Update();	//更新
>>>>>>> master

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
<<<<<<< HEAD
		case start:
			//繧ｿ繧､繝医Ν逕ｻ髱｢

			/*when player jump into option from "TITLE", option_flag = false;
				Option->SetOptionFlag(false);
				title_scene = option;
			*/

=======
		case start: {
			//タイトル画面
			if (titleStart == false) { titleStart = true; mTitle = new Title_c; }
			titleEnd = mTitle->TitleScreen(Key, &title_scene);
			if (titleEnd == true) { titleEnd = false; delete mTitle; }
			}
>>>>>>> master
			break;
		case save_load:
			//セーブ・ロード
			DrawFormatString(150, 100, GetColor(255, 255, 255), "セーブ･ロード"); //デバッグ用
			break;
		case option:
<<<<<<< HEAD
			//繧ｪ繝励す繝ｧ繝ｳ
			Option->Main();
=======
			//オプション
			DrawFormatString(150, 100, GetColor(255, 255, 255), "オプション"); //デバッグ用
>>>>>>> master
			break;
		}
		break;

	case game:
		switch (game_scene) {
		case dungeon:
			//ダンジョン探索
			mDungeon->KeyUpdata(Key);
			break;
		case room:
			//部屋探索
			break;
		case battle:
			//バトル
			break;
		case menu:
<<<<<<< HEAD
			//繝｡繝九Η繝ｼ

			/*when player jump into option from here, option_flag = true;
				Option->SetOptionFlag(false);
				mode = title;
				title_scene = option;
			*/

=======
			mMenu->KeyUpdata(Key);
			//メニュー
>>>>>>> master
			break;
		}
		break;
	}

<<<<<<< HEAD


	/*
	fps.Wait();		//蠕・ｩ・
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
=======
	mFps->Draw();	//fps表示
	mFps->Wait();	//待機
>>>>>>> master
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