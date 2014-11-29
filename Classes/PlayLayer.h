#ifndef PLAY_LAYER_H_
#define PLAY_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class PlayLayer : public cocos2d::CCLayer
{
public:
	PlayLayer();
	~PlayLayer();
	static CCScene* scene();
	CREATE_FUNC(PlayLayer);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);
	virtual bool init();  
	void keyBackClicked();

	
	void initBeans();
	void clearBeans(int row,int column);

	int mBeansArray[GAME_BLOCK_ROW_NUMBER][GAME_BLOCK_COLUMN_NUMBER];
	CCLayer* mBeansLayer;
	int mScore;
};

#endif