#pragma once
#include"cocos2d.h"
#include<string>
using namespace std;

using namespace cocos2d;
class Save {
public:
	double x;
	double y;
    string mapName;
	Save(double Sprite_x, double Sprite_y, string CurrentMap);
	void SaveInFile();

};