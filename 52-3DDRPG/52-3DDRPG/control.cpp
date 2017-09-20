#include "define.h"

int Key[256];
void UpdateKey(void);

Control_c::Control_c()
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
	UpdateKey();

	fps->Update();	//�X�V
	fps->Draw();	//fps�\��

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
			break;
		case start: {
			//�^�C�g�����
			Title_c Title;
			Title.TitleScreen(Key);
			delete &Title;
			}
			break;
		case save_load:
			//�Z�[�u�E���[�h
			break;
		case option:
			//�I�v�V����
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

	fps->Wait();	//�ҋ@
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