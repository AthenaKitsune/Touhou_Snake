#include "HelpScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

SimpleAudioEngine *tbgm;

Scene* TitleScreen::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScreen::create();

	scene->addChild(layer);

	return scene;
}

bool TitleScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	//label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	//this->addChild(label, 1);

	//bgm loading
	tbgm = SimpleAudioEngine::getInstance();
	tbgm->playBackgroundMusic("Last Remote.mp3", true);

	_title = Sprite::create("title_main.png");
	_title->setAnchorPoint(Vec2(0, 0));
	_title->setPosition(Vec2(0, 0));
	this->addChild(_title);

	_cursor = Sprite::create("player_trail.png");
	_cursor->setAnchorPoint(Vec2(0.5, 0.5));
	_cursor->setPosition(Vec2(414, 186));

	auto rotation = RotateBy::create(1, 45);
	auto repeat = RepeatForever::create(rotation);
	this->addChild(_cursor);
	_cursor->runAction(repeat);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ENTER:
			if (current == 0) 
			{
				tbgm->playEffect("1UP.wav");
				auto newScene = HelpScreen::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(2, newScene, Color3B(0,0,0)));
			}
			else { Director::getInstance()->end(); }
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (current == 1) { current = 0; _cursor->setPosition(Vec2(414, 186)); }
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (current == 0) { current = 1; _cursor->setPosition(Vec2(420, 480-338)); }
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _cursor);

	return true;
}