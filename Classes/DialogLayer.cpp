/*对话框场景类的具体实现*/
#include "DialogLayer.h"
//#include "QuizLayer.h"
#include <string>
#include <cctype>
#include <stdio.h>


using namespace std;
size_t index = 0;
size_t pos;
size_t index1 = 0;
size_t pos1;
size_t index2 = 0;
size_t pos2;
string s1,s2,ss,ss2;
string object;
string npcName[10];
int quizNumber = 2;
bool endJudge, quizJudge = false;

DialogLayer *DialogLayer::create(string objectName)
{
	auto aLayer = new DialogLayer;
	object = objectName;
	aLayer->init();
	return aLayer;
}

bool DialogLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		this->setTouchEnabled(true);
		bRet = true;
	} while (0);

	//键盘监听
	this->schedule(schedule_selector(DialogLayer::update), 0.1f);
	auto listener = EventListenerKeyboard::create();

	setNumber(1);

	using std::string;
	char *c = ".txt";
	char filename[10];
	//将int i与char *c连接
	sprintf(filename, "%d%s", dialogNumber, c);
	puts(filename);
	log(filename);

	//获得文件在系统的绝对路径
	string filepath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
	log(filepath.c_str());
	//读取的字节数，读取失败则为0
	ssize_t len = 0;
	//读取的内容  
	unsigned char *data = CCFileUtils::sharedFileUtils()->getFileData(filepath.c_str(), "rb", &len);
	string str = (char*)data;

	//添加分隔符号并获取其长度
	const char* delim = ";;";
	const int l = strlen(delim);
	const char* delim1 = "//";
	const int l1 = strlen(delim1);

	//获得对话人物或者道具的名称s1,s2
	pos1 = str.find(delim1, index1);	
	index1 = pos1 + l1;
	//从str中的index1位置开始寻找delim1
	pos1 = str.find(delim1, index1);
	//获取从index1位置开始，长度为pos1 - index1的字符串
	s1 = str.substr(index1, pos1 - index1);

	index1 = pos1 + l1;
	pos1 = str.find(delim1, index1);
	s2 = str.substr(index1, pos1 - index1);
	log(s1.c_str());
	log(s2.c_str());


	npcName[0] = s1;
	npcName[1] = s2;
	for (int j = 2; j < 10; j++) {
		if (npcName[j-1].compare("end") != 0) {
			index1 = pos1 + l;
			pos1 = str.find(delim1, index1);
			npcName[j] = str.substr(index1, pos1 - index1);
		}
		else {
			break;
		}
	}

	//用来判断该npc是否触发Quiz剧情
	for (int j = 0; j < 10; j++) {
		if (npcName[j] == object) {
			quizJudge = true;
		}
	}

	//触发Quiz剧情
	if ((dialogNumber == quizNumber) && (quizJudge)){
		log("Quiz");
		//完成Quiz则进入下一个主线文本
		if (false /*解开谜题*/) {
			dialogNumber = dialogNumber + 1;
		}
		//未完成Quiz则显示相应的固定对话
		else {
			for (int j = 0; j < 10; j++) {
				if (npcName[j] == object) {
					log("match");
					//设置对话框背景
					setDialogBackground("dialog2.png");

					listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
						log("key pressed");
						keys[keyCode] = true;

						if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
							if (!endJudge) {
								//直接找到该name所在的位置
								pos = str.find(object, 0);
								index = pos + object.length();
								pos = str.find(object, index);
								index = pos + object.length();

								pos = str.find(delim, index);
								index = pos + l;
								pos = str.find(delim, index);
								ss = str.substr(index, pos - index);
								setDialogist(ss);

								//截取、显示对话内容
								index = pos + l;
								pos = str.find(delim, index);
								ss = str.substr(index, pos - index);
								DialogLayer::i = 0;
								this->schedule(schedule_selector(DialogLayer::wordUpdate), 0.02f);

								endJudge = true;
							}
							else {
								this->removeChildByTag(2);
								auto nowScene = Director::getInstance()->getRunningScene();
								nowScene->removeChildByTag(2);
							}

						}
					};

				}
			}
		}
		log("end Quiz");
	}

	else {
		log("main dialog");
		//触发主线对话
		log(object.c_str());
		log(s2.c_str());
		//设置对话框背景
		setDialogBackground("dialog2.png");
		if (s2.compare(object)==0) {
			log("main dialog1");
			listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
				log("key pressed");
				keys[keyCode] = true;
				
				pos = str.find(delim, index);
				index = pos + l;
				pos = str.find(delim, index);
				ss = str.substr(index, pos - index);

				if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
					if ((ss.compare("dialog")) == 0) {
						index = pos + l;
						pos = str.find(delim, index);
						ss = str.substr(index, pos - index);
						log(ss.c_str());

						//创建立绘
						auto portrait = Sprite::create(ss + ".png");
						portrait->setTag(3);
						portrait->setAnchorPoint(Vec2(0.5, 0.5));
						//匹配立绘
						if (ss == s1) {
							portrait->setPosition(ccp(winSize.width / 3, winSize.height*0.618));
						}
						else {
							portrait->setPosition(ccp(winSize.width * 5 / 3, winSize.height*0.618));
							//翻转立绘
							portrait->setScaleX(-1.0f);
						}

						//截取、显示对话者
						index = pos + l;
						pos = str.find(delim, index);
						ss = str.substr(index, pos - index);
						setDialogist(ss);


						this->removeChildByTag(3);
						this->addChild(portrait, -1);

						//截取、显示对话内容
						index = pos + l;
						pos = str.find(delim, index);
						ss = str.substr(index, pos - index);
						DialogLayer::i = 0;
						this->schedule(schedule_selector(DialogLayer::wordUpdate), 0.02f);

					}
					else if (ss.compare("close") == 0) {
						index = pos + l;
						pos = str.find(delim, index);

						//存档文本序数
						dialogNumber = dialogNumber + 1;
						getNumber(dialogNumber);

						index = pos + l;
						pos = str.find(delim, index);
						this->removeChildByTag(2);
						this->removeChildByTag(3);
						auto nowScene = Director::getInstance()->getRunningScene();
						nowScene->removeChildByTag(2);
					}
					index = pos + l;
					pos = str.find(delim, index);

					////释放内存  
					//if (len > 0 && data) delete[] data;
				}
			};
		}
		//触发固定对话
		else {
			//设置对话框背景
			setDialogBackground("dialog2.png");

			string filename2 = object + ".txt";
			log(filename2.c_str());
			//获得文件在系统的绝对路径
			string filepath2 = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename2);
			log(filepath2.c_str());
			//读取的字节数，读取失败则为0
			ssize_t len2 = 0;
			//读取的内容
			unsigned char *data2 = CCFileUtils::sharedFileUtils()->getFileData(filepath2.c_str(), "rb", &len2);
			string str2 = (char*)data2;
			log(str2.c_str());

			listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
				log("key pressed");
				keys[keyCode] = true;
				pos2 = str2.find(delim, index2);
				index2 = pos2 + l;
				pos2 = str2.find(delim, index2);
				ss = str2.substr(index2, pos2 - index2);

				if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
					if ((ss.compare("dialog")) == 0) {
						index2 = pos2 + l;
						pos2 = str2.find(delim, index2);
						//创建立绘
						auto portrait = Sprite::create(object + ".png");
						portrait->setTag(3);
						portrait->setAnchorPoint(Vec2(0.5, 0.5));
						portrait->setPosition(ccp(winSize.width / 3, winSize.height*0.618));
						this->removeChildByTag(3);
						this->addChild(portrait, -1);

						//截取、显示对话者
						index2 = pos2 + l;
						pos2 = str2.find(delim, index2);
						ss = str2.substr(index2, pos2 - index2);
						setDialogist(ss);

						//截取、显示对话内容
						index2 = pos2 + l;
						pos2 = str2.find(delim, index2);
						ss = str2.substr(index2, pos2 - index2);

						DialogLayer::i = 0;
						this->schedule(schedule_selector(DialogLayer::wordUpdate), 0.02f);

					}
					else if (ss.compare("close") == 0) {
						this->removeChildByTag(2);
						this->removeChildByTag(3);
						auto nowScene = Director::getInstance()->getRunningScene();
						nowScene->removeChildByTag(2);
					}
					index2 = pos2 + l;
					pos2 = str2.find(delim, index2);
				}
			};
		}
	}

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		log("key release");
		keys[keyCode] = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_bgSprite);

	return bRet;
}



