#pragma once

class Sound {
private:
	int bn = 0;
	int sn = 0;
	int i;
	int BGMvolume = 100;
	int SEvolume = 100;

	typedef struct {
		int BGM;
		char BGMname;
	} BGM;
	BGM BGMproperty[5];//�ǂݍ��߂�BGM�͂T�܂�

	typedef struct {
		int SE;
		char SEname;
	} SE;
	SE SEproperty[20];//�ǂݍ��߂�SE�͂Q�O�܂�
public:
	Sound();
	~Sound();
	void loadSE(char SEgain);//���ʉ��ǂݍ��� SEgain�ɓǂݍ��݂����t�@�C�����imp3�̃t�@�C���A�t�@�C�����w���mp3�͂���Ȃ��j
	void loadBGM(char BGMgain);//BGM�ǂݍ��݁@ BGMgain�ɓǂݍ��݂����t�@�C�����imp3�̃t�@�C���A�t�@�C�����w���mp3�͂���Ȃ��j
	void PlayBGM(char BGMgain);//BGM�Đ��F��or����BGM�Đ����̂��߂̑OBGM��~�������܂ށi�V���Ƀt�@�C�����w�肷��ΑO��BGM�͎~�܂�j
							   //�K���Ƀ��[�v�ɕ��荞��ł��@�\����͂�
							   //BGM���S��~���͓ǂݍ��܂�ĂȂ��K���Ȗ��O�inull�Ƃ��j�������ɓ����
	void PlaySE(char SEgain);//SE�Đ��@����ȏ����Ȃ�
	void SoundFinalize();//�S�����̃��[�h�A�E�g�@�V�[���؂�ւ����̃V�[���I�������̂Ƃ���
	void BGMvolset(int volume);//�ݒ�܂��̓��j���[����w�肳�ꂽ���ʂ��i�[�FBGM�p
	void SEvolset(int volume);//SE�p
	int BGMvol();//�ʂɉ��ʂ̒l����肵�������p�@���ʂ�Ԃ��܂��FBGM�p
	int SEvol();//�ʂɉ��ʂ̒l����肵�������p�@���ʂ�Ԃ��܂��F�p
				//���̑��A�V�[�����ɉ����ǂݍ��݂̃v���Z�b�g������ƕ֗��H
};;

//extern Sound Sound;#pragma once
