#pragma once

class Data_c {
private:
	int scenario;
	int dungeonX, dungeonY;

public:
	Data_c();		//コンストラクタ
	~Data_c();		//デストラクタ

	int GetScenario();
	int GetDungeonX();
	int GetDungeonY();

	void SetScenario(int i);
	void SetDungeonX(int i);
	void SetDungeonY(int i);
};