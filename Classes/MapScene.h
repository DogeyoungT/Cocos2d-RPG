#pragma once
#include "cocos2d.h"
#include "dialogLayer.h"

#include "audio/include/SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class MapScene : public CCLayer {


public:

	bool init();

	Point tileCoordForPosition(Point position);
	void setViewPointCenter(Point position);

	void update_view(float delta);
	void update(float delta) override;

	void setPlayerPosition(Point position);

	bool isKeyPressed(EventKeyboard::KeyCode);
	void keyPressedDuration(EventKeyboard::KeyCode);
	void menuCloseCallback(cocos2d::Ref* pSender);

	static CCPoint getPos();
	static const char* getMapName();
	static MapScene* create(const char*,bool ifLoad);

	//CREATE_FUNC(MapScene);

	//void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	//void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

};
