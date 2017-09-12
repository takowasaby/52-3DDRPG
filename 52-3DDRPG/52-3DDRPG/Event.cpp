#include "define.h"
#include "Event.h"

Event_c::Event_c():
	m_keyBuffer(KEY_INPUT_Z),
	m_keyPushTime(0),
	m_keyPushContinuanceUpper(60),
	m_keyPushed(0),
	m_keyPushContinuanceTempo(10),
	m_keyPushContinuanceFirst(5),
	m_waitingTime(60000),
	m_allend(0)
{
	reset();
}

Event_c::~Event_c()
{

}

void Event_c::keyCheck()
{
	m_keyPushed = 0;
	if (CheckHitKey(m_keyBuffer))
	{
		m_keyPushTime++;
		if (m_keyPushTime == m_keyPushContinuanceFirst)
		{
			m_keyPushed = 1;
		}
		if (m_keyPushTime >= m_keyPushContinuanceUpper)
		{
			if ((m_keyPushTime - m_keyPushContinuanceUpper) % m_keyPushContinuanceTempo == 0)
			{
				m_keyPushed = 1;
			}
		}
	}
	else
	{
		m_keyPushTime = 0;
	}
}

void Event_c::readDataFromFile(string filename)
{
	reset();
	m_filename = filename;
	ifstream reading_file;
	reading_file.open(filename, ios::in);
	string readLineBuffer;
	vector<string> readEach;
	int winW, winH;
	GetWindowSize(&winW, &winH);

	while (!reading_file.eof())
	{
		getline(reading_file, readLineBuffer);
		if (readLineBuffer[0] == '/' && readLineBuffer[1] == '/')
			continue;
		if (readLineBuffer == "")
			continue;
		readEach = splitString(readLineBuffer, ' ');
		if (readEach.at(0) == "addchara")
		{
			addCharacter(readEach.at(1) );
			printfDx("addchara\n");
		}
		else if (readEach.at(0) == "addcharapicture")
		{
			addCharacterPicture(readEach.at(3) , readEach.at(1) , readEach.at(2) );
		}
		else if (readEach.at(0) == "drawrequest")
		{
			if (readEach.size() == 8)
			{
				drawRequest(
					readEach.at(1) ,
					readEach.at(2) ,
					readEach.at(3) ,
					EVENT_MODE_COMPLETE,
					stoi(readEach.at(4) ) * winW / 100,
					stoi(readEach.at(5) ) * winH / 100,
					stoi(readEach.at(6) ) * winW / 100,
					stoi(readEach.at(7) ) * winH / 100);
			}
		}
		else if (readEach.at(0) == "turn")
		{
			addEventAction(readEach.at(1) , EVENT_ACTION_TURN, 0, 0, 0, 0);
		}
		else if (readEach.at(0) == "dark")
		{
			addEventAction(readEach.at(1) , EVENT_ACTION_DARK, 0, 0, 0, 0);
		}
		else if (readEach.at(0) == "light")
		{
			addEventAction(readEach.at(1), EVENT_ACTION_LIGHT, 0, 0, 0, 0);
		}
		else if (readEach.at(0) == "move")
		{
			addEventAction(readEach.at(1) ,
				EVENT_ACTION_POSITION,
				stoi(readEach.at(2) ) * winW / 100,
				stoi(readEach.at(3) ) * winH / 100,
				stoi(readEach.at(4) ) * winW / 100,
				stoi(readEach.at(5) ) * winH / 100,
				stoi(readEach.at(6) ),
				stoi(readEach.at(7) )
			);
		}
		else if (readEach.at(0) == "opacity")
		{
			addEventAction(readEach.at(1),
				EVENT_ACTION_OPACITY,
				stoi(readEach.at(2) ) * winW / 100,
				stoi(readEach.at(3) ) * winH / 100,
				stoi(readEach.at(4) ) * winW / 100,
				stoi(readEach.at(5) ) * winH / 100,
				stoi(readEach.at(6) ),
				stoi(readEach.at(7) )
			);
		}
		else if (readEach.at(0) == "scale")
		{
			addEventAction(readEach.at(1),
				EVENT_ACTION_SCALE,
				stoi(readEach.at(2) ) * winW / 100,
				stoi(readEach.at(3) ) * winH / 100,
				stoi(readEach.at(4) ) * winW / 100,
				stoi(readEach.at(5) ) * winH / 100,
				stoi(readEach.at(6) ),
				stoi(readEach.at(7) )
			);
		}
		else if (readEach.at(0)  == "text")
		{
			addEventAction(readEach.at(1) ,
				EVENT_ACTION_TEXT,
				0,0,0,0,
				m_waitingTime,
				1
				);
		}
		else if (readEach.at(0) == "textclear")
		{
			addEventAction("NULL",
				EVENT_ACTION_TEXTCLEAR,
				0, 0, 0, 0,
				0,0
			);
		}
		else if (readEach.at(0) == "wait")
		{
			if (readEach.size() == 1)
			{
				addEventAction("NULL",
					EVENT_ACTION_WAIT,
					0, 0,
					m_waitingTime, 0
				);
			}
			else if (readEach.size() == 2)
			{
				addEventAction("NULL",
					EVENT_ACTION_WAIT,
					0, 0,
					stoi(readEach.at(1)), 0
				);
			}
		}
		else  if (readEach.at(0) == "end")
		{
			addEventAction("NULL",
				EVENT_ACTION_END,
				0, 0,
				0, 0
			);
		}
		/*
		for (int i = 0; i < readEach.size(); i++)
		{
			printfDx("%s,", readEach.at(i).c_str());
		}
		printfDx("\n");
		*/
		readEach.clear();
	}
}

