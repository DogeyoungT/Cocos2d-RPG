/*对话框场景类的头文件*/
#ifndef _DIALOG_LAYER_H_
#define _DIALOG_LAYER_H_
#include "cocos2d.h"
#include <stdio.h>

using namespace cocos2d;

class DialogLayer : public CCLayer
{
public:
	bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void setNumber(int);
	int getNumber(int);
	void wordUpdate(float);
	void setDialogBackground(std::string);
	void setDialogist(std::string);
	static DialogLayer * create(std::string);

	// implement the "static create()" method manually

	//CREATE_FUNC(DialogLayer);
private:
	//m_size代表的是对话框背景的大小
	CCSize m_size;
	CCSize winSize;

	int i;
	int dialogNumber = 1;
	CCSprite * m_bgSprite;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};
#endif