#pragma once
#include "define.h"

#include "ECharaData.h"
#include "EDrawSetting.h"
#include "EQueueData.h"
#include <vector>
#include <map>
#include <string>
#include <list>
#include <fstream>

class TextBox;

using namespace std;

class Event_c
{
private:
	string m_filename;
	EventDrawSetting_c *m_EDScall;
	EventQueuePrototype *m_EQPcall;
	map<string, EventChara_c> m_charaData;
	map<string, EventDrawSetting_c> m_drawData;
	map<string, EventDrawSetting_c>::iterator m_ddit;
	list<EventQueuePrototype> m_eventList;
	list<EventQueuePrototype>::iterator m_elit;
	int m_totalID;
	int m_waitingTime;
	int m_allend;

	int m_keyBuffer;
	int m_keyPushTime;
	int m_keyPushContinuanceUpper;
	int m_keyPushed;
	int m_keyPushContinuanceTempo;
	int m_keyPushContinuanceFirst;

	TextBox *textBox;
public:
	Event_c();
	~Event_c();
	void keyCheck();
	void readDataFromFile(string filename);
	int call();
	int addCharacter(string name);//“oê‚·‚éƒLƒƒƒ‰ƒNƒ^[–¼‚Ì“o˜^
	int addCharacterPicture(string filename, string name, string pictureName);//“oê‚·‚éƒLƒƒƒ‰ƒNƒ^[–¼‚É‘Î‰‚·‚é‰æ‘œ‚Ì“o˜^
	int addEventAction(string name, int actionType, int from, int to, int takeTime, int afterOn);
	int addEventAction(string name, int actionType, int from1, int from2, int to1, int to2, int takeTime, int afterOn);
	int drawPicture(int x, int y, int ID);
	int drawExtendPicture(int x, int y, int w, int h, int ID);
	int drawRequestSetPos(string drawName, int x, int y);
	int drawRequestSetSize(string drawName, int width, int height);
	int drawRequestSetMode(string drawName, int mode);
	int drawRequestSetName(string drawName, string name, string pictureName);
	int drawRequestSetDirection(string drawName);
	int drawRequestSetDirection(string drawName, int turn);
	int drawRequest(string drawName, string name, string pictureName, int mode, int x, int y);
	int drawRequest(string drawName, string name, string pictureName, int mode, int x, int y, float size);
	int drawRequest(string drawName, string name, string pictureName, int mode, int x, int y,int width,int height);
	int eraseRequest(string drawName);
	int eraseAllRequest();
	int reset();

	vector<string> splitString(string s, char delim);
};

