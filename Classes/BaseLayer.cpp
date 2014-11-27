#include "BaseLayer.h"

CCScene* BaseLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	BaseLayer *layer = BaseLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

BaseLayer::BaseLayer()
{

}

BaseLayer::~BaseLayer()
{

}

// on "init" you need to initialize your instance
bool BaseLayer::init()
{
	do 
	{
		setTouchEnabled( true );
		this->setKeypadEnabled(true);

	} while (0);

	return true;
}

void BaseLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void BaseLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}