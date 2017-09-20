#pragma once

class Sound {
private:
	int bn = 0;
	int sn = 0;
	int i;
	int SEflag = 0;
	int SEflag2 = 0;
	int BGMvolume, SEvolume;
	typedef struct {
		int BGM;
		char BGMname;
	} BGM;
	BGM BGMproperty[5];

	typedef struct {
		int SE;
		char SEname;
	} SE;
	SE SEproperty[20];
public:
	void loadSE(char SEgain);//���ʉ��ǂݍ���
	void loadBGM(char BGMgain);//BGM�ǂݍ���
	void PlayBGM(char BGMgain);//BGM�Đ��F��or����BGM�Đ����̂��߂̑OBGM��~�������܂ށ@BGM���S��~�͓ǂݍ��܂�ĂȂ��K���Ȗ��O�������ɓ����
	void PlaySE(char SEgain);//SE�Đ��FSE�𓯂�SE���͕ʂ�SE�ɏd�˂���悤�ɂȂ��Ă���
	void SoundFinalize();//�S�����̃��[�h�A�E�g
	void BGMvolset(int volume);//�ݒ�܂��̓��j���[����w�肳�ꂽ���ʂ��i�[�FBGM�p
	void SEvolset(int volume);//SE�p
	int BGMvol();//�ʂɉ��ʂ̒l����肵�������p�FBGM�p
	int SEvol();//SE�p
	//���̑��A�V�[�����ɉ����ǂݍ��݂̃v���Z�b�g������ƕ֗��H
};;

//extern Sound Sound;