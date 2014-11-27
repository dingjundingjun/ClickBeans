#include "FirstLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

CCScene* FirstLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	FirstLayer *layer = FirstLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

FirstLayer::FirstLayer()
{

}

FirstLayer::~FirstLayer()
{

}

void FirstLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

bool FirstLayer::init()
{
	do 
	{
		setTouchEnabled( true );
		this->setKeypadEnabled(true);

	} while (0);

	return true;
}