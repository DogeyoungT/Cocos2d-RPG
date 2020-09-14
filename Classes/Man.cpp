#include "Man.h"



Man::Man()
{
	
}

Man::~Man()
{
}



bool Man::init()
{	
	this->schedule(schedule_selector(Man::update), 0.1f);
	
	("init running");
	hero = Sprite::create("character/hero1.png");
	hero->setAnchorPoint(Point(0.5, 0.5));
	//hero->setScale(0.6);
	//hero->setPosition(Point(320,320));
	this->addChild(hero, 9);
	if (!CCLayer::init()) {
		return false;
	}
	

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		log("key pressed");
		keys[keyCode] = true;
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		log("key release");
		keys[keyCode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool Man::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		log("keycode: %d", &keyCode);
		return true;
	}
	else {
		return false;
	}
}

void Man::update(float delta) {
	Node::update(delta);
	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW, downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (isKeyPressed(leftArrow)) {
		keyPressedDuration(leftArrow);
		hero->setTexture("character/hero2.png");
	}
	else if (isKeyPressed(rightArrow)) {
		keyPressedDuration(rightArrow);
		hero->setTexture("character/hero3.png");
	}
	else if (isKeyPressed(upArrow)) {
		keyPressedDuration(upArrow);
		hero->setTexture("character/hero4.png");
	}
	else if (isKeyPressed(downArrow)) {
		keyPressedDuration(downArrow);
		hero->setTexture("character/hero1.png");
	}
}
void Man::keyPressedDuration(EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX = -32;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX = 32;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY = 32;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY = -32;
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	// 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
	auto moveTo = MoveTo::create(0.2, Point(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
	hero->runAction(moveTo);
	
}



CCPoint Man::getPos() {

	return hero->getPosition();
}

void Man::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}