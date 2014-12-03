#include "PlayLayer.h"
#include "GameOver.h"

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
	mBestScore = getGameBestScore();
	mSound = getSound();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	mScreenSize = size;
	std::srand((unsigned int)time(0));
	setTouchEnabled( true );
	this->setKeypadEnabled(true);

	mBeginLayer = CCLayer::create();
	mBeginSprite = CCSprite::create("begin_layer.png");
	this->addChild(mBeginLayer,1000);
	mBeginLayer->addChild(mBeginSprite);
	mBeginLayer->setPosition(ccp(0,size.height + mBeginLayer->getContentSize().height));
	mBeginSprite->setPosition(ccp(size.width/2,size.height/2));
	mBeginUIlayer = UILayer::create();
	mStartBtn = Util::createUIButton("start_game.png","start_game_press.png");
	mStartBtn->addTouchEventListener(mBeginLayer,toucheventselector(PlayLayer::switchStart));
	mStartBtn->setPosition(ccp(size.width/2,size.height/2 + 10));
	mBeginUIlayer->addWidget(mStartBtn);
	mInfoBtn = Util::createUIButton("game_info.png","game_info_press.png");
	mInfoBtn->addTouchEventListener(mBeginLayer,toucheventselector(PlayLayer::switchInfo));
	mInfoBtn->setPosition(ccp(size.width/2,size.height/2 - 100));
	mBeginUIlayer->addWidget(mInfoBtn);
	mBeginLayer->addChild(mBeginUIlayer);

	mRestartlayer = CCLayer::create();
	mRestartSprite = CCSprite::create("restart_layer.png");
	this->addChild(mRestartlayer,1001);
	mRestartlayer->addChild(mRestartSprite);
	mRestartlayer->setPosition(ccp(0,size.height + mRestartlayer->getContentSize().height));
	mRestartSprite->setPosition(ccp(size.width/2,size.height/2));
	mRestartUIlayer = UILayer::create();
	mReStartBtn = Util::createUIButton("restart_btn.png","restart_btn_press.png");
	mReStartBtn->addTouchEventListener(mRestartlayer,toucheventselector(PlayLayer::switchStart));
	mReStartBtn->setPosition(ccp(size.width/2,size.height/2 - 120));
	mRestartUIlayer->addWidget(mReStartBtn);
	mRestartlayer->addChild(mRestartUIlayer);

	ccColor3B color;
	color.b = 0;
	color.g = 0;
	color.r = 255;
	mBestScoreLabel = UILabel::create();
	mBestScoreLabel->setFontSize(40);
	mBestScoreLabel->setText("100");
	mBestScoreLabel->setColor(color);
	mBestScoreLabel->setPosition(ccp(size.width/2,size.height/2 - 50));
	mRestartlayer->addChild(mBestScoreLabel,100);

	mCurrentScoreLabel = UILabel::create();
	mCurrentScoreLabel->setFontSize(40);
	mCurrentScoreLabel->setText("100");
	mCurrentScoreLabel->setColor(color);
	mCurrentScoreLabel->setPosition(ccp(size.width/2,size.height/2 + 20 ));
	mRestartlayer->addChild(mCurrentScoreLabel,100);

	CCSprite *bgSprite = CCSprite::create("bg.png");
	bgSprite->setAnchorPoint(ccp(0,0));
	this->addChild(bgSprite);
	CCSprite *bgSprite2 = CCSprite::create("bg2.png");
	bgSprite2->setPosition(ccp(size.width/2,size.height/2 - 50));
	this->addChild(bgSprite2);

	CCSprite *progressBg = CCSprite::create("progress_bg.png");
	progressBg->setPosition(ccp(size.width/2,size.height-progressBg->getContentSize().height/2 - 20));
	this->addChild(progressBg);

	CCSprite *progressbgSprite=CCSprite::create("progress.png");  
	progressbgSprite->setPosition(ccp(progressBg->getContentSize().width/2, progressBg->getContentSize().height/2));  
	progressBg->addChild(progressbgSprite);  

	CCSprite *progressSprite=CCSprite::create("progress_ing.png");  
	mProgressTimer = CCProgressTimer::create(progressSprite);  
	mProgressTimer->setType(kCCProgressTimerTypeBar);  
	mProgressTimer->setPosition(ccp(progressBg->getContentSize().width/2, progressBg->getContentSize().height/2));  
	mProgressTimer->setMidpoint(ccp(0, 0));
	mProgressTimer->setBarChangeRate(ccp(1, 0));  
	mProgressTimer->setPercentage(100);  
	progressBg->addChild(mProgressTimer);

	mState = GAME_WAIT;
	mTimeLabel = UILabel::create();
	mTimeLabel->setFontSize(30);
	mTimeLabel->setText("time:60");
	mTimeLabel->setPosition(ccp(270,progressBg->getPosition().y));
	this->addChild(mTimeLabel,100);

	mScoreLabel = UILabel::create();
	mScoreLabel->setFontSize(30);
	mScoreLabel->setText("0");
	mScoreLabel->setPosition(ccp(750,progressBg->getPosition().y));
	this->addChild(mScoreLabel,100);
	//initBeans();
	scheduleUpdate();
	playBeginAnimation();
	mScoreAnimation = CCLabelTTF::create("0","Marker Felt",60);
	this->addChild(mScoreAnimation);

	return true;
}

