#include "MapScene.h"
#include "MyScenes.h"
#include "GameMenuScene.h"
#include "Load.h"
#include "Save.h"
#include <string>

Sprite *hero;
TMXTiledMap *myMap;
TMXLayer *_meta;
TMXLayer *_door;
Layer *layer;
int MoveCounter = 0;
int heroFace = 2;
const char *MapName;

CCPoint MapScene::getPos() {
	return hero->getPosition();
}

const char* MapScene::getMapName()
{
	return MapName;
}

//string MapScene::getMapName()
//{
//	//return MapName;
//}

MapScene* MapScene::create(const char* mapName,bool ifLoad) {
	MapName = mapName;
	if (ifLoad) {
		Loading loadfile;	
		int x = loadfile.x;
		int y = loadfile.y;
		log("loaded");
		mapName = loadfile.mapName.c_str();
		log(mapName);
		log("loaded mapname");
		log(loadfile.mapName.c_str());
		auto MapLayer = new (std::nothrow) MapScene;
		MapLayer->init();
		myMap = TMXTiledMap::create(mapName);
		myMap->setAnchorPoint(Vec2(0.5, 0.5));
		CCSize visibleSize = CCDirector::getInstance()->getWinSize();
		myMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

		//myMap->setPosition(Point(0, 0)); 
		//myMap->setAnchorPoint(Point(0, 0));

		//TMXObjectGroup *objects = myMap->getObjectGroup("Objects");
		//auto spawnPoint = objects->getObject("SpawnPoint");
		
		//auto door = objects->getObject("Door");

		MapLayer->addChild(myMap);
		_meta = myMap->getLayer("Meta");
		_meta->setVisible(false);

		_door = myMap->getLayer("Door");
		_door->setVisible(false);

		hero = Sprite::create("character/hero1.png");
		hero->setAnchorPoint(Point(0.5, 0.5));
		//hero->setScale(0.6);
		/*hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));*/
		hero->setPosition(x, y);
		myMap->addChild(hero, 4);
		return MapLayer;
	}

	else {
		auto MapLayer = new (std::nothrow) MapScene;
		MapLayer->init();
		myMap = TMXTiledMap::create(mapName);
		myMap->setAnchorPoint(Vec2(0.5, 0.5));
		CCSize visibleSize = CCDirector::getInstance()->getWinSize();
		myMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

		//myMap->setPosition(Point(0, 0));
		//myMap->setAnchorPoint(Point(0, 0));

		TMXObjectGroup *objects = myMap->getObjectGroup("Objects");

		auto spawnPoint = objects->getObject("SpawnPoint");
		int x = spawnPoint["x"].asInt();
		int y = spawnPoint["y"].asInt();

		MapLayer->addChild(myMap);

		_meta = myMap->getLayer("Meta");
		_meta->setVisible(false);

		_door = myMap->getLayer("Door");
		_door -> setVisible(false);

		hero = Sprite::create("character/hero1.png");
		hero->setAnchorPoint(Point(0.5, 0.5));
		//hero->setScale(0.6);
		/*hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));*/

		hero->setPosition(x, y);
		myMap->addChild(hero, 4);
		return MapLayer;
	}	
}

bool MapScene::init() {
	if (CCLayer::init())
	{
		CCLOG("init");
		this->schedule(schedule_selector(MapScene::update), 0.11f);
		//this->schedule(schedule_selector(MapScene::update_view), 0.005f);

		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("odk.mp3");
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("odk.mp3", true);
		CCLOG("bgm ready");
		
		CCSize visibleSize = CCDirector::getInstance()->getWinSize();

		this->setPosition(Point(0,0));

				//myScene = Scene::create();
		//myScene->addChild(this);

		//_meta = myMap->getLayer("Meta");
		//_meta->setVisible(false);

		//this->addChild(myMap);

		//log("init running");
		auto game_optcounterListener = EventListenerKeyboard::create();
		game_optcounterListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
		{
			if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
			{
				auto aScene = new MyScenes;
				MyScenes *gameMenu = aScene->create(4);
				//auto scene = MyScenes::create(4);	
				Director::getInstance()->pushScene(gameMenu);
			}
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(game_optcounterListener, this);

		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			//log("key pressed");
			keys[keyCode] = true;
		};

		listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			//log("key release");
			keys[keyCode] = false;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		return true;

	}
	return false;
}

bool MapScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		log("keycode: %d", &keyCode);
		return true;
	}
	else {
		return false;
	}
}

void MapScene::update_view(float delta) {
	setViewPointCenter(hero->getPosition());
}

