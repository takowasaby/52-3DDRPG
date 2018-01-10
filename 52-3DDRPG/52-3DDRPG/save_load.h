#pragma once

class TextBox;

class SaveLoad_c {
private:
	int FontTitleMain;

	const int DECISION = 0;
	const int CANCEL = 1;
	const int CURSOR = 2;
	const int BUZZER = 3;

	int TempScreen;

	int Cursor = 0;
	int SE[4];
//	bool first;
	int bright = 0;
	int dataCheck[4] = {};
	int end;

	DATEDATA drawDate[4];
	int drawCount[4][4] = {};

	FILE *sdfp;
/*
	typedef struct {
		int* CharX;
		int* CharY;
		int* Status;
		int StatusNum;
	}OriginData_t;
	
	OriginData_t Origin;
*/
	typedef struct {
	//	int scenario;
		int stage[5] = {};
		int dir[5] = {};
		int room[5] = {};
		int dungeonX[5] = {};
		int	dungeonY[5] = {};
		int flag[5][128] = {};
		int playCount[4];

		DATEDATA dateData;
	}SaveData_t;

	SaveData_t Data;
	TextBox *textBox;

public:
	SaveLoad_c();
	~SaveLoad_c();

	bool SaveScreen(const int*);
	bool LoadScreen(const int*);
	void Save(const int);
	void Load(const int);
	void DeleteData(const int);
	void LoadTime(const int);
	void FileCheck(void);
};

typedef enum {
	CharX,
	CharY,
	Status,
}DataList;