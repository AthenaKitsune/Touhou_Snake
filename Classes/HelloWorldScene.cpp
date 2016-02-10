#include "HelloWorldScene.h"
#include "EndScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

SimpleAudioEngine *bgm;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//difficulty

	//bgm loading
	bgm = SimpleAudioEngine::getInstance();
	bgm->preloadBackgroundMusic("Pichuun.mp3");
	bgm->playBackgroundMusic("suwa foughten field -edit volume-.mp3", true);

	/////////////////////////////
	// 2. initialization of everything

	//create map
	_map = Sprite::create("map_lake.png");
	_map->setAnchorPoint(Vec2(0, 0));
	_map->setPosition(Vec2(0, 0));
	this->addChild(_map);

	//create player and add key listener
	_player = Sprite::create("player_sprite.png");
	_player->setAnchorPoint(Vec2(0, 0));
	_player->setPosition(Vec2(32, 32));
	this->addChild(_player);
	//_pos.insert(0, _player->getPosition());
	this->scheduleUpdate();

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			if (loc.x > 32 && direction != 'r' && paused == false) { direction = 'l'; }
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			if (loc.x < 608 - 32 && direction != 'l' && paused == false) { direction = 'r'; }
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (loc.y < 448 - 32 && direction != 'd' && paused == false) { direction = 'u'; }
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (loc.y > 32 && direction != 'u' && paused == false) { direction = 'd'; }
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
			if (paused == false) { paused = true; }
			else { paused = false;  }
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _player);

	//create power up
	_power = Sprite::create("player_power.png");
	_power->setAnchorPoint(Vec2(0, 0));
	_power->setPosition(Vec2(32 + (rand() % 18) * 32, 32 + (rand() % 13) * 32));
	this->addChild(_power);
	this->scheduleUpdate();
	powerup = false;
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float delta) 
{

	//power update collision, should not spawn in tail + score update
	if (_power->getPosition() == _player->getPosition()) 
	{
		bgm->playEffect("POWERUP.wav");
		score++;
		if (score >= 233) 
		{
			paused = true;
			auto newScene = EndScreen::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1, newScene, Color3B(0, 0, 0)));
		}
		powerup = true;
		//randomize power position
		auto position = _power->getPosition();
		powerloc = position;
		position.x = 32 + (rand() % 18) * 32;
		position.y = 32 + (rand() % 13) * 32;
		_power->setPosition(position);
	}

	//tail collision detection, apparently ignored if it only has one tail
	if (powerup == false)
	{
		for (int i = 0; i < score; i++)
		{
			if (_player->getPosition() == _trailer.at(i)->getPosition())
			{
				bgm->playEffect("Pichuun.wav");
				auto newScene = HelloWorld::createScene();
				Director::getInstance()->replaceScene(newScene);
			}
		}
	}
		
	//move every n frames
	if (paused != true) elapsed++;
	if (elapsed >= difficulty)
	{
		//continues motion
		Vec2 loc = _player->getPosition();
		switch (direction)
		{
			case 'l':
				if (loc.x > 32)_player->setPosition(loc.x - 32, loc.y);
				else
				{
					bgm->playEffect("Pichuun.wav");
					auto newScene = HelloWorld::createScene();
					Director::getInstance()->replaceScene(newScene);
				}
				break;
			case 'r':
				if (loc.x < 608 - 32)_player->setPosition(loc.x + 32, loc.y);
				else
				{
					bgm->playEffect("Pichuun.wav");
					auto newScene = HelloWorld::createScene();
					Director::getInstance()->replaceScene(newScene);
				}
				break;
			case 'u':
				if (loc.y < 448 - 32)_player->setPosition(loc.x, loc.y + 32);
				else
				{
					bgm->playEffect("Pichuun.wav");
					auto newScene = HelloWorld::createScene();
					Director::getInstance()->replaceScene(newScene);
				}
				break;
			case 'd':
				if (loc.y > 32)_player->setPosition(loc.x, loc.y - 32);
				else
				{
					bgm->playEffect("Pichuun.wav");
					auto newScene = HelloWorld::createScene();
					Director::getInstance()->replaceScene(newScene);
				}
				break;
		}

		//append snake tail
		if (powerup == true)
		{
			auto _ntrail = Sprite::create("player_trail.png");
			_ntrail->setAnchorPoint(Vec2(0, 0));
			_ntrail->setPosition(powerloc);
			this->addChild(_ntrail);
			_trailer.insert(0, _ntrail);
		}

		//move snake tail
		if (powerup == false)
		{
			for (int i = score - 1; i >= 0; i--)
			{
				if (i != 0)
					_trailer.at(i)->setPosition(_trailer.at(i-1)->getPosition());
				else
					_trailer.at(i)->setPosition(loc);
			}
		}
		powerup = false;
		//reset elapsed variable
		elapsed = 0;
	}
}
