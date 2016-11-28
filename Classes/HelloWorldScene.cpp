#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
HelloWorld::HelloWorld()
{
	Player = NULL;
	//collectablelayer = NULL;
}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 , origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//Player Init
	Player = new Character();
	Player->Init(R_SOLDIERIDLE, R_SOLDIERUP, R_SOLDIERDOWN, R_SOLDIERLEFT, R_SOLDIERRIGHT, origin.x + visibleSize.width/2, origin.y + visibleSize.height/2, 100, 1, 1);
	this->addChild(Player->GetCharCurrentSprite().getSprite(),0);

	//Tilemap Init
	//Level 1
	level1collidemap = new CCTMXTiledMap();
	level1collidemap->initWithTMXFile(TilemapFileName[L1_COLLIDE]);
	level1collidelayer = level1collidemap->layerNamed("Layer");
	this->addChild(level1collidemap,0);
	level1collectmap = new CCTMXTiledMap();
	level1collectmap->initWithTMXFile(TilemapFileName[L1_COLLECT]);
	level1collectlayer = level1collectmap->layerNamed("Layer");
	this->addChild(level1collectmap, 0);


	InitInputEvents();

	this->scheduleUpdate();

    return true;
}

void HelloWorld::InitInputEvents()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void HelloWorld::update(float dt)
{
	Player->update(dt);
	Player->CollisionCheck(level1collidelayer);	
	Player->CollectionCheck(level1collectlayer);
	
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);   
}

void HelloWorld::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		Player->CharCurrentState = Character::C_WALK_UP;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		Player->CharCurrentState = Character::C_WALK_DOWN;
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		Player->CharCurrentState = Character::C_WALK_LEFT;
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		Player->CharCurrentState = Character::C_WALK_RIGHT;
	}
}
void HelloWorld::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
	return true;
}
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{

}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{

}
void HelloWorld::onMouseMove(cocos2d::Event*)
{

}
void HelloWorld::onMouseUp(cocos2d::Event*)
{

}
void HelloWorld::onMouseDown(cocos2d::Event* event)
{

}
void HelloWorld::onMouseScroll(cocos2d::Event*)
{

}


HelloWorld::~HelloWorld()
{
	if (Player)
	{
		delete Player;
		Player = NULL;
	}
}