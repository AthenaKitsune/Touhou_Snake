#include "HelloWorldScene.h"
#include "DialogueScene.h"
#include "HelpScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

SimpleAudioEngine *cbgm;

Scene* HelpScreen::createScene()
{
	auto scene = Scene::create();
	auto layer = HelpScreen::create();

	scene->addChild(layer);

	return scene;
}

bool HelpScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	//label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	//this->addChild(label, 1);

	//bgm loading
	//bgm = SimpleAudioEngine::getInstance();
	//bgm->playBackgroundMusic("suwa foughten field -edit volume-.mp3");

	_help = Sprite::create("title_help.png");
	_help->setAnchorPoint(Vec2(0, 0));
	_help->setPosition(Vec2(0, 0));
	this->addChild(_help);

	_cursor = Sprite::create("player_trail.png");
	_cursor->setAnchorPoint(Vec2(0.5, 0.5));
	_cursor->setPosition(Vec2(350, 18));

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
				cbgm = SimpleAudioEngine::getInstance();
				cbgm->stopBackgroundMusic();
				cbgm->playEffect("1UP.wav");
				auto newScene = DialogueScreen::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(2, newScene, Color3B(0, 0, 0)));
			}
			else { Director::getInstance()->end(); }
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _cursor);

	return true;
}