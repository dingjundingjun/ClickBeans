#ifndef PLAY_LAYER_H_
#define PLAY_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

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

	virtual bool init();  
	void keyBackClicked();

};

#endif