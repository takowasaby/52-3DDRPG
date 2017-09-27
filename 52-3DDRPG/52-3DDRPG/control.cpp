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

	UpdateKey();	//�L�[���͂̌��m

	fps->Update();	//�X�V

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
			if (titleStart == false) { titleStart = true; Title = new Title_c; }
			titleEnd = Title->TitleScreen(Key, &title_scene);
			if (titleEnd == true) { titleEnd = false; delete Title; }
			}
			break;
		case save_load:
			//�Z�[�u�E���[�h
			DrawFormatString(150, 100, GetColor(255, 255, 255), "�Z�[�u����[�h"); //�f�o�b�O�p
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
			break;
		case room:
			//�����T��
			break;
		case battle:
			//�o�g��
			break;
		case menu:
			//���j���[
			break;
		}
		break;
	}

	fps->Draw();	//fps�\��
	fps->Wait();	//�ҋ@
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