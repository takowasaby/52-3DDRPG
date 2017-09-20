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
	void loadSE(char SEgain);//効果音読み込み
	void loadBGM(char BGMgain);//BGM読み込み
	void PlayBGM(char BGMgain);//BGM再生：次or他のBGM再生時のための前BGM停止処理を含む　BGM完全停止は読み込まれてない適当な名前を引数に入れる
	void PlaySE(char SEgain);//SE再生：SEを同じSE又は別のSEに重ねられるようになっている
	void SoundFinalize();//全音源のロードアウト
	void BGMvolset(int volume);//設定またはメニューから指定された音量を格納：BGM用
	void SEvolset(int volume);//SE用
	int BGMvol();//個別に音量の値を入手したい時用：BGM用
	int SEvol();//SE用
	//その他、シーン毎に音源読み込みのプリセットがあると便利？
};;

//extern Sound Sound;