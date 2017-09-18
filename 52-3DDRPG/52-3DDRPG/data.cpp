#include "define.h"

Data_c::Data_c()
{
}

Data_c::~Data_c()
{
}

void Data_c::LoadAll(int scenario)
{
	ItemLoad(scenario);
	SoubiLoad(scenario);
	SkillLoad(scenario);
	CharacterLoad(scenario);
}

void Data_c::ItemLoad(int scenario)
{
}

void Data_c::SoubiLoad(int scenario)
{
}

void Data_c::SkillLoad(int scenario)
{
}

void Data_c::CharacterLoad(int scenario)
{
}

int Data_c::GetScenario()
{
	return scenario;
}

int Data_c::GetDungeonX()
{
	return dungeonX;
}

int Data_c::GetDungeonY()
{
	return dungeonY;
}

void Data_c::SetScenario(int i)
{
	scenario = i;
}

void Data_c::SetDungeonX(int i)
{
	dungeonX = i;
}

void Data_c::SetDungeonY(int i)
{
	dungeonY = i;
}