int Event_c::call()
{
	keyCheck();
	clsDx();
	for (m_elit = m_eventList.begin(); m_elit != m_eventList.end();)
	{
		m_EQPcall = &(*m_elit);
		if (m_drawData.find(m_EQPcall->getName()) != m_drawData.end() &&
			m_EQPcall->getName() != "NULL" &&
			m_EQPcall->getActionType() != EVENT_ACTION_TEXT)
		{
			m_EDScall = &m_drawData[m_EQPcall->getName()];
		}
		if (m_keyPushed)
		{
			m_EQPcall->getLast();
		}
		switch (m_EQPcall->getActionType())
		{
		case EVENT_ACTION_POSITION:
			m_EDScall->setPos(m_EQPcall->getCurrentNumber());
			break;
		case EVENT_ACTION_OPACITY:
			m_EDScall->setOpacity(m_EQPcall->getCurrentNumber());
			break;
		case EVENT_ACTION_SCALE:
			m_EDScall->setSizeWH(m_EQPcall->getCurrentNumber(),m_EDScall->getPictureID());
			break;
		case EVENT_ACTION_TEXT:
			printfDx("comment:\n");
			printfDx("%s\n", m_EQPcall->getName().c_str());
			break;
		case EVENT_ACTION_TURN:
			drawRequestSetDirection(m_EQPcall->getName());
			break;
		case EVENT_ACTION_LIGHT:
			m_EDScall->setDark(0);
			break;
		case EVENT_ACTION_DARK:
			m_EDScall->setDark(1);
			break;
		case EVENT_ACTION_TEXTCLEAR:
			break;
		case EVENT_ACTION_WAIT:
			if(m_EQPcall->getTakeTime() == m_waitingTime)
			{
				printfDx("click Z!\n");
			}
			break;
		case EVENT_ACTION_END:
			m_allend = 1;
			break;
		}
		if (m_allend)
		{
			break;
		}
		if (!m_EQPcall->call())
		{
			if (!m_EQPcall->getAfterOn())
			{
				m_eventList.erase(m_elit);
				break;
			}
			m_elit = m_eventList.erase(m_elit);
			continue;
		}
		if (!m_EQPcall->getAfterOn())
		{
			break;
		}
		m_elit++;
	}
	if (m_allend)
	{
		reset();
		return 0;
	}
	for (m_ddit = m_drawData.begin(); m_ddit != m_drawData.end(); ++m_ddit)
	{
		m_EDScall = &m_ddit->second;
		//m_EDScall->debugOutput();
		switch (m_EDScall->getMode())
		{
		case EVENT_MODE_DEFAULTSIZE:
			drawPicture(m_EDScall->getX(), m_EDScall->getY(), m_charaData[m_EDScall->getName()].getPictureID(m_EDScall->getPictureName()));
			break;
		case EVENT_MODE_RESIZE:
			if(m_EDScall->getTurn() == 1)
				drawExtendPicture(m_EDScall->getX() + m_EDScall->getWidth(), m_EDScall->getY(), -m_EDScall->getWidth(), m_EDScall->getHeight(), m_charaData[m_EDScall->getName()].getPictureID(m_EDScall->getPictureName()));
			else
				drawExtendPicture(m_EDScall->getX(), m_EDScall->getY(), m_EDScall->getWidth(), m_EDScall->getHeight(), m_charaData[m_EDScall->getName()].getPictureID(m_EDScall->getPictureName()));
			break;
		case EVENT_MODE_COMPLETE:
			//printfDx("\n%s:%d", m_EDScall->getName().c_str(), m_EDScall->getOpacity());
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_EDScall->getOpacity());
			if (m_EDScall->getDark())
			{
				//printfDx("darkComing\n");
				SetDrawBright(150, 150, 150);
			}
			if (m_EDScall->getTurn() == 1)
				drawExtendPicture(m_EDScall->getX() + m_EDScall->getWidth(), m_EDScall->getY(), -m_EDScall->getWidth(), m_EDScall->getHeight(), m_charaData[m_EDScall->getName()].getPictureID(m_EDScall->getPictureName()));
			else
				drawExtendPicture(m_EDScall->getX(), m_EDScall->getY(), m_EDScall->getWidth(), m_EDScall->getHeight(), m_charaData[m_EDScall->getName()].getPictureID(m_EDScall->getPictureName()));
			if (m_EDScall->getDark())
			{
				SetDrawBright(255, 255, 255);
			}
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	return 1;
}

int Event_c::addCharacter(string name)
{
	m_charaData[name] = EventChara_c(name);
	m_charaData[name].setID(m_totalID);
	m_totalID ++;
	return m_totalID - 1;
}

int Event_c::addCharacterPicture(string filename, string name, string pictureName)
{
	return m_charaData[name].pictureRead(filename, pictureName)/*returns pictureID*/;
}

int Event_c::addEventAction(string name,int actionType,int from, int to, int takeTime,int afterOn)
{
	m_eventList.push_back(EventQueuePrototype(name, actionType, from, to, takeTime, afterOn));
	return 0;
}

int Event_c::addEventAction(string name, int actionType, int from1,int from2,int to1, int to2, int takeTime, int afterOn)
{
	m_eventList.push_back(EventQueuePrototype(name, actionType, from1 ,from2, to1 ,to2, takeTime, afterOn));
	return 0;
}

int Event_c::drawPicture(int x, int y, int ID)
{
	return DrawGraph(x, y, ID, TRUE);
}

int Event_c::drawExtendPicture(int x, int y, int w, int h, int ID)
{
	return DrawExtendGraph(x, y, x + w, y + h, ID, TRUE);
}

int Event_c::drawRequestSetPos(string drawName, int x, int y)
{
	m_drawData[drawName].setPos(x, y);
	return 0;
}

int Event_c::drawRequestSetSize(string drawName, int width, int height)
{
	m_drawData[drawName].setSize(width, height, m_drawData[drawName].getPictureID());
	return 0;
}

int Event_c::drawRequestSetMode(string drawName, int mode)
{
	m_drawData[drawName].setMode(mode);
	return 0;
}
int Event_c::drawRequestSetName(string drawName, string name, string pictureName)
{
	m_drawData[drawName].setName(name);
	m_drawData[drawName].setPictureName(pictureName);
	m_drawData[drawName].setPictureID(m_charaData[name].getPictureID(pictureName));
	return 0;
}
int Event_c::drawRequestSetDirection(string drawName)
{
	if (m_drawData[drawName].getTurn() == 0)
	{
		m_drawData[drawName].setTurn(1);
	}
	else if (m_drawData[drawName].getTurn() == 1)
	{
		m_drawData[drawName].setTurn(0);
	}
	return 0;
}

int Event_c::drawRequestSetDirection(string drawName,int turn)
{
	m_drawData[drawName].setTurn(turn);
	return 0;
}

int Event_c::drawRequest(string drawName,string name,string pictureName,int mode,int x, int y)
{

	m_drawData[drawName] = EventDrawSetting_c(x, y, name, pictureName, mode);
	m_drawData[drawName].setPictureID(m_charaData[name].getPictureID(pictureName));
	return 0;
}

int Event_c::drawRequest(string drawName, string name, string pictureName, int mode,int x, int y, float size)
{
	int nw, nh;
	m_drawData[drawName] = EventDrawSetting_c(x, y, name, pictureName, mode);
	m_drawData[drawName].setPictureID(m_charaData[name].getPictureID(pictureName));
	GetGraphSize(m_charaData[name].getPictureID(pictureName), &nw, &nh);
	drawRequestSetSize(drawName,(int)(size * nw), (int)(size * nh));
	return 0;
}

int Event_c::drawRequest(string drawName, string name, string pictureName, int mode, int x, int y,int width, int height)
{
	m_drawData[drawName] = EventDrawSetting_c(x, y, name, pictureName, mode);
	m_drawData[drawName].setPictureID(m_charaData[name].getPictureID(pictureName));
	drawRequestSetSize(drawName, width, height);
	return 0;
}

int Event_c::eraseRequest(string drawName)
{
	m_drawData.erase(drawName);
	return 0;
}

int Event_c::eraseAllRequest()
{
	m_drawData.clear();
	return 0;
}

int Event_c::reset()
{
	for (map<string, EventChara_c>::iterator edd = m_charaData.begin(); edd != m_charaData.end(); edd++)
	{
		for (map<string, int>::iterator ed = edd->second.getPictureMap()->begin(); ed != edd->second.getPictureMap()->end(); ed++)
		{
			DeleteGraph(ed->second);
		}
	}
	m_charaData.clear();
	m_drawData.clear();
	m_totalID = 0;
	m_eventList.clear();
	return 0;
}

vector<string> Event_c::splitString(string s, char delim)
{
	vector<string> elems;
	string item;
	for (char ch: s)
	{
		if (ch == delim)
		{
			if (!item.empty())
			{
				elems.push_back(item);
			}
			item.clear();
		}
		else
		{
			item += ch;
		}
	}
	if (!item.empty())
	{
		elems.push_back(item);
	}
	return elems;
}