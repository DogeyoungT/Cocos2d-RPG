#pragma once
#include"cocos2d.h"
#include<string>
using namespace std;
using namespace cocos2d;

class Loading {
public:
	int dialogNumber;
	
	Loading();
	double getPositionX();
	double getPositionY();
	string getMapName();
	double x;
	double y;
	string mapName;
};