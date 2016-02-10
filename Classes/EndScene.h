#include "cocos2d.h"
using namespace cocos2d;

class EndScreen : public cocos2d::Layer
{
private:
	Sprite* _diff;
	Sprite* _cursor;
	int current = 0;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	//int current = 0;

	CREATE_FUNC(EndScreen);
};