#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

class EventDrawSetting_c
{
private:
	int m_x, m_y;
	int m_width, m_height;
	int m_opacity;

	int m_oncex, m_oncey;
	int m_onceWidth, m_onceHeight;
	int m_onceOpacity;

	string m_name;
	string m_pictureName;
	int m_pictureID;
	int m_mode;
	int m_turn;
	int m_dark;
public:
	EventDrawSetting_c();
	EventDrawSetting_c(int x, int y, string name, string pictureName,int mode);
	~EventDrawSetting_c();

	void setSizeWH(int wh, int pictureID);
	void setSize(int width, int height);
	void setSize(int width, int height, int pictureID);
	void setPos(int xy);
	void setPos(int x, int y);
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	void setTurn(int i);
	int getTurn();
	void setOpacity(int i);
	int getOpacity();
	void setName(string name);
	string getName();
	void setPictureName(string pictureName);
	string getPictureName();
	void setPictureID(int i);
	int getPictureID();
	void setMode(int mode);
	int getMode();
	void setDark(int i);
	int getDark();
	void debugOutput();
};
