#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <iostream>
#include <string>
#include <vector>
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
	int callEvent();
	void setListFileName(string listfile);
	void readList();
	void addList(ListAction la, int num);
	void Event(int num);
private:
	Event_c *m_event;
	Data_c  *m_data;
	int m_flag[128];
	ListAction m_list[128];
	string m_ListFileName;
	int m_filelist;
	int m_callEventFlag;
};

#endif // EVENTLIST_H