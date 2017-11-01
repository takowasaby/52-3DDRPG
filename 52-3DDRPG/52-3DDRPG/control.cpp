#include "define.h"

Control_c::Control_c() {
	mEvents = new Event_c;
	mFps = new Fps_c;
	mMenu = new Menu_c();
	mDungeon = new Dungeon_c();
	mRoom = new Room_c();
<<<<<<< HEAD
	mEventlist = new EventList();
=======
	mScenario = new Scenario_c();
>>>>>>> scenario

	GData.LoadAll(0);
	battleManager = new BattleManager();

	mEventlist->Initialize(mEvents);
	mEventlist->setListFileName("resource/data/eventlist.csv");
	mEventlist->readList();
	mEventlist->Event(0);
	mEventlist->Event(1);
	mEventlist->Event(2);
}

Control_c::~Control_c() {
	delete mEvents;
	delete mFps;
	delete mMenu;
	delete mDungeon;
	delete mRoom;
}

bool Control_c::All() {

	UpdateKey();	//�L�[���͂̌��m

	mFps->Update();	//�X�V

	switch (GData.GetMode()) {
	case event:
		switch (GData.GetScene(event)) {
		case conversation:
			//�����G��b
			break;
		case opening:
			//�I�[�v�j���O
			break;
		case ending:
			//�G���f�B���O
			break;
		}
		break;

	case title:
		switch (GData.GetScene(title)) {
		case gameover:
			//�Q�[���I�[�o�[
			break;
		case scenario: 
			//�V�i���I�I�����
			mScenario->KeyUpdate(Key);
			mScenario->ScenarioAll();
			break;
		case start: {
			//�^�C�g�����
			if (titleStart == false) { titleStart = true; mTitle = new Title_c; }
			titleEnd = mTitle->TitleScreen(Key);
			if (titleEnd == true) { titleEnd = false; titleStart = false; delete mTitle; }
			}
			break;
		case save: {
			//�Z�[�u
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->SaveScreen(Key, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; SaveLoadStart = false; delete mSaveLoad; }
			}
			break;
		case load: {
			//���[�h
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->LoadScreen(Key, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; SaveLoadStart = false; delete mSaveLoad; }
			}
			break;
		case option:
			//�I�v�V����
			if (optionStart == false) { optionStart = true; mOption = new Option_c; }
			optionEnd = mOption->Main(Key);
			if (optionEnd == true) { optionEnd = false; optionStart = false; delete mOption; }
			break;
		}
		break;

	case game:
		switch (GData.GetScene(game)) {
		case dungeon:
			//�_���W�����T��
			mDungeon->KeyUpdate(Key);
			mDungeon->DungeonAll();
			break;
		case room:
			//�����T��
			mRoom->KeyUpdate(Key);
			mRoom->RoomAll();
			break;
		case battle:
			//�o�g��
			battleManager->KeyUpdata(Key);
			battleManager->Update();
			battleManager->Draw();
			break;
		case menu:
			mMenu->KeyUpdate(Key);
			mMenu->MenuAll();
			//���j���[
			break;
		}
		break;
	}

	mEventlist->call();

	//mFps->Draw();	//fps�\��
	mFps->Wait();	//�ҋ@

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