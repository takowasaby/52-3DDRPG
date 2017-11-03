#include "define.h"

EventQueuePrototype::EventQueuePrototype()
{

}

EventQueuePrototype::EventQueuePrototype(string name, int actionType, int from, int to, int takeTime, int afterOK)
{
	m_name = name;
	m_actionType = actionType;
	m_fromNumber = from;
	m_toNumber = to;
	m_takeTime = takeTime;
	m_currentTime = 0;
	m_afterOn = afterOK;
}

EventQueuePrototype::EventQueuePrototype(string name, int actionType, int from1, int from2, int to1, int to2, int takeTime, int afterOK)
{
	m_name = name;
	m_actionType = actionType;
	m_fromNumber = from1;
	m_fromNumber2 = from2;
	m_toNumber = to1;
	m_toNumber2 = to2;
	m_takeTime = takeTime;
	m_currentTime = 0;
	m_afterOn = afterOK;
}

string EventQueuePrototype::getName()
{
	return m_name;
}

int EventQueuePrototype::getActionType()
{
	return m_actionType;
}

int EventQueuePrototype::getCurrentNumber()
{
	long long int number = 0;
	if (m_takeTime == 0)
	{
		return m_toNumber;
	}
	if (m_actionType & (EVENT_ACTION_POSITION | EVENT_ACTION_SCALE)) 
	{
		long long int n1 = (((m_fromNumber*(m_takeTime - m_currentTime)) + (m_toNumber*m_currentTime)) / m_takeTime);
		long long int n2 = (((m_fromNumber2*(m_takeTime - m_currentTime)) + (m_toNumber2*m_currentTime)) / m_takeTime);
		number = ((n1 << 16) | n2);
	}
	else
	{
		number = (((m_fromNumber*(m_takeTime - m_currentTime)) + (m_toNumber*m_currentTime)) / m_takeTime);
	}
	return (int)number;
}

int EventQueuePrototype::getAfterOn()
{
	return m_afterOn;
}

int EventQueuePrototype::call()
{
	m_currentTime++;
	if (m_currentTime > m_takeTime)
	{
		return 0;
	}
	return m_currentTime;
}

int EventQueuePrototype::getLast()
{
	m_currentTime = m_takeTime;
	return 0;
}

int EventQueuePrototype::getTakeTime()
{
	return m_takeTime;
}