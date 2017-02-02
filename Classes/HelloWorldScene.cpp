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

	InitTileMaps();
	InitTurrets();
	InitPlayer();
	InitText();
	InitInputEvents();

	this->scheduleUpdate();

    return true;
}

void HelloWorld::InitTileMaps()
{
	//Tilemap Init
	//Level 1
	level1stage1 = new CCTMXTiledMap();
	level1stage1->initWithTMXFile(TilemapFileName[L1_S1]);
	level1stage1collide = level1stage1->layerNamed("Collide");
	level1stage1health = level1stage1->layerNamed("Health");
	level1stage1speed = level1stage1->layerNamed("Speed");
	level1stage1strength = level1stage1->layerNamed("Strength");
	level1stage1charspawn = level1stage1->layerNamed("CharSpawn");
	level1stage1turretdownspawn = level1stage1->layerNamed("TurretDown");
	level1stage1exit = level1stage1->layerNamed("Exit");
	this->addChild(level1stage1, 0, "Level1Stage1Map");
}
void HelloWorld::InitTurrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	level1stage1TurretDownList.clear();

	Size s = level1stage1turretdownspawn->getLayerSize();
	unsigned int GID = 0;
	if (s.width > 0 && s.height > 0)
	{
		for (int x = 0; x < s.width; ++x)
		{
			for (int y = 0; y < s.height; ++y)
			{
				GID = level1stage1turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID > 0)
				{
					TurretDownPos = level1stage1turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					level1stage1turretdownspawn->setTileGID(level1stage1turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 1);

					//Turret bullet addchild
					for (auto child : TurretDown->getBulletList())
					{
						this->addChild(child, -1);
					}

					level1stage1TurretDownList.pushBack(TurretDown);
				}
			}
		}
	}
}
void HelloWorld::InitPlayer()
{
	//Player Init
	Player = Character::createOBJ();
	Vec2 CharSpawnPos;
	Size s = level1stage1charspawn->getLayerSize();
	unsigned int GID = 0;
	if (s.width > 0 && s.height > 0)
	{
		for (int x = 0; x < s.width; ++x)
		{
			for (int y = 0; y < s.height; ++y)
			{
				GID = level1stage1charspawn->getTileGIDAt(Vec2(x, y));
				if (GID > level1stage1charspawn->getTileSet()->_firstGid)
				{
					CharSpawnPos = level1stage1charspawn->getTileAt(Vec2(x, y))->getPosition();
					level1stage1charspawn->setTileGID(level1stage1charspawn->getTileSet()->_firstGid, Vec2(x, y));
				}
			}
		}
	}
	Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16);
	this->addChild(Player, 0);

	//Player bullet addchild
	for (auto child : Player->getBulletList())
	{
		this->addChild(child, -1);
	}

}
void HelloWorld::InitText()
{
	//Text Labels
	CCLabelTTF* HealthLabel = CCLabelTTF::create("Health: ", "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	HealthLabel->setPosition(Vec2(50, 5));
	this->addChild(HealthLabel, 1);

	HealthValueLabel = CCLabelTTF::create(std::to_string(Player->GetHealth()), "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	HealthValueLabel->setPosition(Vec2(100, 5));
	this->addChild(HealthValueLabel, 1);

	CCLabelTTF* StrengthLabel = CCLabelTTF::create("Strength: ", "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	StrengthLabel->setPosition(Vec2(200, 5));
	this->addChild(StrengthLabel, 1);

	StrengthValueLabel = CCLabelTTF::create(std::to_string(Player->GetStrength()), "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	StrengthValueLabel->setPosition(Vec2(250, 5));
	this->addChild(StrengthValueLabel, 1);

	CCLabelTTF* SpeedLabel = CCLabelTTF::create("Speed: ", "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	SpeedLabel->setPosition(Vec2(350, 5));
	this->addChild(SpeedLabel, 1);

	SpeedValueLabel = CCLabelTTF::create(std::to_string(Player->GetSpeed()), "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	SpeedValueLabel->setPosition(Vec2(400, 5));
	this->addChild(SpeedValueLabel, 1);
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
	//Text value labels update
	HealthValueLabel->setString(std::to_string(Player->GetHealth()));
	StrengthValueLabel->setString(std::to_string(Player->GetStrength()));
	SpeedValueLabel->setString(std::to_string(Player->GetSpeed()));
	updatePlayer(dt);
	updateTurret(dt);
}

void HelloWorld::updatePlayer(float dt)
{
	//Player updates
	Player->update(dt);
	if (this->getChildByName("Level1Stage1Map"))
	{
		Player->CollisionCheck(level1stage1collide);
		Player->HealthPackCheck(level1stage1health);
		Player->SpeedPackCheck(level1stage1speed);
		Player->StrengthPackCheck(level1stage1strength);
		if (Player->ExitCheck(level1stage1exit))
		{
			//Remove relevant childs
			this->removeChildByName("Level1Stage1Map");

			for (auto bullet : Player->getBulletList())
			{
				if (bullet->getActive() == true)
				{
					bullet->setActive(false);
				}
			}
			for (auto turrets : level1stage1TurretDownList)
			{
				for (auto bullet : turrets->getBulletList())
				{
					if (bullet->getActive() == true)
					{
						bullet->setActive(false);
					}
				}
			}
		}
	}

	

	for (auto bullet : Player->getBulletList())
	{
		if (bullet->getActive() == true)
		{
			for (auto turrets : level1stage1TurretDownList)
			{
				// check if damage the player
				turrets->ReceiveDamageCheck(level1stage1turretdownspawn, bullet);
			}
		}
	}
}

void HelloWorld::updateTurret(float dt)
{
	//Turret updates
	if (this->getChildByName("Level1Stage1Map"))
	{
		for (auto turrets : level1stage1TurretDownList)
		{
			turrets->Update(dt);
			turrets->CollisionCheck(level1stage1collide);

			for (auto bullet : turrets->getBulletList())
			{
				if (bullet->getActive() == true)
					// check if damage the player
					Player->ReceiveDamageCheck(bullet);
			}
		}
	}
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
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		
	}
}
void HelloWorld::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D && Player->IsMoving())
	{
		Player->CharCurrentState = Character::C_IDLE;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		Player->CharCurrentState = Character::C_SHOOT;
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
}