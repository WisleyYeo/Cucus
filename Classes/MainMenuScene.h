#ifndef __MAIN__MENU_H__
#define __MAIN__MENU_H__

#include "cocos2d.h" 
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "LevelSelection.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	MainMenu();
	~MainMenu();

	virtual bool init();
	virtual void update(float dt);

	void goToLevelSelect(Ref *pSender, Widget::TouchEventType type);

	void menuCloseCallback(Ref *pSender, Widget::TouchEventType type);

	void linkFb(Ref *pSender, Widget::TouchEventType type);
	void linkInsta(Ref *pSender, Widget::TouchEventType type);


	CREATE_FUNC(MainMenu);

private:

	// Setting 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size ratio = Director::getInstance()->getWinSize();

	Button* LevelSelect_Button;

	Button* Fb_Button;
	Button* Insta_Button;
};



#endif