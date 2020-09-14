#include "MyScenes.h"
#include "MapScene.h"
#include "StartMenu.h"
#include "GameMenuScene.h"
#include <string>

void MyScenes::setMapName(string mapName)
{
	this->MapName = mapName;
}

MyScenes* MyScenes::create(int testIndex /* = 1 */)
{
	auto scene = new (std::nothrow) MyScenes;
	if (scene && scene->init())
	{
		scene->autorelease();
		switch (testIndex)
		{
		case 1:
			scene->addChild(StartScene::create());
			break;
		case 2:
		{
			auto myLayer = MapScene::create(this->MapName.c_str(),false);
			//auto size = Director::getInstance()->getWinSize();
			//myLayer->setPosition(Vec2(0, 0));
			scene->addChild(myLayer);
			break; 
		}
		case 3:
		{
			auto myLayer = MapScene::create("default",true);

			scene->addChild(myLayer);
			break;
		}
		case 4:
		{	
			auto GameMenu = GameMenuScene::create();
			scene->addChild(GameMenu);
			break;
		}
		case 5:
		{
			auto myLayer = MapScene::create("dorm_man.tmx", false);
	
			scene->addChild(myLayer);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		delete scene;
		scene = nullptr;
	}

	return scene;
}