void MapScene::update(float delta) {
	Node::update(delta);
	MoveCounter += 1;

	auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW, downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	auto Z = EventKeyboard::KeyCode::KEY_Z;
	if (isKeyPressed(leftArrow)) {
		if (MoveCounter % 3 == 0)hero->setTexture("character/hero2.png");
		else if (MoveCounter % 3 == 1)hero->setTexture("character/hero2_1.png");
		else if (MoveCounter % 3 == 2)hero->setTexture("character/hero2_2.png");
		heroFace = 4;
		keyPressedDuration(leftArrow);
	}
	else if (isKeyPressed(rightArrow)) {
		if (MoveCounter % 3 == 0)hero->setTexture("character/hero3.png");
		else if (MoveCounter % 3 == 1)hero->setTexture("character/hero3_1.png");
		else if (MoveCounter % 3 == 2)hero->setTexture("character/hero3_2.png");
		heroFace = 6;
		//hero->runAction(pause);
		keyPressedDuration(rightArrow);
	}
	else if (isKeyPressed(upArrow)) {
		if (MoveCounter % 3 == 0)hero->setTexture("character/hero4.png");
		else if (MoveCounter % 3 == 1)hero->setTexture("character/hero4_1.png");
		else if (MoveCounter % 3 == 2)hero->setTexture("character/hero4_2.png");
		heroFace = 8;
		//hero->runAction(pause);
		keyPressedDuration(upArrow);
	}
	else if (isKeyPressed(downArrow)) {
		if (MoveCounter % 3 == 0)hero->setTexture("character/hero1.png");
		else if (MoveCounter % 3 == 1)hero->setTexture("character/hero1_1.png");
		else if (MoveCounter % 3 == 2)hero->setTexture("character/hero1_2.png");
		heroFace = 2;
		//hero->runAction(pause);
		keyPressedDuration(downArrow);
	}
	else if (isKeyPressed(Z)) {
		keyPressedDuration(Z);
	}


	auto manPos = hero->getPosition();
	Point tileCoord = this->tileCoordForPosition(manPos);
	int tileGid = _door ->getTileGIDAt(tileCoord);
	if (tileGid)
	{
		auto properties = myMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto change = properties["Door"].asString();
			auto aName = properties["MapName"].asString();
			auto mName = aName.c_str();
			if ("True" == change) {	
				auto aScene = new MyScenes;
				aScene->setMapName(mName);
				MyScenes *nextScene = aScene->create(2);
				//auto scene = MyScenes::create(4);	
				Director::getInstance()->replaceScene(nextScene);
				return;
			}
		}
	}

}

void MapScene::keyPressedDuration(EventKeyboard::KeyCode code)
{

	int offsetX = 0, offsetY = 0;
	auto manPos = hero->getPosition();
	Point tileCoord = this->tileCoordForPosition(manPos);

	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX = -1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX = 1;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY = -1;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY = 1;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		{
			TMXObjectGroup *objects = myMap->getObjectGroup("Objects");
			CCLOG(objects->getGroupName().c_str());
			auto ClothesPoint = objects->getObject("Clothes");
			int x = ClothesPoint["x"].asInt();
			int y = ClothesPoint["y"].asInt();
			Point ClothesCoord = this->tileCoordForPosition(Point(x, y));
			if (heroFace == 2 && ClothesCoord.x == tileCoord.x && ClothesCoord.y == tileCoord.y + 1)
			{ 
				Director::getInstance()->end();
			}
			else if (heroFace == 4 && ClothesCoord.x == tileCoord.x - 1 && ClothesCoord.y == tileCoord.y)
			{
				DialogLayer* dialogLayer = DialogLayer::create("danxue");
				auto myScene = Director::getInstance()->getRunningScene();
				dialogLayer->setScale(0.5);
				dialogLayer->setAnchorPoint(Vect(0, 0));
				myScene->addChild(dialogLayer, 2, 2);
			}
			else if (heroFace == 6 && ClothesCoord.x == tileCoord.x + 1 && ClothesCoord.y == tileCoord.y)
			{
				Director::getInstance()->end();
			}
			else if (heroFace == 8 && ClothesCoord.x == tileCoord.x && ClothesCoord.y == tileCoord.y - 1)
			{
				Director::getInstance()->end();
			}
			break;
		}

	default:
		offsetY = offsetX = 0;
		break;
	}

	tileCoord.x += offsetX;
	tileCoord.y += offsetY;

	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid)
	{
		auto properties = myMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collision = properties["Collidable"].asString();
			if ("True" == collision) {
				//log("123");
				offsetX = 0;
				offsetY = 0;
				return;
			}
		}
	}


	auto moveTo = MoveTo::create(0.10, Point(manPos.x + offsetX * 32, manPos.y - offsetY * 32));
	hero->runAction(moveTo);



}

void MapScene::setViewPointCenter(Point position)
{
	auto winSize = Director::getInstance()->getWinSize();
	float x = MAX(position.x, winSize.width / 2);
	float y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (myMap->getMapSize().width*myMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (myMap->getMapSize().height*myMap->getTileSize().height) - winSize.height / 2);

	auto acturalPosition = Point(x, y);

	auto centerView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerView - acturalPosition;
	this->setPosition(viewPoint);
}

void MapScene::setPlayerPosition(Point position)
{
	Point tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid) {

		auto properties = myMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty()) {

			auto collision = properties["Collidable"].asString();
			if ("True" == collision) {
				//log("123");
				return;
			}
		}
	}
	hero->setPosition(position);
}

Point MapScene::tileCoordForPosition(Point position)
{

	int x = position.x / myMap->getTileSize().width;
	/*int y = position.y / myMap->getTileSize().height+1;*/
	int y = ((myMap->getMapSize().height * myMap->getTileSize().height) - position.y) / myMap->getTileSize().height;
	return Point(x, y);
}





