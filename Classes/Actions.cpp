#include "Actions.h"
using namespace std;


auto listener = EventListenerKeyboard::create();


Actions::Actions()
{
}


Actions::~Actions()
{
}

MoveBy * Actions::move_up()
{
	auto move_act = MoveBy::create(2, Point(0, 10));
	return move_act;
}

MoveBy * Actions::move_down()
{
	auto move_act = MoveBy::create(0.5, Point(0, -10));
	return move_act;
}

MoveBy * Actions::move_left()
{
	auto move_act = MoveBy::create(0.5, Point(-10, 0));
	return move_act;
}

MoveBy * Actions::move_right()
{
	auto move_act = MoveBy::create(0.5, Point(10, 0));
	return move_act;
}

bool Actions::init()
{

	return true;
}