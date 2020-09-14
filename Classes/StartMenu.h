#pragma once

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"#pragma once

using namespace cocos2d;
using namespace CocosDenshion;

class StartScene : public CCLayer {
public:
	CREATE_FUNC(StartScene);
	virtual bool init() override;


	virtual void onEnter() override;

	virtual void onEnterTransitionDidFinish() override;

	void menuEffect(float dt);
	void update(float dt);
	void onStart(cocos2d::Ref* sender);
	void onQuit(cocos2d::Ref* sender);
	void onLoad(cocos2d::Ref* sender);
};