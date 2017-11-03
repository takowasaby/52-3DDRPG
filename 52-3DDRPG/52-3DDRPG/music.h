#pragma once

class Music_c {
private:
  int ReserveHandle[100][3] = { {} };
  int PlaynowHandle[100][2] = { {} };
  int PlayednowHandle[100][2] = { {} };
  int FadeHandle[100][2] = { {} };
  int SaveHandle[100][2] = { {} };
  int testE;
public:
  Music_c();
  ~Music_c();

  void PlaySounds(void); //���ۂɖ炷�֐�(control���ł̂ݎg�p)
  void ReserveSound(int SoundHandle, int PlayType, int FadeFlag = FALSE); //�e�������ōĐ�������֐�
  void StopSound(int SoundHandle, int FadeFlag = FALSE); //�e�������ōĐ����̉����~����֐�
  void PauseSound(int FadeFlag = FALSE); //���ݏ������̂����鉹���~����֐�
  void RestartSound(int FadeFlag = FALSE); //Pause�֐��Œ�~���������Đ�����֐�

};

extern Music_c GMusic;