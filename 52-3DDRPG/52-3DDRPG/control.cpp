#include "define.h"

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
}

void Control_c::All() {

	UpdateKey();	//�L�[���͂̌��m

	mFps->Update();	//�X�V

	switch (mode) {
	case event:
		switch (event_scene) {
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
		switch (title_scene) {
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
			titleEnd = mTitle->TitleScreen(Key, &title_scene);
			if (titleEnd == true) { titleEnd = false; delete mTitle; }
			}
			break;
		case save:
			//�Z�[�u
			DrawFormatString(150, 100, GetColor(255, 255, 255), "�Z�[�u"); //�f�o�b�O�p
			break;
		case load:
			//���[�h
			DrawFormatString(150, 100, GetColor(255, 255, 255), "���[�h"); //�f�o�b�O�p
			break;
		case option:
			//�I�v�V����
			DrawFormatString(150, 100, GetColor(255, 255, 255), "�I�v�V����"); //�f�o�b�O�p
			break;
		}
		break;

	case game:
		switch (game_scene) {
		case dungeon:
			//�_���W�����T��
			mDungeon->KeyUpdata(Key);
			break;
		case room:
			//�����T��
			break;
		case battle:
			//�o�g��
			break;
		case menu:
			mMenu->KeyUpdata(Key);
			//���j���[
			break;
		}
		break;
	}

	mFps->Draw();	//fps�\��
	mFps->Wait();	//�ҋ@

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