#include "LevelSelection.h"
USING_NS_CC;

LevelSelection::LevelSelection() {}
LevelSelection::~LevelSelection() {}

Scene* LevelSelection::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelSelection::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelSelection::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	this->removeAllChildren();

	//Game BackGround
	auto mainBackground = Sprite::create("wp1.jpg");
	mainBackground->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
	mainBackground->setScaleX((ratio.width / mainBackground->getContentSize().width));
	mainBackground->setScaleY((ratio.height / mainBackground->getContentSize().height));
	this->addChild(mainBackground, 0);

	//Level selection buttons init
	Level1_Button = Button::create("Level1.png", "Level1.png");
	Level1_Button->addTouchEventListener(CC_CALLBACK_2(LevelSelection::goToLevel1, this));
	Level1_Button->setPosition(Vec2(origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height * 0.85f));
	Level1_Button->setScale(1);
	Level1_Button->setTag(1);
	this->addChild(Level1_Button);

	Level2_Button = Button::create("Level2.png", "Level2.png");
	Level2_Button->addTouchEventListener(CC_CALLBACK_2(LevelSelection::goToLevel2, this));
	Level2_Button->setPosition(Vec2(origin.x + visibleSize.width * 0.3f, origin.y + visibleSize.height * 0.85f));
	Level2_Button->setScale(1);
	Level2_Button->setTag(2);
	this->addChild(Level2_Button);

	Level3_Button = Button::create("Level3.png", "Level3.png");
	Level3_Button->addTouchEventListener(CC_CALLBACK_2(LevelSelection::goToLevel3, this));
	Level3_Button->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.85f));
	Level3_Button->setScale(1);
	Level3_Button->setTag(3);
	this->addChild(Level3_Button);

	// init border
	auto Borders_Black = Sprite::create("Borders_Black-01.png");
	Borders_Black->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5));
	this->addChild(Borders_Black);

	// init back to menu button
	auto Back = Button::create("Exit_Button.png", "Exit_Muted_Button.png");
	Back->addTouchEventListener(CC_CALLBACK_2(LevelSelection::goToMenu, this));
	Back->setPosition(Vec2(origin.x + visibleSize.width * 0.888f, origin.y + visibleSize.height * 0.8913));
	this->addChild(Back);

	this->scheduleUpdate();

	return true;
}

void LevelSelection::goToLevel1(Ref *pSender, Widget::TouchEventType type)
{
	// when click start, detect which game

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main game
		auto scene = createScene();
		scene = Level1::createScene();

		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		break;
	}
}

void LevelSelection::goToLevel2(Ref *pSender, Widget::TouchEventType type)
{
	// when click start, detect which game

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main game
		auto scene = createScene();
		scene = Level2::createScene();

		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		break;
	}
}

void LevelSelection::goToLevel3(Ref *pSender, Widget::TouchEventType type)
{
	// when click start, detect which game

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main game
		auto scene = createScene();
		scene = Level3::createScene();

		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		break;
	}
}

void LevelSelection::goToMenu(Ref *pSender, Widget::TouchEventType type)
{
	// when click start, detect which game

	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main game
		auto scene = createScene();
		scene = MainMenu::createScene();

		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		break;
	}
}

void LevelSelection::update(float dt)
{
}

void LevelSelection::menuCloseCallback(Ref* pSender, Widget::TouchEventType type)
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