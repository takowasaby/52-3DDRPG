#include "define.h"

Sound::Sound() 
{
}
Sound::~Sound() 
{
	InitSoundMem();
	bn = 0;
	sn = 0;
}

void Sound::loadBGM(char BGMgain)
{
	BGMproperty[bn].BGM = LoadSoundMem("%c.mp3",BGMgain);
	BGMproperty[bn].BGMname = BGMgain;
	bn++;
}

void Sound::loadSE(char SEgain)
{
	SEproperty[sn].SE = LoadSoundMem("%c.mp3", SEgain);
	SEproperty[sn].SEname = SEgain;
	sn++;
}

void Sound::PlayBGM(char BGMgain)
{
	for (i = 0; i <= bn; i++){
		if (BGMgain != BGMproperty[i].BGMname && CheckSoundMem(BGMproperty[i].BGM) == 1)StopSoundMem(BGMproperty[i].BGM);
		if (BGMgain == BGMproperty[i].BGMname && CheckSoundMem(BGMproperty[i].BGM) == 0){
			PlaySoundMem(BGMproperty[i].BGM, DX_PLAYTYPE_LOOP);
			ChangeVolumeSoundMem(255 * BGMvolume / 100, BGMproperty[i].BGM);
			break;
		}
	}
}

void Sound::PlaySE(char SEgain)
{
	for (i = 0; i <= sn; i++){
		if (SEgain == SEproperty[i].SEname) {
		    PlaySoundMem(SEproperty[i].SE, DX_PLAYTYPE_BACK);
			ChangeVolumeSoundMem(255 * SEvolume / 100, SEproperty[i].SE);
			break;
		}
	}
}

void Sound::SoundFinalize()
{
	InitSoundMem();
	bn = 0;
	sn = 0;
}

void Sound::BGMvolset(int volume) 
{
	volume = BGMvolume;
}

void Sound::SEvolset(int volume)
{
	volume = SEvolume;
}

int Sound::BGMvol() 
{
	return BGMvolume;
}

int Sound::SEvol()
{
	return SEvolume;
}