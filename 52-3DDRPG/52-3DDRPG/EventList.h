#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include "ListAction.h"

class Event_c;
class Data_c;

using namespace std;

class EventList
{
public:
	EventList();
	void Initialize(Event_c*);
	void readEvent(string filename);
	void call();
	int  callEvent();
	void setListFileName(int listfile);
	void readList();
	void addList(ListAction la, int num);
	int getCallEventFlag()
	{
		return m_callEventFlag;
	}
	void Event(int num);
private:
	Event_c *m_event;
	Data_c  *m_data;
	int m_flag[128];
	ListAction m_list[128];
	string m_ListFileName;
	queue<string> m_eventfile;
	int m_filelist;
	int m_callEventFlag;
	int m_callBattleFlag;
	int m_scenario;
	int m_eventType;
	int m_active;
};

#endif // EVENTLIST_H