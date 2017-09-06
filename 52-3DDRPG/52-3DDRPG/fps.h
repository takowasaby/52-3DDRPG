#pragma once

#include "define.h"

class Fps_c {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps_c();
	~Fps_c();

	bool Update();

	void Draw();

	void Wait();
};