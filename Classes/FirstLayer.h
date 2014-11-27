#ifndef _FIRST_LAYER_H_
#define _FIRST_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

class FirstLayer : public cocos2d::CCLayer
{
public:
		FirstLayer();
		~FirstLayer();
		static CCScene* scene();
		CREATE_FUNC(FirstLayer);
		
		virtual bool init();  
		void keyBackClicked();

private:
		UIButton *mStartButton;
		UIButton *mHelpButton;
};

#endif