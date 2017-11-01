#pragma once
#include <vector>
#include "Action.h"

using namespace std;

class ListAction
{
private:
	Action m_actions[128];
	int pos;
public:
	ListAction();
	~ListAction();
	void addAction(Action act);
	Action index(int i);
	int size();
	void reset();
};

