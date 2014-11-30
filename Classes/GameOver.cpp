#include "GameOver.h"
#include "PlayLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

CCScene* GameOver::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameOver *layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

void GameOver::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

bool GameOver::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	setTouchEnabled( true );
	this->setKeypadEnabled(true);
	mUIlayer = UILayer::create();
	mReStartBtn = Util::createUIButton("restar.png","restar_press.png");
	mReStartBtn->addTouchEventListener(this,toucheventselector(GameOver::switchRestart));
	mReStartBtn->setPosition(ccp(size.width/2 - 100,100));
	mUIlayer->addWidget(mReStartBtn);

	mExitBtn = Util::createUIButton("exit.png","exit_press.png");
	mExitBtn->addTouchEventListener(this,toucheventselector(GameOver::switchExit));
	mExitBtn->setPosition(ccp(size.width/2 + 100,100));
	mUIlayer->addWidget(mExitBtn);

	this->addChild(mUIlayer);
	return true;
}

void GameOver::switchRestart(CCObject *obj,TouchEventType type)
{
	CCScene *scene = PlayLayer::scene();
	CCTransitionScene *reScene =Util::createSceneAnimaion(SCENE_RADIA_CCW,scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void GameOver::switchExit(CCObject *obj,TouchEventType type)
{
	CCDirector::sharedDirector()->end();
}