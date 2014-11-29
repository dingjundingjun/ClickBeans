#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
using namespace cocos2d::extension;

#define GAME_BLOCK_ROW_NUMBER 15
#define GAME_BLOCK_COLUMN_NUMBER 20
#define GAME_BLOCK_WIDTH 48
#define GAME_BLOCK_HEIGHT 48
#define BEANS_NUMBER 200
#define BEANS_TAG 1000
#define ROW_PX 15
#define COLUMN_PX 0
#define BEANS_CLEAR 1000
static char* BEANS[6] = {"box1.png","box2.png","box3.png","box4.png","box5.png","box6.png"};
class Util
{
public:
	static UIButton* createUIButton(char* normal,char* press);
};
#endif