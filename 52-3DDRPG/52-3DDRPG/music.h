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

  void PlaySounds(void); //ÀÛ‚É–Â‚ç‚·ŠÖ”(control‰º‚Å‚Ì‚İg—p)
  void ReserveSound(int SoundHandle, int PlayType, int FadeFlag = FALSE); //Šeˆ—“à‚ÅÄ¶‚ğ‚·‚éŠÖ”
  void StopSound(int SoundHandle, int FadeFlag = FALSE); //Šeˆ—“à‚ÅÄ¶’†‚Ì‰¹‚ğ’â~‚·‚éŠÖ”
  void PauseSound(int FadeFlag = FALSE); //Œ»İˆ—’†‚Ì‚ ‚ç‚ä‚é‰¹‚ğ’â~‚·‚éŠÖ”
  void RestartSound(int FadeFlag = FALSE); //PauseŠÖ”‚Å’â~‚µ‚½‰¹‚ğÄ¶‚·‚éŠÖ”

};

extern Music_c GMusic;