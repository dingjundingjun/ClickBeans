#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class GameOver : public cocos2d::CCLayer
{
public:
	GameOver();
	~GameOver();
	static CCScene* scene();
	CREATE_FUNC(GameOver);
	virtual bool init();  
	void keyBackClicked();

	void switchRestart(CCObject *obj,TouchEventType type);
	void switchExit(CCObject *obj,TouchEventType type);
private:
	UIButton *mReStartBtn;
	UIButton *mExitBtn;
	UILayer *mUIlayer;
};

#endif