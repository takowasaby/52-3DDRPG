#include "define.h"
EventDrawSetting_c::EventDrawSetting_c()
{
	m_x = 100;
	m_y = 100;
	m_turn = 0;
	m_opacity = 255;
	m_dark = 0;
}

EventDrawSetting_c::EventDrawSetting_c(int x,int y,string name,string pictureName,int mode)
{
	//EventDrawSetting_c();
	m_turn = 0;
	m_opacity = 255;
	m_dark = 0;
	setPos(x, y);
	setName(name);
	setPictureName(pictureName);
	setMode(mode);
}

EventDrawSetting_c::~EventDrawSetting_c()
{

}

void EventDrawSetting_c::setSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void EventDrawSetting_c::setSizeWH(int wh,int pictureID)
{
	m_width = wh >> 16;
	m_height = (wh & ((1 << 15) - 1));
	setSize(m_width, m_height, pictureID);
}

void EventDrawSetting_c::setSize(int width, int height, int pictureID)
{

	int nw, nh;
	GetGraphSize(pictureID, &nw, &nh);
	if (width == 0)
	{
		m_width = (int)(1.0f * height / nh * nw);
		m_height = height;
	}
	else if (height == 0)
	{
		m_width = width;
		m_height = (int)(1.0f * height / nw * nh);
	}
	else
	{
		m_width = width;
		m_height = height;
	}
}

void EventDrawSetting_c::setPos(int xy)
{
	m_x = xy >> 16;
	m_y = (xy & ((1 << 15) - 1));
}

void EventDrawSetting_c::setPos(int x, int y)
{
	m_x = x;
	m_y = y;
}

int EventDrawSetting_c::getWidth()
{
	return m_width;
}

int EventDrawSetting_c::getHeight()
{
	return m_height;
}

int EventDrawSetting_c::getX()
{
	return m_x;
}

int EventDrawSetting_c::getY()
{
	return m_y;
}

void EventDrawSetting_c::setTurn(int i)
{
	m_turn = i;
}

int EventDrawSetting_c::getTurn()
{
	return m_turn;
}

void EventDrawSetting_c::setOpacity(int i)
{
	m_opacity = i;
}

int EventDrawSetting_c::getOpacity()
{
	return m_opacity;
}

void EventDrawSetting_c::setName(string name)
{
	m_name = name;
}

string EventDrawSetting_c::getName()
{
	return m_name;
}

void EventDrawSetting_c::setPictureName(string pictureName)
{
	m_pictureName = pictureName;
}

string EventDrawSetting_c::getPictureName()
{
	return m_pictureName;
}

void EventDrawSetting_c::setPictureID(int i)
{
	m_pictureID = i;
}

int EventDrawSetting_c::getPictureID()
{
	return m_pictureID;
}

void EventDrawSetting_c::setMode(int mode)
{
	m_mode = mode;
}

int EventDrawSetting_c::getMode()
{
	return m_mode;
}

void EventDrawSetting_c::setDark(int i)
{
	m_dark = i;
}

int EventDrawSetting_c::getDark()
{
	return m_dark;
}

void EventDrawSetting_c::debugOutput()
{
	printfDx("Name[ x, y, w, h, n, pn, mode, turn, opacity, dark]\n");
	printfDx(" = %s[ %d, %d, %d, %d, %s, %s, %d, %d, %d, %d]\n",m_name.c_str(), m_x, m_y, m_width, m_height, m_name.c_str(), m_pictureName.c_str(), m_mode, m_turn, m_opacity, m_dark);
}