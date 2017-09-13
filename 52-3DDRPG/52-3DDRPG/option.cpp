#include "define.h"

void option_c::Ini()
{
	//BGMの音量大小0-5
	//SEの音量大小0-5
	//キーコンフィグ
	//戦闘モード0-3
	//ウィンドウモードtrue or false
	//背景画像、カーソル画像読み込み
}

void option_c::main()
{
	backdraw();	//背景描写
	itemdraw();	//項目描写
	configdraw();	//設定描写
	cursol();	//カーソル
}

void option_c::backdraw()
{
}

void option_c::itemdraw()
{
	//仮置き項目
	DrawFormatString(240, 20, GetColor(255, 255, 255), "OPTION");
	DrawFormatString(40, 50, GetColor(255, 255, 255), "BGM");
	DrawFormatString(40, 90, GetColor(255, 255, 255), "SE");
	DrawFormatString(40, 130, GetColor(255, 255, 255), "KeyConfig");
	DrawFormatString(40, 170, GetColor(255, 255, 255), "BattleMode");
	DrawFormatString(40, 210, GetColor(255, 255, 255), "WindowMode");
}

void option_c::configdraw()
{
}

void option_c::cursol()
{
}

void option_c::Fin()
{
}
