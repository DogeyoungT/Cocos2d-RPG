#include "GameMenuScene.h"
#include "MapScene.h"
#include "MyScenes.h"
#include "Save.h"

unsigned int game_optcounter;
MenuItemImage *game_item_save;
MenuItemImage *game_item_load;
MenuItemImage *game_item_resume;
MenuItemImage *game_item_option;
MenuItemImage *game_item_quit;
int game_menuCounter;



bool GameMenuScene::init()
{	game_optcounter = 1;
	game_menuCounter = 1;

	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("kts.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("kts.mp3", true);


	//log("%d", game_optcounter);
	if (!Layer::init()) return false;
	auto size = Director::getInstance()->getWinSize();
	auto bgpic = Sprite::create("menu/game_background.jpg");
	bgpic->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(bgpic);	
	game_item_resume = MenuItemImage::create("menu/resume_normal.png", "menu/resume_selected.png", CC_CALLBACK_1(GameMenuScene::onResume, this));
	game_item_resume->setOpacity(0);
	game_item_save = MenuItemImage::create("menu/save_normal.png", "menu/save_selected.png", CC_CALLBACK_1(GameMenuScene::onSave, this));
	game_item_save->setOpacity(0);
	game_item_load = MenuItemImage::create("load_normal.png", "load_selected.png", CC_CALLBACK_1(GameMenuScene::onLoad, this));
	game_item_load->setOpacity(0);
	//game_item_option = MenuItemImage::create("option_normal.png", "option_selected.png", CC_CALLBACK_1(GameMenuScene::onOption, this));
	//game_item_option->setOpacity(0);
	game_item_quit = MenuItemImage::create("quit_normal.png", "quit_selected.png", CC_CALLBACK_1(GameMenuScene::onQuit, this));
	game_item_quit->setOpacity(0);

	auto game_optcounterListener = EventListenerKeyboard::create();
	game_optcounterListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//log("%d", game_optcounter);
		//CCLOG("keypressed");


		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			//CCLOG("down");
			game_optcounter += 1;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//CCLOG("up");
			game_optcounter -= 1;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			if (game_item_save->isSelected()) game_item_save->activate();
			else if (game_item_load->isSelected()) game_item_load->activate();
			else if (game_item_resume->isSelected()) game_item_resume->activate();
			//else if (game_item_option->isSelected()) game_item_option->activate();
			else if (game_item_quit->isSelected()) game_item_quit->activate();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->popScene();
		}
		//log("%d", game_optcounter);

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(game_optcounterListener, this);

	auto game_menu = Menu::create(game_item_resume, game_item_save, game_item_load, game_item_quit, nullptr);
	game_menu->alignItemsVertically();
	game_menu->setPosition(Vec2(size.width / 2, size.height / 3));
	addChild(game_menu);

	schedule(CC_SCHEDULE_SELECTOR(GameMenuScene::menuEffect, 0.5f, 5));
	schedule(CC_SCHEDULE_SELECTOR(GameMenuScene::update));

	return true;

}

void GameMenuScene::menuEffect(float dt)
{	
	if (game_menuCounter == 1)
	{
		game_item_resume->runAction(FadeIn::create(0.5));
		game_menuCounter++;
	}
	else if (game_menuCounter == 2)
	{
		game_item_save->runAction(FadeIn::create(1.0));
		game_menuCounter++;
	}
	else if (game_menuCounter == 3)
	{
		game_item_load->runAction(FadeIn::create(1.5));
		game_menuCounter++;
	}

	//else if (game_menuCounter == 4)
	//{
	//	//game_item_option->runAction(FadeIn::create(2.0));
	//	game_menuCounter++;
	//}
	else if (game_menuCounter == 4)
	{
		game_item_quit->runAction(FadeIn::create(2.0));
		game_menuCounter++;
	}

}



void GameMenuScene::update(float dt)
{

	int n = game_optcounter % 4;
	log(n);
	if (n == 1)
	{
		game_item_resume->selected();
		game_item_save->unselected();
		game_item_quit->unselected();
		game_item_load->unselected();
	}
	else if (n == 2)
	{	
		game_item_resume->unselected();
		game_item_save->selected();
		game_item_load->unselected();
		game_item_quit->unselected();
	}
	else if (n == 3)
	{	
		game_item_resume->unselected();
		game_item_quit->unselected();
		game_item_load->selected();
		game_item_save->unselected();
	}
	else if (n == 0)
	{
		game_item_resume->unselected();
		game_item_load->unselected();
		game_item_save->unselected();
		game_item_quit->selected();
	}


}

void GameMenuScene::onEnter()
{
	CCLOG("GameMenuScene#onEnter");
	Layer::onEnter();
}

void GameMenuScene::onEnterTransitionDidFinish()
{
	CCLOG("GameMenuScene#onEnterTransitionDidFinish");
	Layer::onEnterTransitionDidFinish();
}

void GameMenuScene::onResume(Ref* sender)
{
	Director::getInstance()->popScene();
}

void GameMenuScene::onSave(Ref* sender)
{
	CCLOG("GameMenuScene#Saved");
	Point playerPosition = MapScene::getPos();
	string mapname = MapScene::getMapName();
	Save::Save(playerPosition.x, playerPosition.y, mapname);
	Director::getInstance()->popScene();
}

void GameMenuScene::onLoad(Ref* sender)
{

	Director::getInstance()->popScene();
	auto aScene = new MyScenes;
	auto scene = aScene->create(3);
	
	Director::getInstance()->replaceScene(scene);
	CCLOG("GameMenuScene#onLoad");
}

void GameMenuScene::onQuit(Ref* sender)
{
	Director::getInstance()->popToRootScene();
	//getCocosApp()->quit();
}