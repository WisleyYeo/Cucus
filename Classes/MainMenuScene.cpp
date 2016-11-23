#include "MainMenuScene.h"
USING_NS_CC;

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	this->removeAllChildren();

	//Game BackGround
	//auto mainBackground = Sprite::create("LevelSelect/LVS_Background-01.png");
	//mainBackground->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
	//mainBackground->setScaleX((ratio.width / mainBackground->getContentSize().width));
	//mainBackground->setScaleY((ratio.height / mainBackground->getContentSize().height));
	//this->addChild(touchObj.mainBackground, 0);

	//Level selection buttons init
	Game1_Button = Button::create("Button_Start.png", "Play_Muted_Button.png");
	Game1_Button->addTouchEventListener(CC_CALLBACK_2(MainMenu::goToGame, this));
	Game1_Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f));
	Game1_Button->setScale(1.25);
	Game1_Button->setTag(1);
	this->addChild(Game1_Button);

	// init border
	auto Borders_Black = Sprite::create("Borders_Black-01.png");
	Borders_Black->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
	this->addChild(Borders_Black);

	// init exit button
	auto Exit = Button::create("Exit_Button.png", "Exit_Muted_Button.png");
	Exit->addTouchEventListener(CC_CALLBACK_2(MainMenu::menuCloseCallback, this));
	Exit->setPosition(Vec2(origin.x + visibleSize.width * 0.888f, origin.y + visibleSize.height * 0.8913));
	this->addChild(Exit);

	// social media
	Fb_Button = Button::create("Button_Facebook.png", "Button_Facebook_Muted.png");
	Fb_Button->addTouchEventListener(CC_CALLBACK_2(MainMenu::linkFb, this));
	Fb_Button->setPosition(Vec2(origin.x + visibleSize.width * 0.787f, origin.y + visibleSize.height * 0.089f));
	this->addChild(Fb_Button);

	Insta_Button = Button::create("Button_Insta.png", "Button_Insta_Muted.png");
	Insta_Button->addTouchEventListener(CC_CALLBACK_2(MainMenu::linkInsta, this));
	Insta_Button->setPosition(Vec2(origin.x + visibleSize.width * 0.928f, origin.y + visibleSize.height * 0.089f));
	this->addChild(Insta_Button);

	this->scheduleUpdate();

	return true;
}

void MainMenu::goToGame(Ref *pSender, Widget::TouchEventType type)
{
	// when click start, detect which game

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main game
		auto scene = createScene();
		scene = HelloWorld::createScene();

		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		break;
	}
}

void MainMenu::update(float dt)
{
}

void MainMenu::menuCloseCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
}

// linking to browser
void MainMenu::linkFb(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:
		
		CCApplication::getInstance()->openURL("https://www.facebook.com/SakaeSushi.sg/");

		break;
	}
}
void MainMenu::linkInsta(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:
		
		CCApplication::getInstance()->openURL("https://www.instagram.com/sakaesushisg/?hl=en");

		break;
	}
}