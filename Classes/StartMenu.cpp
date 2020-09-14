#include "StartMenu.h"
#include "Load.h"
#include "MyScenes.h"

unsigned int optcounter;
MenuItemImage *item_start;
MenuItemImage *item_load;
MenuItemImage *item_extra;
MenuItemImage *item_option;
MenuItemImage *item_quit;
int menuCounter = 1;

bool StartScene::init()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("kts.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("kts.mp3", true);

	optcounter = 1;
	//log("%d", optcounter);
	if (!Layer::init()) return false;
	auto size = Director::getInstance()->getWinSize();
	auto bgpic = Sprite::create("background.png");
	bgpic->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bgpic);
	item_start = MenuItemImage::create("start_normal.png", "start_selected.png", CC_CALLBACK_1(StartScene::onStart, this));
	item_start->setOpacity(0);
	item_load = MenuItemImage::create("load_normal.png", "load_selected.png", CC_CALLBACK_1(StartScene::onLoad, this));
	item_load->setOpacity(0);
	item_extra = MenuItemImage::create("extra_normal.png", "extra_selected.png", CC_CALLBACK_1(StartScene::onQuit, this));
	item_extra->setOpacity(0);
	item_option = MenuItemImage::create("option_normal.png", "option_selected.png", CC_CALLBACK_1(StartScene::onQuit, this));
	item_option->setOpacity(0);
	item_quit = MenuItemImage::create("quit_normal.png", "quit_selected.png", CC_CALLBACK_1(StartScene::onQuit, this));
	item_quit->setOpacity(0);
	auto optcounterListener = EventListenerKeyboard::create();
	optcounterListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//log("%d", optcounter);
		//CCLOG("keypressed");


		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			//CCLOG("down");
			optcounter += 1;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//CCLOG("up");
			optcounter -= 1;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			if (item_start->isSelected()) item_start->activate();
			else if (item_load->isSelected()) item_load->activate();
			else if (item_extra->isSelected()) item_extra->activate();
			else if (item_option->isSelected()) item_option->activate();
			else if (item_quit->isSelected()) item_quit->activate();

		}
		//log("%d", optcounter);

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(optcounterListener, this);

	auto menu = Menu::create(item_start, item_load, item_extra, item_option, item_quit, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(size.width / 2, size.height / 3));
	addChild(menu);

	schedule(CC_SCHEDULE_SELECTOR(StartScene::menuEffect, 0.5f, 5));
	schedule(CC_SCHEDULE_SELECTOR(StartScene::update));

	return true;

}

void StartScene::menuEffect(float dt)
{
	if (menuCounter == 1)
	{
		item_start->runAction(FadeIn::create(0.5));
		menuCounter++;
	}
	else if (menuCounter == 2)
	{
		item_load->runAction(FadeIn::create(1.0));
		menuCounter++;
	}
	else if (menuCounter == 3)
	{
		item_extra->runAction(FadeIn::create(1.5));
		menuCounter++;
	}
	else if (menuCounter == 4)
	{
		item_option->runAction(FadeIn::create(2.0));
		menuCounter++;
	}
	else if (menuCounter == 5)
	{
		item_quit->runAction(FadeIn::create(2.5));
		menuCounter++;
	}

}

void StartScene::update(float dt)
{

	int n = optcounter % 5;
	if (n == 1)
	{
		item_quit->unselected();
		item_start->selected();
		item_load->unselected();
	}
	else if (n == 2)
	{
		item_start->unselected();
		item_load->selected();
		item_extra->unselected();
	}
	else if (n == 3)
	{
		item_load->unselected();
		item_extra->selected();
		item_option->unselected();
	}
	else if (n == 4)
	{
		item_extra->unselected();
		item_option->selected();
		item_quit->unselected();
	}
	else if (n == 0)
	{
		item_option->unselected();
		item_quit->selected();
		item_start->unselected();
	}

}

void StartScene::onEnter()
{
	CCLOG("StartScene#onEnter");
	Layer::onEnter();
}

void StartScene::onEnterTransitionDidFinish()
{
	CCLOG("StartScene#onEnterTransitionDidFinish");
	Layer::onEnterTransitionDidFinish();
}

void StartScene::onStart(Ref* sender)
{
	auto aScene = new MyScenes;
	auto scene = aScene->create(5);
	Director::getInstance()->pushScene(scene);
}

void StartScene::onLoad(Ref* sender)
{
	auto aScene = new MyScenes;
	auto scene = aScene->create(3);
	Director::getInstance()->pushScene(scene);
	CCLOG("StartScene#onLoad");
}

void StartScene::onQuit(Ref* sender)
{
	Director::getInstance()->popScene();
	//getCocosApp()->quit();
}