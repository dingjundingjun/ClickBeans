#ifndef _UTIL_H_
#define _UTIL_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
using namespace cocos2d::extension;

#define GAME_BLOCK_ROW_NUMBER 13
#define GAME_BLOCK_COLUMN_NUMBER 23
#define GAME_BLOCK_WIDTH 40
#define GAME_BLOCK_HEIGHT 40
#define BEANS_NUMBER 200
#define BEANS_TAG 1000
#define ROW_PX 50
#define COLUMN_PX 41
#define BEANS_CLEAR 1000
#define GAME_TIME 3600
#define GAME_WAIT 0
#define GAME_START 1
#define GAME_END 2
#define GAME_EXPLAIN 3

#define SCENE_JUMP 0
#define SCENE_RADIA_CCW 1
static char* BEANS[6] = {"box1.png","box2.png","box3.png","box4.png","box5.png","box6.png"};
static int gGameScore = 0;
class Util
{
public:
	static UIButton* createUIButton(char* normal,char* press);
	static CCTransitionScene* createSceneAnimaion(int index,CCScene *scene);
};
#endif