#ifndef __LEVEL__SELECTION_H__
#define __LEVEL__SELECTION_H__

#include "cocos2d.h" 
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "MainMenuScene.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class LevelSelection : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	LevelSelection();
	~LevelSelection();

	virtual bool init();
	virtual void update(float dt);

	void goToLevel1(Ref *pSender, Widget::TouchEventType type);
	void goToLevel2(Ref *pSender, Widget::TouchEventType type);
	void goToLevel3(Ref *pSender, Widget::TouchEventType type);
	void goToMenu(Ref *pSender, Widget::TouchEventType type);

	void menuCloseCallback(Ref *pSender, Widget::TouchEventType type);

	CREATE_FUNC(LevelSelection);

private:

	// Setting 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size ratio = Director::getInstance()->getWinSize();

	Button* Level1_Button;
	Button* Level2_Button;
	Button* Level3_Button;
};



#endif#pragma once
