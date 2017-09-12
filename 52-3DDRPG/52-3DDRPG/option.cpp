#include "define.h"

void option_c::Ini()
{

}

void option_c::main()
{
	backdraw();
	itemdraw();
	configdraw();
	cursol();
}

void option_c::backdraw()
{
}

void option_c::itemdraw()
{
}

void option_c::configdraw()
{
	DrawFormatString(240, 20, GetColor(255, 255, 255), "OPTION");
	DrawFormatString(40, 50, GetColor(255, 255, 255), "BGM");
	DrawFormatString(40, 90, GetColor(255, 255, 255), "SE");
	DrawFormatString(40, 130, GetColor(255, 255, 255), "KeyConfig");
	DrawFormatString(40, 170, GetColor(255, 255, 255), "BattleMode");
	DrawFormatString(40, 210, GetColor(255, 255, 255), "WindowMode");
}

void option_c::cursol()
{
}

void option_c::Fin()
{
}
