#pragma once

#define CommonSEs 4 //���pSE�̑���

class Music_c {
private:
  int ReserveHandle[100][3] = { {} };
  int PlaynowHandle[100] = {};
  int PlayednowHandle[100][2] = { {} };
  int FadeHandle[100][2] = { {} };
  int SaveHandle[100][2] = { {} };

public:
  Music_c();
  ~Music_c();

  const int DECISION = 0;
  const int CANCEL = 1;
  const int CURSOR = 2;
  const int BUZZER = 3;

  int CommonSE[CommonSEs];

  void InitMusic(void);

  void PlaySounds(void); //���ۂɖ炷�֐�(control���ł̂ݎg�p)

  void ReserveSound(int SoundHandle, int PlayType, int FadeFlag = FALSE); //�e�������ōĐ�������֐�
  void StopSound(int SoundHandle, int FadeFlag = FALSE); //�e�������ōĐ����̉����~����֐�
  void PauseSound(int FadeFlag = FALSE); //���ݏ������̂����鉹���~����֐�
  void RestartSound(int FadeFlag = FALSE); //Pause�֐��Œ�~���������Đ�����֐�

};

extern Music_c GMusic;