//设置文本序数
void DialogLayer::setNumber(int i) {
	dialogNumber = i;
}

//存档文本序数
int DialogLayer::getNumber(int dialogNumber) {
	return dialogNumber;
}

//设置对话框
void DialogLayer::setDialogBackground(string pictureName) {
	//设置对话框的背景图片
	CCSprite * background = CCSprite::create(pictureName);
	m_bgSprite = background;
	CCSize contentSize = background->getContentSize();
	m_size = contentSize;
	winSize = CCDirector::sharedDirector()->getWinSize();
	m_bgSprite->setScale(1.4);
	m_bgSprite->setScaleY(1.6);
	background->setAnchorPoint(Vec2(0.5, 0));
	background->setPosition(Vec2(winSize.width, winSize.height / 15));
	background->setTag(2);
	this->addChild(background);
}

//显示对话者
void DialogLayer::setDialogist(string ss)
{
	CCLabelTTF * content1 = CCLabelTTF::create(ss + ":", "", 24);
	content1->setAnchorPoint(Vec2(0.5, 0.5));
	content1->setPosition(ccp(m_size.width / 2 + 14, m_size.height / 2 - 7));
	//设置ttf的文本域
	content1->setDimensions(CCSize(this->m_size.width, this->m_size.height));
	//设置ttf的水平对齐方式
	content1->setHorizontalAlignment(kCCTextAlignmentLeft);
	content1->setTag(1);
	m_bgSprite->removeChildByTag(1);
	m_bgSprite->addChild(content1);
}

//刷新，逐字显示文本
void DialogLayer::wordUpdate(float dt)
{
	string subss = ss.substr(0, i);
	CCLabelTTF * content2 = CCLabelTTF::create(subss, "", 20);
	content2->setAnchorPoint(Vec2(0.5, .5));
	content2->setPosition(ccp(m_size.width/2, m_size.height/5)); 
	//设置ttf的文本域
	content2->setDimensions(CCSize(this->m_size.width, this->m_size.height)*0.95);
	//设置ttf的水平对齐方式
	content2->setHorizontalAlignment(kCCTextAlignmentLeft);

	//当长度达到该行文本长度时时结束刷新,取消wordUpdate函数  
	if (i > ss.length()) {
		i = 0;
		this->unschedule(schedule_selector(DialogLayer::wordUpdate));
	}
	else {
		content2->setTag(2);
		m_bgSprite->removeChildByTag(2);
		m_bgSprite->addChild(content2);
		i++;
	}
}

void DialogLayer::menuCloseCallback(Ref* pSender)
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