void PlayLayer::switchStart(CCObject *obj,TouchEventType type)
{
	
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
		{
			CCLOG("switch start");
			beginCallBack();
			break;
		}
	}
}

void PlayLayer::switchInfo(CCObject *obj,TouchEventType type)
{
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
	{
		CCLOG("switch Info");
		break;
	}
	}
}

void PlayLayer::beginCallBack()
{
	CCActionInterval *moTo = CCMoveTo::create(0.5,ccp(0,CCDirector::sharedDirector()->getWinSize().height));
	CCActionInterval *action = CCSequence::create(moTo,CCCallFunc::create((PlayLayer*)getParent(),callfunc_selector(PlayLayer::initBeans)),NULL);
	runAction(action);
}

void PlayLayer::playBeginAnimation()
{
	CCActionInterval *move = CCMoveTo::create(0.5, ccp(0,0));
	CCActionInterval* jumpto = CCJumpBy ::create(0.5, ccp(0, 0), 100, 1 );
	CCActionInterval *action = CCSequence::create(move,jumpto,NULL);
	mBeginLayer->runAction(action);
}

void PlayLayer::showResult()
{

	char str[10];
	memset(str,0,10);
	sprintf(str,"%d",mBestScore);
	mBestScoreLabel->setText(str);

	char str1[10];
	memset(str1,0,10);
	sprintf(str1,"%d",mScore);
	mCurrentScoreLabel->setText(str1);

	CCActionInterval *move = CCMoveTo::create(0.5, ccp(0,0));
	CCActionInterval* jumpto = CCJumpBy ::create(0.5, ccp(0, 0), 100, 1 );
	CCActionInterval *action = CCSequence::create(move,jumpto,NULL);
	mRestartlayer->runAction(action);
}

void PlayLayer::update(float delta)
{
	if(mState == GAME_START)
	{
		mTime++;
		CCLOG("game time = %d",mTime);
		upadeTime();
		if(mTime >= GAME_TIME)
		{
			mState = GAME_END;
		}
	}
	else if(mState == GAME_END)
	{
		CCLOG("game is over you score is %d",mScore);
		gameOver();
	}
}

void PlayLayer::showAddScoreAnimation(int score)
{
	char str[10];
	memset(str,0,10);
	sprintf(str,"+%d",score);
	mScoreAnimation->setString(str);

	mScoreAnimation->setPosition(ccp(mScoreLabel->getPosition().x,mScoreLabel->getPosition().y - 60));
	mScoreAnimation->setVisible(true);
	CCActionInterval *move = CCMoveBy::create(0.5,ccp(0,100));
	CCActionInterval *alpha = CCFadeOut::create(0.5);
	CCFiniteTimeAction *ccFiniteAction = CCSpawn::create(move,alpha,NULL);
	mScoreAnimation->runAction(ccFiniteAction);
}

void PlayLayer::upadeTime()
{
	int t = 60 - mTime / 60;
	if(t < 0)
		t = 0;
	char str[10];
	memset(str,0,10);
	sprintf(str,"time : %d",t);
	mTimeLabel->setText(str);
	int percent = (t)*100/60;
	mProgressTimer->setPercentage(percent);  
}

