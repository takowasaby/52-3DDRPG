#pragma once

#include "define.h"

class Fps_c {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

public:
	Fps_c();
	~Fps_c();

	bool Update();

	void Draw();

	void Wait();
};