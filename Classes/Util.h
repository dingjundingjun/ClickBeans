#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
using namespace cocos2d::extension;

#define GAME_BLOCK_ROW_NUMBER 20
#define GAME_BLOCK_COLUMN_NUMBER 15
#define GAME_BLOCK_WIDTH 48
#define GAME_BLOCK_HEIGHT 48
class Util
{
public:
	static UIButton* createUIButton(char* normal,char* press);
};
#endif