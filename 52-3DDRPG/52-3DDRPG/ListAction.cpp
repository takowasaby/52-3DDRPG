#include "ListAction.h"



ListAction::ListAction()
{
	pos = 0;
}


ListAction::~ListAction()
{
}

void ListAction::addAction(Action act)
{
	m_actions[pos] = act;
	pos++;
}

Action ListAction::index(int i)
{
	return m_actions[i];
}

int ListAction::size()
{
	return pos;
}

void ListAction::reset()
{
	pos = 0;
}
