#include "SplashScene.h"
//#include "TouchSwipe.h"
USING_NS_CC;

Scene* SplashScreen::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SplashScreen::create();
	
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScreen::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//init tonchswipes 

	scaleFactorY = 1.0f;
	scaleFactorX = 1.0f;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size ratio =Director::getInstance()->getWinSize();
	
	// splash image
	SplashBG = Sprite::create("Splash_screen-01.png");
	SplashBG->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
	SplashBG->setScaleX((visibleSize.width / SplashBG->getContentSize().width)*scaleFactorX);
	SplashBG->setScaleY((visibleSize.height / SplashBG->getContentSize().height)*scaleFactorY);
	this->addChild(SplashBG);

	//drop down obj
	SplashOBJ = Sprite::create("Splash_Screen_Title.png");
	//set obj outside of game screen
	SplashOBJ->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 1.5f);
	this->addChild(SplashOBJ);

	// THIS WILL RUN 1.5 SECOND UPON CREATION OF SCENE
	this->scheduleOnce(schedule_selector(SplashScreen::autoDropDown), 0.8f);
	// THIS WILL RUN 5 SECOND UPON CREATION OF SCENE
	this->scheduleOnce(schedule_selector(SplashScreen::autoSwitchScene), 4.3f);
	
	return true;
}

void SplashScreen::autoSwitchScene(float dt)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

void SplashScreen::autoDropDown(float dt)
{
	auto move = MoveBy::create(2, Vec2(origin.x + visibleSize.width * 0.f, origin.y + visibleSize.height * -1.f));
	auto move_ease_in = EaseBounceOut::create(move->clone());
	SplashOBJ->runAction(move_ease_in);
}

void SplashScreen::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
