#pragma once
#include <vector>

using namespace std;

class Action
{
private:
	int m_type;
	int m_num1;
	int m_num2;
	int m_num3;
	int m_num4;
	vector<int> m_flag;
public:
	Action();
	~Action();
	void setAction(int type, int n1, int n2, int n3, int n4);
	int getFlag(int i);
	int flagSize();
	int index(int i);
	int getType();
	void reset();
	void appendFlag(int flag);
};