void PlayLayer::updateScore()
{
	char str[10];
	memset(str,0,10);
	sprintf(str,"%d",mScore);
	mScoreLabel->setText(str);
}

int PlayLayer::getGameBestScore()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");//com.laj.clickbeans
	if (JniHelper::getMethodInfo(t, "com/laj/clickbeans/GameDataControl", "getBestScore", "()I")) {
		jclass header_class = t.env->FindClass("com/laj/clickbeans/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/laj/clickbeans/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"getBestScore","()I");
		int score = t.env->CallIntMethod(header_object,getBestScoreID);
		CCLOG("get best score = %d",score);
		return score;
	}
#endif
	return 0;
}

void PlayLayer::setGameBestScore(int score)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getMethodInfo(t, "com/laj/clickbeans/GameDataControl", "setBestScore", "(I)I")) {
		jclass header_class = t.env->FindClass("com/laj/clickbeans/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/laj/clickbeans/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"setBestScore","(I)I");
		t.env->CallIntMethod(header_object,getBestScoreID,score);
		CCLOG("get best score = %d",score);
	}
#endif
}

int PlayLayer::getSound()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getMethodInfo(t, "com/laj/clickbeans/GameDataControl", "getSound", "()I")) {
		jclass header_class = t.env->FindClass("com/laj/clickbeans/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/laj/clickbeans/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"getSound","()I");
		int score = t.env->CallIntMethod(header_object,getBestScoreID);
		CCLOG("get best score = %d",score);
		return score;
	}
#endif
	return 1;
}


void PlayLayer::setSound(int score)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	CCLOG("getData_ ==========  ");
	if (JniHelper::getMethodInfo(t, "com/laj/clickbeans/GameDataControl", "setSound", "(I)I")) {
		jclass header_class = t.env->FindClass("com/laj/clickbeans/GameDataControl");
		jmethodID init_id = t.env->GetStaticMethodID( header_class, "getInstance", "()Lcom/laj/clickbeans/GameDataControl;");
		CCLOG("get best init_id = %d",init_id);
		jobject header_object = t.env->CallStaticObjectMethod(header_class, init_id);
		jmethodID getBestScoreID = t.env->GetMethodID(header_class,"setSound","(I)I");
		t.env->CallIntMethod(header_object,getBestScoreID,score);
		CCLOG("get best score = %d",score);
	}
#endif
}

