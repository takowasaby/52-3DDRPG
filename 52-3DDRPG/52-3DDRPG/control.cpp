#include "define.h"

Control_c::Control_c() 
{
	mEvents = new Event_c;
	mFps = new Fps_c;
	mMenu = new Menu_c();
	mDungeon = new Dungeon_c();
}

Control_c::~Control_c()
{
	delete mEvents;
	delete mFps;
//	delete mTitle;
	delete mMenu;
	delete mDungeon;
//	delete mSaveLoad;
}

bool Control_c::All() {

	UpdateKey();	//キー入力の検知

	mFps->Update();	//更新

	switch (GData.GetMode()) {
	case event:
		switch (GData.GetScene(0)) {
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
		switch (GData.GetScene(1)) {
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
			titleEnd = mTitle->TitleScreen(Key);
			if (titleEnd == true) { titleEnd = false; delete mTitle; }
			}
			break;
		case save: {
			//セーブ
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->SaveScreen(Key, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; delete mSaveLoad; }
			}
			break;
		case load: {
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->LoadScreen(Key, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; delete mSaveLoad; }
			}
			break;
		case option:
			//オプション
			if (optionStart == false) { optionStart = true; mOption = new Option_c; }
			optionEnd = mOption->Main(Key);
			if (optionEnd == true) { optionEnd = false; delete mOption; }
			break;
		}
		break;

	case game:
		switch (GData.GetScene(2)) {
		case dungeon:
			//ダンジョン探索
			mDungeon->KeyUpdata(Key);
			mDungeon->DungeonAll();
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