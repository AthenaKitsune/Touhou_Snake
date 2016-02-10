#include "cocos2d.h"
using namespace cocos2d;

class HelpScreen : public cocos2d::Layer
{
private:
	Sprite* _help;
	Sprite* _cursor;
	int current = 0;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(HelpScreen);
};