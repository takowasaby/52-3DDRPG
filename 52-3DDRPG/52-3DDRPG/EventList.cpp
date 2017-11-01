#include "define.h"
#define ABS(x) (x>0?x:-x)

EventList::EventList():
	m_callEventFlag(0)
{
	for (int i = 0; i < 128; i++)
	{
		m_flag[i] = 0;
	}
}

void EventList::Initialize(Event_c *event)
{
	m_event = event;
}

void EventList::readEvent(string filename)
{
	m_event->readDataFromFile(filename);
}

void EventList::call()
{
	//clsDx();
	if (m_callEventFlag == 1)
	{
		m_callEventFlag = callEvent();
	}
	for (int i = 0; i < 3; i++)
	{
		//printfDx("%d:%d\n", i, m_flag[i]);
	}
}

int EventList::callEvent()
{
	return m_event->call();
}

void EventList::setListFileName(string listfile)
{
	m_ListFileName = listfile;
}

void EventList::readList()
{
	signed int  num[64];
	int  count;
	int  counter = 0;
	int eventCount = 0;
	int minasFlag;
	int n;
	ListAction laction;
	Action     action;
	char ch;
	//m_filelist = FileRead_open(m_ListFileName.c_str());
	m_filelist = FileRead_open("resource/data/eventlist.csv");

	if (m_filelist == NULL)
	{
		printfDx("read error2\n");
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
				printfDx("minasCame\n");
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
			printfDx("%d}", num[count]);
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
			printfDx("update\n");
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
	int i;
	int flag;
	string filename;
	for (int i = 0; i < m_list[num].size(); i++)
	{
		printfDx("%d : %d\n", num, m_list[num].index(i).getType());
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
		printfDx("\n");
		if(!flag)
		{
			continue;
		}
		switch (m_list[num].index(i).getType())
		{
		case 0://Flag
			m_flag[ABS(m_list[num].index(i).index(0))] = m_list[num].index(i).index(1);
			break;
		case 1://Event
			
			m_callEventFlag = 1;
			filename = "resource/text/event-" +to_string(m_list[num].index(i).index(0)) + ".txt";
			printfDx("%s\n", filename.c_str());
			readEvent(filename);
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
			break;
		case 6://move
			GData.SetDungeonX(m_list[num].index(i).index(0));
			GData.SetDungeonY(m_list[num].index(i).index(1));
			break;
		case 7://room
			//m_data->
			GData.SetRoom(m_list[num].index(i).index(0));
			GData.SetStage(m_list[num].index(i).index(2));
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
			break;
		}
	}
}
