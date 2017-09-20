#include "define.h"

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
		if (BGMgain != BGMproperty[i].BGMname&&CheckSoundMem(BGMproperty[i].BGM) == 1)StopSoundMem(BGMproperty[i].BGM);
		if (BGMgain == BGMproperty[i].BGMname&&CheckSoundMem(BGMproperty[i].BGM) == 0){
			PlaySoundMem(BGMproperty[i].BGM, DX_PLAYTYPE_LOOP);
			break;
		}
	}
}

void Sound::PlaySE(char SEgain)
{
	SEflag2++;
	for (i = 0; i <= sn; i++)
		if (SEgain == SEproperty[i].SEname&&SEflag=!SEflag2){
		PlaySoundMem(SEproperty[i].SE, DX_PLAYTYPE_BACK);
		SEflag++;
		break;
	}
}

void Sound::SoundFinalize()
{
	StopSoundMem(quest);
}