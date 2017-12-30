#include "define.h"
#define ABS(x) (x>0?x:-x)

EventList::EventList():
	m_callEventFlag(0),
	m_scenario(0),
	m_callBattleFlag(0),
	m_eventType(-1),
	m_active(-1)
{
	for (int i = 0; i < 128; i++)
	{
		m_flag[i] = 0;
	}
	m_flag[1] = 1;
}

void EventList::Initialize(Event_c *event)
{
	m_event = event;
	m_active = -1;
}

void EventList::readEvent(string filename)
{
	m_eventfile.push(filename);
}

void EventList::call()
{
	//clsDx();
	if (m_callEventFlag == 1 && !m_callBattleFlag)
	{
		m_callEventFlag = callEvent();
	}
	if (m_callEventFlag != 1 && !m_eventfile.empty())
	{
		m_callEventFlag = 1;
		m_event->readDataFromFile(m_eventfile.front());
		m_eventfile.pop();
	}
	/*
	for (int i = 0; i < 10; i++)
	{
		printfDx("%d:%d\n", i, m_flag[i]);
	}*/
	if(m_active != -1)
		Event(m_eventType);
}

int EventList::callEvent()
{
	return m_event->call();
}

void EventList::setListFileName(int listfile)
{
	m_scenario = listfile;
	string name = "resource/csv/scenario" + to_string(listfile) +"/scenario"+ to_string(listfile) + "_event.csv";
//	printfDx("%s\n", name.c_str());
	m_ListFileName = name;
}

void EventList::readList()
{
	for (int i = 0; i < 128; i++)
	{
		m_flag[i] = 0;
	}
	m_flag[1] = 1;
	signed int  num[64];
	int  count;
	int  counter = 0;
	int eventCount = 0;
	int minasFlag;
	int n;
	ListAction laction;
	Action     action;
	char ch;
	m_filelist = FileRead_open(m_ListFileName.c_str());
	if (m_filelist == NULL)
	{
//		printfDx("read error2\n");
		return;
	}
	//m_list.clear();
	while (FileRead_eof(m_filelist) == 0)
	{
		for (int i = 0; i < 64; i++)
		{
			num[i] = -1;
			if (i >= 30)
				num[i] = 0;
		}
		count = 0;
		minasFlag = 0;
		for (int i = 0; i < 1024; i++)
		{
			ch = FileRead_getc(m_filelist);
			if (ch == '/')
			{
				while (FileRead_getc(m_filelist) != '\n')
				{}
				i = -1;
				continue;
			}
			if (ch == ',')
			{
				//printfDx("%d : %d,", count, num[count]);
				if (minasFlag)
				{
					num[count] *= -1;
				}
				minasFlag = 0;
				count++;
			}
			if (ch >= '0' && ch <= '9')
			{
				if (num[count] == -1)
				{
					num[count] = 0;
				}
				num[count] *= 10;
				n = (int)(ch - '0');
				num[count] += n;
			}
			if (ch == '\n')
			{
				if (minasFlag)
				{
					num[count] *= -1;
				}
				break;
			}
			if (ch == EOF)
			{
				break;
			}
			if (ch == '-')
			{
				//printfDx("minasCame\n");
				minasFlag = 1;
			}
		}
		if (count < 2 || ch == EOF)
			break;
		switch(num[1])
		{
		case 0:
			action.setAction( 0, num[28], num[29], 0, 0);
			break;
		case 1:
			//printfDx("eventadd");
			action.setAction( 1, num[2], 0, 0, 0);
			break;
		case 2:
			action.setAction( 2, num[3], num[4], num[5], num[6]);
			break;
		case 3:
			action.setAction( 3, num[7], num[8], num[9], num[10]);
			break;
		case 4:
			action.setAction( 4, num[11], num[12], num[13], 0);
			break;
		case 5:
			action.setAction( 5, num[14], num[15], num[16], num[17]);
			break;
		case 6:
			action.setAction( 6, num[18], num[19], num[20], num[21]);
			break;
		case 7:
			action.setAction( 7, num[22], num[23], num[24], 0);
			break;
		case 8:
			action.setAction( 8, num[25], 0, 0, 0);
			break;
		case 9:
			action.setAction( 9, num[26], num[27], 0, 0);
			break;
		}
		count = 30;
		while (num[count] != 0 && count < 60)
		{
			//printfDx("%d}", num[count]);
			action.appendFlag(num[count]);
			count ++;
		}

		//action.setAction();
		if (num[0] == -1 || eventCount == num[0])
		{
			laction.addAction(action);
		}
		else
		{
			//printfDx("update\n");
			addList(laction, counter);
			eventCount = num[0];
			laction.reset();
			laction.addAction(action);
			counter++;
		}
		action.reset();
	}
	addList(laction,counter);
	laction.reset();
}