void PlayLayer::initBeans()
{
	mState = GAME_START;
	mTime = 0;
	int i = 0;
	int j = 0;
	int p = 0;
	mScore = 0;
	updateScore();
	for(i = 0 ; i < GAME_BLOCK_ROW_NUMBER;i++)
	{
		for(j = 0;j < GAME_BLOCK_COLUMN_NUMBER;j++)
		{
			mBeansArray[i][j] = -1;
			removeChildByTag(i*100 + j);
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
				bean->setPosition(ccp(mScreenSize.width/2,mScreenSize.height/2));
				bean->setTag(row*100 + column);
				//bean->setPosition(ccp(column * GAME_BLOCK_WIDTH + GAME_BLOCK_WIDTH/2 + ROW_PX,row * GAME_BLOCK_HEIGHT + GAME_BLOCK_HEIGHT/2 + COLUMN_PX));
				CCLOG("row = %d,column = %d",row,column);
				addChild(bean);
				CCMoveTo *moveTo = CCMoveTo::create(0.5,ccp(column * GAME_BLOCK_WIDTH + GAME_BLOCK_WIDTH/2 + ROW_PX,row * GAME_BLOCK_HEIGHT + GAME_BLOCK_HEIGHT/2 + COLUMN_PX));
				bean->runAction(moveTo);
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
	if(mState != GAME_START)
	{
		return;
	}
	CCLOG("ccTouchEnded");
	CCPoint point = pTouch->getLocation();
	int row = (point.y - COLUMN_PX)/GAME_BLOCK_WIDTH;
	int column = (point.x - ROW_PX)/GAME_BLOCK_HEIGHT;
	CCLOG("row = %d,column = %d",row,column);
	if(row >= GAME_BLOCK_ROW_NUMBER || column >= GAME_BLOCK_COLUMN_NUMBER)
	{
		return;
	}
	if(mBeansArray[row][column] == -1)
	{
		CCLOG("this block has no bean");
		clearBeans(row,column);
		if(isGameOver())
		{
			CCLOG("you are win you score is 200");
			gameOver();
		}
	}
	else
	{
		CCLOG("this bean tag is %d",row*100+column);
	}
}

void PlayLayer::gameOver()
{
	mState = GAME_WAIT;
	gGameScore = mScore;
	if(gGameScore > mBestScore)
	{
		mBestScore = gGameScore;
		setGameBestScore(gGameScore);
	}
	/*CCScene *scene = GameOver::scene();
	CCTransitionScene *tScene = Util::createSceneAnimaion(SCENE_RADIA_CCW,scene);
	CCDirector::sharedDirector()->replaceScene(tScene);*/
	showResult();
}

bool PlayLayer::isGameOver()
{
	for(int i = 0;i < GAME_BLOCK_ROW_NUMBER;i++)
		for(int j = 0;j<GAME_BLOCK_COLUMN_NUMBER;j++)
	{
		if(mBeansArray[i][j] != -1)
		{
			return false;
		}
	}
	return true;
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
		if(oneBean == -1)
		{
			continue;
		}
		for(int p = n+1;p < 4;p++)
		{
			int secondBean = tempBeans[p][0];
			if(oneBean == secondBean)
			{
				CCLOG("11111 %d  , %d",tempBeans[n][1],tempBeans[n][2]);
				tempBeans[p][0] = BEANS_CLEAR;
				tempBeans[n][0] = BEANS_CLEAR;
			}
		}
	}
	bool isClear = false;
	int scoreAdd = 0;
	for(int n = 0;n < 4;n++)
	{
		if(tempBeans[n][0] == BEANS_CLEAR)
		{
			isClear = true;
			//this->removeChildByTag(tempBeans[n][1]*100 + tempBeans[n][2]);
			mBeansArray[tempBeans[n][1]][tempBeans[n][2]] = -1;
			mScore++;
			scoreAdd++;
			updateScore();
			playBeanAnimation((CCSprite*)this->getChildByTag(tempBeans[n][1]*100 + tempBeans[n][2]),tempBeans[n][1],tempBeans[n][2],(n == 0 || n == 2));
		}
	}
	if(scoreAdd > 0)
	{
			showAddScoreAnimation(scoreAdd);
	}
	if(isClear == false)
	{
		mTime += 120;
	}
}

void PlayLayer::playBeanAnimation(CCSprite* sprite,int row,int column,bool left)
{
	CCLOG("error row = %d column = %d",row,column);
	ccBezierConfig bezier;
	int startX = sprite->getPosition().x;
	int startY = sprite->getPosition().y;
	int endX =0;
	int endY = -1*GAME_BLOCK_HEIGHT;
	if(left)
	{
		endX = -1 * rand()%120 - 50 + startX;
	}
	else
	{
		endX = rand()%120 + 50 + startX;
	}

	CCPointArray * array = CCPointArray::create(20);
	array->addControlPoint(ccp(startX,startY));
	array->addControlPoint(ccp((endX - startX)/2 + startX,startY + rand()%20 + 10));
	array->addControlPoint(ccp(endX,endY));
	float time = 1.5*row/GAME_BLOCK_ROW_NUMBER;
	if(time >= 1)
	{
		time = 1;
	}
	if(time < 0.5)
	{
		time = 0.5;
	}
	CCActionInterval  * CardinalSplineTo=CCCardinalSplineTo::create(time, array, 0);
	CCActionInterval *sequence = CCSequence::create(CardinalSplineTo,CCCallFuncND::create(this,callfuncND_selector(PlayLayer::spriteCallBack),(void*)sprite),NULL);
	sprite->runAction(sequence);
}

void PlayLayer::spriteCallBack(CCNode* pSender, void* data)
{
	CCSprite *sprite = (CCSprite*)data;
	sprite->removeFromParent();
}

void PlayLayer::registerWithTouchDispatcher(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}