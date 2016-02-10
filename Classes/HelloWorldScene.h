#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
	Sprite* _player;
	Sprite* _map;
	Sprite* _power;
	char direction;
	int score = 0;
	int difficulty = 6;
	bool powerup;
	bool paused = false;
	Vec2 powerloc;
	Vector<Sprite*> _trailer;
	Label* label = Label::createWithSystemFont("0", "Arial", 32);
public:
    static cocos2d::Scene* createScene();
	int elapsed = 0;
    virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float) override;
};


#endif // __HELLOWORLD_SCENE_H__
