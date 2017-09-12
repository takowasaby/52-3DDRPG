#pragma once
#include <string>

class EventQueuePrototype
{
private:
	string m_name;
	int m_actionType;
	int m_fromNumber;
	int m_fromNumber2;
	int m_toNumber;
	int m_toNumber2;
	int m_takeTime;
	int m_currentTime;
	int m_afterOn;
public:
	EventQueuePrototype(string name, int actionType, int from, int to, int takeTime, int afterOK);
	EventQueuePrototype(string name, int actionType, int from1, int from2, int to1, int to2, int takeTime, int afterOK);
	string getName();
	int getActionType();
	int getCurrentNumber();
	int getAfterOn();
	int call();
	int getLast();
	int getTakeTime();
};