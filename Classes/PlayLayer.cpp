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
	std::srand((unsigned int)time(0));
	setTouchEnabled( true );
	this->setKeypadEnabled(true);
	CCSprite *bgSprite = CCSprite::create("bg.png");
	bgSprite->setAnchorPoint(ccp(0,0));
	this->addChild(bgSprite);

	initBeans();
	return true;
}

void PlayLayer::initBeans()
{
	int i = 0;
	int j = 0;
	int p = 0;
	mScore = 0;
	for(i = 0 ; i < GAME_BLOCK_ROW_NUMBER;i++)
	{
		for(j = 0;j < GAME_BLOCK_COLUMN_NUMBER;j++)
		{
			mBeansArray[i][j] = -1;
		}
	}
	for(p = 0; p < BEANS_NUMBER;p++)
	{
		int random = rand()%6;
		CCSprite* beans = CCSprite::create(BEANS[random]);
		while(true)
		{
			int row = rand()% (GAME_BLOCK_ROW_NUMBER);
			int column = rand()%(GAME_BLOCK_COLUMN_NUMBER);
			if(mBeansArray[row][column] == -1)
			{
				mBeansArray[row][column] = random;
				CCSprite* bean = CCSprite::create(BEANS[random]);
				bean->setTag(row*100 + column);
				bean->setPosition(ccp(column * GAME_BLOCK_WIDTH + GAME_BLOCK_WIDTH/2 + ROW_PX,row * GAME_BLOCK_HEIGHT + GAME_BLOCK_HEIGHT/2 + COLUMN_PX));
				CCLOG("row = %d,column = %d",row,column);
				addChild(bean);
				break;
			}
		}
	}
}

bool PlayLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}

void PlayLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void PlayLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCLOG("ccTouchEnded");
	CCPoint point = pTouch->getLocation();
	int row = (point.y - ROW_PX)/GAME_BLOCK_WIDTH;
	int column = (point.x - COLUMN_PX)/GAME_BLOCK_HEIGHT;
	CCLOG("row = %d,column = %d",row,column);
	if(row >= GAME_BLOCK_ROW_NUMBER || column >= GAME_BLOCK_COLUMN_NUMBER)
	{
		return;
	}
	if(mBeansArray[row][column] == -1)
	{
		CCLOG("this block has no bean");
		clearBeans(row,column);
	}
	else
	{
		CCLOG("this bean tag is %d",row*100+column);
		
	}
}

void PlayLayer::clearBeans(int row,int column)
{
	int i = 0;
	int leftBean = -1;
	int rightBean = -1;
	int upBean = -1;
	int downBean = -1;
	int tempBeans[4][3] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	//left
	for(i = column - 1;i >= 0;i--)
	{
		if(mBeansArray[row][i] != -1)
		{
			tempBeans[0][0] = mBeansArray[row][i];
			tempBeans[0][1] = row;
			tempBeans[0][2] = i;
			break;
		}
	}
	//right
	for(i = column + 1;i < GAME_BLOCK_COLUMN_NUMBER;i++)
	{
		if(mBeansArray[row][i] != -1)
		{
			tempBeans[1][0] = mBeansArray[row][i];
			tempBeans[1][1] = row;
			tempBeans[1][2] = i;
			break;
		}
	}
	//up
	for(i = row + 1;i < GAME_BLOCK_ROW_NUMBER;i++)
	{
		if(mBeansArray[i][column] != -1)
		{
			tempBeans[2][0] = mBeansArray[i][column];
			tempBeans[2][1] = i;
			tempBeans[2][2] = column;
			break;
		}
	}
	//down
	for(i = row -1;i >=0;i--)
	{
		if(mBeansArray[i][column] != -1)
		{
			tempBeans[3][0] = mBeansArray[i][column];
			tempBeans[3][1] = i;
			tempBeans[3][2] = column;
			break;
		}
	}

	for(int n = 0;n < 4;n++)
	{
		int oneBean = tempBeans[n][0];
		for(int p = n+1;p < 4;p++)
		{
			int secondBean = tempBeans[p][0];
			if(oneBean == secondBean)
			{
				CCLOG("11111 %d  , %d",tempBeans[n][1],tempBeans[n][2]);
				tempBeans[p][0] = BEANS_CLEAR;
				tempBeans[n][0] = BEANS_CLEAR;
				/*
				this->removeChildByTag(tempBeans[n][1]*100 + tempBeans[n][2]);
				this->removeChildByTag(tempBeans[p][1]*100 + tempBeans[p][2]);
				mBeansArray[tempBeans[n][1]][tempBeans[n][2]] = -1;
				mBeansArray[tempBeans[p][1]][tempBeans[p][2]] = -1;
				*/
			}
		}
	}
	for(int n = 0;n < 4;n++)
	{
		if(tempBeans[n][0] == BEANS_CLEAR)
		{
			this->removeChildByTag(tempBeans[n][1]*100 + tempBeans[n][2]);
			mBeansArray[tempBeans[n][1]][tempBeans[n][2]] = -1;
			mScore++;
		}
	}
}

void PlayLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}