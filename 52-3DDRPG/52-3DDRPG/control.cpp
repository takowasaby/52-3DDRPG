#include "define.h"

Control_c::Control_c() {
	mEvents = new Event_c;
	mFps = new Fps_c;
	mMenu = new Menu_c();
	mDungeon = new Dungeon_c();
	mRoom = new Room_c();
	mEventlist = new EventList();
	mScenario = new Scenario_c();
//	mGameOver = new GameOver();

//	GData.LoadAll(0);

	mRoom->SetEventList(mEventlist);
	mDungeon->SetEventList(mEventlist);
	mScenario->SetEventList(mEventlist);

	mEventlist->Initialize(mEvents);
//	mEventlist->setListFileName(0);
//	mEventlist->readList();
//	mEventlist->Event(0);
//	mEventlist->Event(1);
//	mEventlist->Event(2);
}

Control_c::~Control_c() {
  delete mEvents;
  delete mFps;
  delete mMenu;
  delete mDungeon;
  delete mRoom;
  delete mEventlist;
  delete mScenario;
//  delete mGameOver;
}

bool Control_c::All() {

	UpdateKey();	//キー入力の検知

	mFps->Update();	//更新

	switch (GData.GetMode()) {
	case event:
		switch (GData.GetScene(event)) {
		case conversation:
			//立ち絵会話
			if (GData.GetEventFlag()) {
				mEventlist->SetFlagfromData(GData.GetScenario());
			}
			else {
				GData.SceneRequest(2, 0);
			}
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
		switch (GData.GetScene(title)) {
		case gameover:
			//ゲームオーバー
			if (GameOverStart == false) { GameOverStart = true; mGameOver = new GameOver; }
			GameOverEnd = mGameOver->GameOverAll(Key);
			if (GameOverEnd == true) { GameOverEnd = false; GameOverStart = false; delete mGameOver; }
			break;
		case scenario: 
			//シナリオ選択画面
			mScenario->KeyUpdate(Key);
			mScenario->ScenarioAll();
			break;
		case start: {
			//タイトル画面
			if (titleStart == false) { titleStart = true; mTitle = new Title_c; }
			titleEnd = mTitle->TitleScreen(Key);
			if (titleEnd == true) { titleEnd = false; titleStart = false; delete mTitle; }
			}
			break;
		case save: {
			//セーブ
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->SaveScreen(Key);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; SaveLoadStart = false; delete mSaveLoad; }
			}
			break;
		case load: {
			//ロード
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->LoadScreen(Key);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; SaveLoadStart = false; delete mSaveLoad; }
			}
			break;
		case option:
			//オプション
			if (optionStart == false) { optionStart = true; mOption = new Option_c; }
			optionEnd = mOption->Main(Key);
			if (optionEnd == true) { optionEnd = false; optionStart = false; delete mOption; }
			break;
		}
		break;

	case game:
		switch (GData.GetScene(game)) {
		case dungeon:
			//ダンジョン探索
			mDungeon->KeyUpdate(Key);
			mDungeon->DungeonAll();
			break;
		case room:
			//部屋探索
			mRoom->KeyUpdate(Key);
			mRoom->RoomAll();
			break;
		case battle:
			//バトル
			if (BattleStart == false) { BattleStart = true; battleManager = new BattleManager; }
			battleManager->KeyUpdata(Key);
			BattleEnd = battleManager->Update();
			battleManager->Draw();
			if (BattleEnd == true) { BattleEnd = false; BattleStart = false; delete battleManager; mEventlist->setBattleFlag(0); }
			break;
		case menu:
			mMenu->KeyUpdate(Key);
			mMenu->MenuAll();
			//メニュー
			break;
		}
		break;
	}

	mEventlist->call();

	if (GData.GetCountFlag()) GData.ClockCount();

	if (GData.GetDungeonLoadFlag()) {
		mDungeon->DataLoad(GData.GetScenario(), GData.GetStage());
		GData.SetDungeonLoadFlag(FALSE);
	}
	else if (GData.GetRoomLoadFlag()) {
		mRoom->CursorReset();
		mRoom->DataLoad(GData.GetScenario(), GData.GetStage(), GData.GetRoom());
		GData.SetRoomLoadFlag(FALSE);
	}

	GMusic.PlaySounds();

	/*
	if (Key[KEY_INPUT_F]) {
		if (windowMode) {
			ChangeWindowMode(1);
			windowMode = 0;
		}
		else {
			ChangeWindowMode(0);
			windowMode = 1;
		}
	}
	*/

	//mFps->Draw();	//fps表示
	mFps->Wait();	//待機

	if (Key[KEY_INPUT_ESCAPE] == 1) {
		return false;
	}
	return true;
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
