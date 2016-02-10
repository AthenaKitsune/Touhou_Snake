#include "HelloWorldScene.h"
#include "DialogueScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

SimpleAudioEngine *ebgm;

Scene* DialogueScreen::createScene()
{
	auto scene = Scene::create();
	auto layer = DialogueScreen::create();

	scene->addChild(layer);

	return scene;
}

bool DialogueScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	//label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	//this->addChild(label, 1);

	//bgm loading
	ebgm = SimpleAudioEngine::getInstance();
	ebgm->playBackgroundMusic("Mysterious Mountain.mp3", true);

	_title = Sprite::create("back_main.png");
	_title->setAnchorPoint(Vec2(0, 0));
	_title->setPosition(Vec2(0, 0));
	this->addChild(_title);

	_location = Sprite::create("back_location.png");
	_location->setAnchorPoint(Vec2(0, 1));
	_location->setPosition(Vec2(0, 480));
	_title->addChild(_location);

	_sanae = Sprite::create("sanae_normal.png");
	_sanae->setAnchorPoint(Vec2(0, 0));
	_sanae->setPosition(Vec2(0, 0));
	_title->addChild(_sanae);

	_dialogue = Sprite::create("d1.png");
	_dialogue->setAnchorPoint(Vec2(0, 0));
	_dialogue->setPosition(Vec2(0, 0));
	_sanae->addChild(_dialogue);

	_cursor = Sprite::create("player_trail.png");
	_cursor->setAnchorPoint(Vec2(0.5, 0.5));
	_cursor->setPosition(Vec2(414, 186));

	//auto rotation = RotateBy::create(1, 45);
	//auto repeat = RepeatForever::create(rotation);
	//this->addChild(_cursor);
	//_cursor->runAction(repeat);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ENTER:
			if (current == 0)
			{
				current++;

				//No?
				_dialogue->setTexture("d2.png");
			}
			else if (current == 1)
			{
				current++;

				_sanae->setTexture("sanae_sweat.png");

				//Ugh. Even though I went to try and resolve this incident... I don't have a single lead.
				_dialogue->setTexture("d3.png");
			}
			else if (current == 2)
			{
				current++;

				//I guess I'll just look around here then. Maybe Lady Suwako can offer me some advice.
				_dialogue->setTexture("d4.png");
			}
			else if (current == 3)
			{
				current++;

				_sanae->setTexture("sanae_surprised.png");

				//Hmm? What's this?
				_dialogue->setTexture("d5.png");
			}
			else if (current == 4)
			{
				current++;

				_sanae->setTexture("sanae_normal.png");

				//Looks like I don't need to look any further!
				_dialogue->setTexture("d6.png");
			}
			else if (current == 5)
			{
				current++;

				_sanae->setTexture("sanae_ready.png");

				//Just you wait Reimu! I'll solve this incident!
				_dialogue->setTexture("d7.png");

				ebgm->playEffect("CAUTION.wav");

				_cline = Sprite::create("caution_line.png");
				_cline->setAnchorPoint(Vec2(0, 0));
				_cline->setPosition(Vec2(0, 0));
				this->addChild(_cline);

				_cword = Sprite::create("caution_word.png");
				_cword->setAnchorPoint(Vec2(0, 0));
				_cword->setPosition(Vec2(0, 0));
				this->addChild(_cword);

				//auto actleft = MoveBy::create(4, Vec2(640, 0));
				auto actright = MoveBy::create(4, Vec2(-640, 0));
				//_cline->runAction(actleft);
				_cword->runAction(actright);
			}
			else if (current == 6)
			{
				auto newScene = HelloWorld::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(1, newScene, Color3B(0, 0, 0)));
			}
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _dialogue);

	return true;
}