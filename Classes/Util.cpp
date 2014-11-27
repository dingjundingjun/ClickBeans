#include "Util.h"
UIButton* Util::createUIButton(char* normal,char* press)
{
	UIButton *btn = UIButton::create();
	btn->setTouchEnabled(true);
	btn->loadTextures(normal,press,"");  
	return btn;
}
