#include "define.h"
EventChara_c::EventChara_c()
{

}

EventChara_c::EventChara_c(string name) :
	m_name(name)
{

}

EventChara_c::EventChara_c(string name, int direction) :
	m_name(name),
	m_direction(direction)
{

}

EventChara_c::~EventChara_c()
{

}

int EventChara_c::pictureRead(string filename, string pictureName)
{
	int pOnce = LoadGraph(filename.c_str());
	m_picture[pictureName] = pOnce;
	return pOnce;
}

int EventChara_c::getPictureID(string pictureName)
{
	return m_picture[pictureName];
}

void EventChara_c::setID(int n)
{
	m_ID = n;
}

int EventChara_c::getID()
{
	return m_ID;
}

void EventChara_c::setOutName(string name)
{
	m_outName = name;
}

string EventChara_c::getOutName()
{
	return m_outName;
}

map<string, int>* EventChara_c::getPictureMap()
{
	return &m_picture;
}
