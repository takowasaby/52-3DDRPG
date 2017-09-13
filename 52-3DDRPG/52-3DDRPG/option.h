#pragma once

class option_c {
private:
	int BGMVol, SEVol, BattleType, KeyConfig;
	int cursor_posi = 50;
public:
	bool WinMode;
	void Ini();
	void main();
	void backdraw();
	void itemdraw();
	void configdraw();
	void cursor();
	void Fin();
};
