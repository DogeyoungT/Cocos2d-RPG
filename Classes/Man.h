#pragma once
#include "cocos2d.h"
#include "Actions.h"

using namespace std;
USING_NS_CC;
extern Sprite *hero;
class Man : public Layer
{
	
public:
	Man();
	~Man();
	virtual bool init();
	void update(float delta) override;
	bool isKeyPressed(EventKeyboard::KeyCode);
	void keyPressedDuration(EventKeyboard::KeyCode);
	void menuCloseCallback(cocos2d::Ref* pSender);
	CCPoint getPos();

	// implement the "static create()" method manually
	CREATE_FUNC(Man);
private:
	bool isJumping;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	// DEFAULT anchor point for all Sprites


};