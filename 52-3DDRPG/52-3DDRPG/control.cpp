#include "define.h"

Control_c::Control_c() {
	mEvents = new Event_c;
	mFps = new Fps_c;
	mMenu = new Menu_c();
	mDungeon = new Dungeon_c();
	mRoom = new Room_c();

	GData.LoadAll(0);
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
			DrawFormatString(150, 100, GetColor(255, 255, 255), "�V�i���I�I��"); //�f�o�b�O�p
			break;
		case start: {
			//�^�C�g�����
			if (titleStart == false) { titleStart = true; mTitle = new Title_c; }
			titleEnd = mTitle->TitleScreen(Key);
			if (titleEnd == true) { titleEnd = false; delete mTitle; }
			}
			break;
		case save: {
			//�Z�[�u
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->SaveScreen(Key, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; delete mSaveLoad; }
			}
			break;
		case load: {
			//���[�h
			if (SaveLoadStart == false) { SaveLoadStart = true; mSaveLoad = new SaveLoad_c; }
			SaveLoadEnd = mSaveLoad->LoadScreen(Key, CharX, CharY, Status, 10);
			if (SaveLoadEnd == true) { SaveLoadEnd = false; delete mSaveLoad; }
			}
			break;
		case option:
			//�I�v�V����
			if (optionStart == false) { optionStart = true; mOption = new Option_c; }
			optionEnd = mOption->Main(Key);
			if (optionEnd == true) { optionEnd = false; delete mOption; }
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
			break;
		case menu:
			mMenu->KeyUpdate(Key);
			mMenu->MenuAll();
			//���j���[
			break;
		}
		break;
	}

	mFps->Draw();	//fps�\��
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