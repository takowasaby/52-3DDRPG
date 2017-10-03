#pragma once

class option_c {
private:
	int BGMVol, SEVol, BattleType, KeyConfig;
public:
	bool WinMode;
	void Ini();
	void main();
	void backdraw();
	void itemdraw();
	void configdraw();
	void cursol();
	void Fin();
};
