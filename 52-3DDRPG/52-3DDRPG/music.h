#pragma once

#define CommonSEs 4 //共用SEの総数

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

  void PlaySounds(void); //実際に鳴らす関数(control下でのみ使用)

  void ReserveSound(int SoundHandle, int PlayType, int FadeFlag = FALSE); //各処理内で再生をする関数
  void StopSound(int SoundHandle, int FadeFlag = FALSE); //各処理内で再生中の音を停止する関数
  void PauseSound(int FadeFlag = FALSE); //現在処理中のあらゆる音を停止する関数
  void RestartSound(int FadeFlag = FALSE); //Pause関数で停止した音を再生する関数

};

extern Music_c GMusic;