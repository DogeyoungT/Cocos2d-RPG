#pragma once
#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"#pragma once

using namespace cocos2d;
using namespace CocosDenshion;

class GameMenuScene : public CCLayer {
public:	
	virtual bool init() override;

	virtual void onEnter() override;

	virtual void onEnterTransitionDidFinish() override;

	void menuEffect(float dt);

	void update(float dt);

	void onResume(cocos2d::Ref* sender);
	void onSave(cocos2d::Ref* sender);
	//void onResume(cocos2d::Ref* sender);
	//void onOption(cocos2d::Ref* sender);
	void onLoad(cocos2d::Ref* sender);
	void onQuit(cocos2d::Ref* sender);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	CREATE_FUNC(GameMenuScene);
};