#include "Action.h"



Action::Action()
{
}


Action::~Action()
{
}

void Action::setAction(int type, int n1, int n2, int n3, int n4)
{
	m_type = type;
	m_num1 = n1;
	m_num2 = n2;
	m_num3 = n3;
	m_num4 = n4;
}

int Action::getFlag(int i)
{
	return m_flag[i];
}

int Action::flagSize()
{
	return m_flag.size();
}

int Action::index(int i)
{
	int ans = 0;
	switch (i)
	{
	case 0:
		ans = m_num1;
		break;
	case 1:
		ans = m_num2;
		break;
	case 2:
		ans = m_num3;
		break;
	case 3:
		ans = m_num4;
		break;
	}
	return ans;
}

int Action::getType()
{
	return m_type;
}

void Action::reset()
{
	m_flag.clear();
}

void Action::appendFlag(int flag)
{
	m_flag.push_back(flag);
}

