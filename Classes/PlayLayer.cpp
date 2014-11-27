#include "PlayLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

CCScene* PlayLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	PlayLayer *layer = PlayLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

PlayLayer::PlayLayer()
{

}

PlayLayer::~PlayLayer()
{

}

void PlayLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

bool PlayLayer::init()
{
	do 
	{
		setTouchEnabled( true );
		this->setKeypadEnabled(true);

	} while (0);

	return true;
}