void EventList::addList(ListAction la, int num)
{
	m_list[num] = la;
}

void EventList::Event(int num)
{
	if (m_callEventFlag || m_callBattleFlag)
		return;
	if (m_active == m_list[num].size())
		return;
	int end = 0;
	int i;
	int flag;
	string filename;
	string str;
	if (m_eventType != num)
	{
		if (m_active != -1)
			return;
		m_eventType = num;
		m_active = 0;
	}
	//printfDx("event");
	for (i = m_active; i < m_list[num].size(); i++)
	{
		if (m_list[num].index(i).index(0) <= 9)
		{
			str = "0" + to_string(m_list[num].index(i).index(0));
		}
		else
		{
			str = to_string(m_list[num].index(i).index(0));
		}
		//printfDx("%d : %d\n", num, m_list[num].index(i).getType());
		flag = 1;
		
		for (int j = 0; j < m_list[num].index(i).flagSize(); j++)
		{
			//printfDx("%d,", m_list[num].index(i).getFlag(j));
			if (m_list[num].index(i).getFlag(j) > 0 && m_flag[ABS(m_list[num].index(i).getFlag(j))] == 0)
			{
				flag = 0;
				break;
			}
			if (m_list[num].index(i).getFlag(j) < 0 && m_flag[ABS(m_list[num].index(i).getFlag(j))] == 1)
			{
				flag = 0;
				break;
			}
		}
		//printfDx("\n");
		if(!flag)
		{
			m_active++;
			continue;
		}
		switch (m_list[num].index(i).getType())
		{
		case 0://Flag
			m_flag[ABS(m_list[num].index(i).index(0))] = m_list[num].index(i).index(1);
			GData.SetFlag(ABS(m_list[num].index(i).index(0)), m_list[num].index(i).index(1));
			break;
		case 1://Event
			filename = "resource/text/scenario"+to_string(m_scenario)+"/"+ to_string(m_scenario) + "-" + str + ".txt";
			//printfDx("%s\n", filename.c_str());
			readEvent(filename);
			m_callEventFlag = 2;
			break;
		case 2://Item
			if (m_list[num].index(i).index(2) == -1)
			{
				GData.CalcItemFlag(m_list[num].index(i).index(0), m_list[num].index(i).index(1));
			}
			break;
		case 3://equip
			GData.CalcSoubiFlag(m_list[num].index(i).index(0), m_list[num].index(i).index(1));
			GData.SetCharacterSoubi(m_list[num].index(i).index(2),
				GData.GetSoubiPoint(m_list[num].index(i).index(0), 1),
				m_list[num].index(i).index(0));
			break;
		case 4://chara
			GData.SetCharacterFlag(m_list[num].index(i).index(0), m_list[num].index(i).index(1));
			break;
		case 5://skill
			GData.SetCharacterSkillCode(m_list[num].index(i).index(1),
				m_list[num].index(i).index(0),
				m_list[num].index(i).index(2));
			break;
		case 6://move
			GData.SetDungeonX(m_list[num].index(i).index(0));
			GData.SetDungeonY(m_list[num].index(i).index(1));
			GData.SetStage(m_list[num].index(i).index(3));
			GData.SceneRequest(2, 0);
			break;
		case 7://room
			//m_data->
			GData.SetRoom(m_list[num].index(i).index(0));
			GData.SetStage(m_list[num].index(i).index(2));
			GData.SceneRequest(2, 1);
			break;
		case 8://heel
			for (i = 0; i < CHARACTER_SIZE; i++) 
			{
				GData.SetCharacterStatus(i,
					0,
					GData.GetCharacterStatus(i,0,0),
					1);
			}
			break;
		case 9://scene change
			if (m_list[num].index(i).index(0) == 1)
			{
				GData.SceneRequest(2, 2);
				m_callBattleFlag = 2;
			}
			else if (m_list[num].index(i).index(0) == 2)
			{
				GData.SceneRequest(2, 2);
				m_callBattleFlag = 2;
			}
			break;
		}
		m_active++;
		if (m_callEventFlag || m_callBattleFlag)
			break;
	}
	if (m_active == m_list[num].size())
		m_active = -1;
}
