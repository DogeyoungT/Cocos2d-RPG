#pragma once
#pragma once
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Actions
{
public:
	Actions();
	~Actions();
	EventListenerKeyboard *listener;
	MoveBy *move_up();
	MoveBy *move_down();
	MoveBy *move_left();
	MoveBy *move_right();
	bool init();
};
