#pragma once

class SaveLoad_c {
private:
	int FontTitleMain;

	const int DECISION = 0;
	const int CANCEL = 1;
	const int CURSOR = 2;
	const int BUZZER = 3;

	int TempScreen;

	int Cursor = 10;
	int SE[4];
	bool first = true;
	int bright = 0;

	FILE *sdfp;

	typedef struct {
		int* CharX;
		int* CharY;
		int* Status;
		int StatusNum;
	}OriginData_t;

	OriginData_t Origin;

	typedef struct {
		int saveCharX;
		int saveCharY;
		int savestatus[13];
	}SaveData_t;

	SaveData_t Data;

public:
	SaveLoad_c();
	~SaveLoad_c();

	bool SaveScreen(const int*, int*, int*, int*, int*, const int);
	bool LoadScreen(const int*, int*, int*, int*, int*, const int);
	void Save(const int, OriginData_t);
	void Load(const int, OriginData_t);
};

typedef enum {
	CharX,
	CharY,
	Status,
}DataList;