#pragma once

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"
#include <string>
using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

class MyScenes : public Scene
{
private:
	string MapName = "dorm_man.tmx";
public:
	MyScenes* create(int testIndex = 1);
	void setMapName(string);
};





