#ifndef PLAY_LAYER_H_
#define PLAY_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif
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
	void update(float delta);
	
	void initBeans();
	void clearBeans(int row,int column);
	void playBeanAnimation(CCSprite* sprite,int row,int column,bool left);
	void spriteCallBack(CCNode* pSender, void* data);
	bool isGameOver();
	void gameOver();
	void upadeTime();
	void updateScore();
	void showAddScoreAnimation(int score);
	int getGameBestScore();
	void setGameBestScore(int score);
	void setSound(int score);
	void showInset();
	int getSound();
	void playBeginAnimation();
	void beginCallBack();
	void switchStart(CCObject *obj,TouchEventType type);
	void switchInfo(CCObject *obj,TouchEventType type);
	void switExplain(CCObject *obj,TouchEventType type);
	void showResult();
	void showExplain(bool bShow);
	int mBeansArray[GAME_BLOCK_ROW_NUMBER][GAME_BLOCK_COLUMN_NUMBER];
	CCLayer* mBeansLayer;
	int mScore;
	int mTime;
	int mState;
	int mBestScore;
	int mSound;
	CCSize mScreenSize;
	UILabel *mTimeLabel;
	UILabel *mScoreLabel;
	CCLabelTTF *mScoreAnimation;
	CCProgressTimer *mProgressTimer;
	CCLayer *mBeginLayer;
	CCLayer *mRestartlayer;
	CCSprite *mBeginSprite;
	CCSprite *mRestartSprite;

	UIButton *mStartBtn;
	UIButton *mInfoBtn;
	CCSprite *mExplainSprite;
	UILayer *mBeginUIlayer;

	UIButton *mReStartBtn;
	UILayer *mRestartUIlayer;
	UILabel *mBestScoreLabel;
	UILabel *mCurrentScoreLabel;

	int mPlayTimes;
};

#endif