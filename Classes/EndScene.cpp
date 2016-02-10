#include "HelloWorldScene.h"
#include "EndScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

SimpleAudioEngine *abgm;

Scene* EndScreen::createScene()
{
	auto scene = Scene::create();
	auto layer = EndScreen::create();

	scene->addChild(layer);

	return scene;
}

bool EndScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	//label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	//this->addChild(label, 1);

	//bgm loading
	abgm = SimpleAudioEngine::getInstance();
	abgm->playBackgroundMusic("The Gods Give Us Blessed Rain ~ Sylphid Dream.mp3");

	_diff = Sprite::create("title_win.png");
	_diff->setAnchorPoint(Vec2(0, 0));
	_diff->setPosition(Vec2(0, 0));
	this->addChild(_diff);

	_cursor = Sprite::create("player_trail.png");
	_cursor->setAnchorPoint(Vec2(0.5, 0.5));
	_cursor->setPosition(Vec2(400, 18));

	auto rotation = RotateBy::create(1, 45);
	auto repeat = RepeatForever::create(rotation);
	this->addChild(_cursor);
	_cursor->runAction(repeat);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ENTER:
			abgm = SimpleAudioEngine::getInstance();
			abgm->stopBackgroundMusic();
			Director::getInstance()->end();
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _cursor);

	return true;
}