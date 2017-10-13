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
	BGM BGMproperty[5];//読み込めるBGMは５つまで

	typedef struct {
		int SE;
		char SEname;
	} SE;
	SE SEproperty[20];//読み込めるSEは２０まで
public:
	Sound();
	~Sound();
	void loadSE(char SEgain);//効果音読み込み SEgainに読み込みたいファイル名（mp3のファイル、ファイル名指定にmp3はいらない）
	void loadBGM(char BGMgain);//BGM読み込み　 BGMgainに読み込みたいファイル名（mp3のファイル、ファイル名指定にmp3はいらない）
	void PlayBGM(char BGMgain);//BGM再生：次or他のBGM再生時のための前BGM停止処理を含む（新たにファイルを指定すれば前のBGMは止まる）
							   //適当にループに放り込んでも機能するはず
							   //BGM完全停止時は読み込まれてない適当な名前（nullとか）を引数に入れる
	void PlaySE(char SEgain);//SE再生　特殊な処理なし
	void SoundFinalize();//全音源のロードアウト　シーン切り替え時のシーン終了処理のときに
	void BGMvolset(int volume);//設定またはメニューから指定された音量を格納：BGM用
	void SEvolset(int volume);//SE用
	int BGMvol();//個別に音量の値を入手したい時用　音量を返します：BGM用
	int SEvol();//個別に音量の値を入手したい時用　音量を返します：用
				//その他、シーン毎に音源読み込みのプリセットがあると便利？
};;

//extern Sound Sound;#pragma once
