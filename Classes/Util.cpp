#include "Util.h"
UIButton* Util::createUIButton(char* normal,char* press)
{
	UIButton *btn = UIButton::create();
	btn->setTouchEnabled(true);
	btn->loadTextures(normal,press,"");  
	return btn;
}


CCTransitionScene* Util::createSceneAnimaion(int index,CCScene *scene)
{
	CCTransitionScene * reScene = NULL;
	switch(index)
	{
	case SCENE_JUMP:
		{
			reScene = CCTransitionJumpZoom::create(0.5, scene);
			break;
		}
	case SCENE_RADIA_CCW:
		{
			reScene = CCTransitionProgressRadialCCW::create(0.5, scene);
			break;
		}
	}
	//reScene = CCTransitionProgressInOut::create(1, scene);
	return reScene;
}