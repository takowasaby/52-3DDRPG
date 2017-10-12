#include "define.h"

Control_c::Control_c() :
mode(1),
event_scene(0),
title_scene(2),
game_scene(0)
{
	mEvents = new Event_c;
	mFps = new Fps_c;
	mMenu = new Menu_c();
	mDungeon = new Dungeon_c(mData, &mode, &event_scene, &title_scene, &game_scene);
	mData = new Data_c;
}

Control_c::~Control_c()
{
	delete mEvents;
	delete mFps;
//	delete mTitle;
	delete mMenu;
	delete mDungeon;
	delete mData;
//	delete mSaveLoad;
}

bool Control_c::All() {

	UpdateKey();	//キー入力の検知

	mFps->Update();	//更新

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
			if (titleStart == false) { titleStart = true; mTitle = new Title_c; }
			titleEnd = mTitle->TitleScreen(Key, &title_scene);
			if (titleEnd == true) { titleEnd = false; delete mTitle; }
			}
			break;
		case save: {
			//セーブ
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->SaveScreen(Key, &game_scene, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; delete mSaveLoad; }
			}
			break;
		case load: {
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->LoadScreen(Key, &game_scene, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; delete mSaveLoad; }
			}
			break;
		case option:
			//オプション
			if (optionStart == false) { optionStart = true; mOption = new Option_c; }
			optionEnd = mOption->Main(Key, &mode, &title_scene, &game_scene);
			if (optionEnd == true) { optionEnd = false; delete mOption; }
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
			mMenu->KeyUpdata(Key);
			//メニュー
			break;
		}
		break;
	}

	mFps->Draw();	//fps表示
	mFps->Wait();	//待機

	if (Key[KEY_INPUT_ESCAPE] == 1) {
		return FALSE;
	}
	return TRUE;
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