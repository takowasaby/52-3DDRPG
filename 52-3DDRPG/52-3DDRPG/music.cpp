#include "define.h"

Music_c::Music_c() {
}

Music_c::~Music_c() {
  InitSoundMem();
}

void Music_c::InitMusic(void) {
  CommonSE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
  CommonSE[CANCEL] = LoadSoundMem("resource/sounds/SE/common/Cancel2.ogg");
  CommonSE[CURSOR] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
  CommonSE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
  for (int i = 0; i < CommonSEs; ++i) {
    ChangeVolumeSoundMem(64, CommonSE[i]);
  }
}

void Music_c::PlaySounds(void){
  for (int i = 1; i <= FadeHandle[0][0] && i < 100 - 1; ++i) {
    ++FadeHandle[i][1];
    ChangeVolumeSoundMem(FadeHandle[i][1], FadeHandle[i][0]);
    if (FadeHandle[i][1] == 255) {
      memmove(&FadeHandle[i][0], &FadeHandle[i + 1][0], sizeof(int) * (99 - i) * 2);
      --i;
      --FadeHandle[0][0];
    }
  }

  for (int i = 1; i <= ReserveHandle[0][0] && i < 100 - 1; ++i) {
    if (ReserveHandle[i][2] == FALSE) {
      PlaySoundMem(ReserveHandle[i][0], ReserveHandle[i][1]);
      if (ReserveHandle[i][1] == DX_PLAYTYPE_LOOP) {
        PlaynowHandle[i] = ReserveHandle[i][0];
        PlaynowHandle[i] = ReserveHandle[i][1];
        ++PlaynowHandle[0];
      }
    }
    else {
      FadeHandle[FadeHandle[0][0]][0] = ReserveHandle[i][0];
      ++FadeHandle[0][0];
      ChangeVolumeSoundMem(0, ReserveHandle[i][0]);
      PlaySoundMem(ReserveHandle[i][0], ReserveHandle[i][1]);
      if (ReserveHandle[i][1] == DX_PLAYTYPE_LOOP) {
        PlaynowHandle[i] = ReserveHandle[i][0];
        PlaynowHandle[i] = ReserveHandle[i][1];
        ++PlaynowHandle[0];
      }
    }
  }
  memset(&ReserveHandle[0][0], 0, sizeof(ReserveHandle));
}

void Music_c::ReserveSound(int SoundHandle, int PlayType, bool FadeFlag) {
  ++ReserveHandle[0][0];
  ReserveHandle[ReserveHandle[0][0]][0] = SoundHandle;
  ReserveHandle[ReserveHandle[0][0]][1] = PlayType;
  ReserveHandle[ReserveHandle[0][0]][2] = FadeFlag;
}

void Music_c::StopSound(int SoundHandle, bool FadeFlag) {
  StopSoundMem(SoundHandle);
  for (int i = 1; i <= PlaynowHandle[0] && i < 100; ++i) {
    if (SoundHandle == PlaynowHandle[i]) {
      memmove(&PlaynowHandle[i], &PlaynowHandle[i + 1], sizeof(int) * (99 - i) * 2);
      --PlaynowHandle[0];
      break;
    }
  }
}

void Music_c::PauseSound(bool FadeFlag) {
  for (int i = 0; i <= PlaynowHandle[0] && i < 100; ++i) {
    StopSoundMem(PlaynowHandle[i]);
  }
  memcpy(SaveHandle, PlaynowHandle, sizeof(PlaynowHandle));
  memset(PlaynowHandle, 0, sizeof(PlaynowHandle));
}

void Music_c::RestartSound(bool FadeFlag) {
  for (int i = 0; i <= SaveHandle[0][0] && i < 100; ++i) {
    PlaySoundMem(PlaynowHandle[i], DX_PLAYTYPE_LOOP, FALSE);
  }
  memcpy(&PlaynowHandle[PlaynowHandle[0] + 1], &SaveHandle[1][0], sizeof(int) * SaveHandle[0][0] * 2);
  PlaynowHandle[0] += SaveHandle[0][0];
  memset(SaveHandle, 0, sizeof(SaveHandle));
}