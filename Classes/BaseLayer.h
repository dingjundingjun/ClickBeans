#ifndef _BASE_LAYER_H_
#define _BASE_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class BaseLayer : public cocos2d::CCLayer
{
	BaseLayer();
	~BaseLayer();
	virtual bool init();  
	static CCScene* scene();
	CREATE_FUNC(BaseLayer);
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void keyBackClicked();
};

#endif