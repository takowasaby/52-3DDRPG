#pragma once
#include <string>
#include <iostream>
#include <map>

using namespace std;

class EventChara_c
{
private:
	int m_ID;
	string m_name;
	map<string, int> m_picture;
	int m_direction;
public:
	EventChara_c();
	EventChara_c(string name);
	~EventChara_c();
	int pictureRead(string filename, string pictureName);
	int getPictureID(string pictureName);
	void setID(int n);
	int  getID();
	map<string, int>* getPictureMap();
};