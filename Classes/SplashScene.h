#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h" 
#include "ui\CocosGUI.h"
#include "MainMenuScene.h"
#include <string>
#include <vector>

using namespace cocos2d;
//using namespace CocosDenshion;
using namespace ui;
using namespace std;

class SplashScreen : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//main game scene callback
	void SelectionMenu(Ref *pSender, Widget::TouchEventType type);
	//auto switchscene 
	void autoSwitchScene(float dt);

	// OBJ Dropdown
	void autoDropDown(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(SplashScreen);

private: 
	float scaleFactorY;
	float scaleFactorX;

	Sprite* SplashBG;
	Sprite* SplashOBJ;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

};

#endif // __MainMenu_SCENE_H__
