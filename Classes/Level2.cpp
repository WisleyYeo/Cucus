﻿#include "Level2.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
Level2::Level2()
{
	Player = NULL;
	//collectablelayer = NULL;
}
Scene* Level2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Level2::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool Level2::init()
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
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Level2::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 , origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	InitPause();
	InitTileMaps();
	InitTurrets();
	InitPlayer();
	InitText();
	InitInputEvents();

	this->scheduleUpdate();

    return true;
}

void Level2::InitTileMaps()
{
	//Tilemap Init
	//Level 1
	Level2stage1 = new CCTMXTiledMap();
	Level2stage1->initWithTMXFile(TilemapFileName[L2_S1]);
	Level2stage1collide = Level2stage1->layerNamed("Collide");
	Level2stage1health = Level2stage1->layerNamed("Health");
	Level2stage1speed = Level2stage1->layerNamed("Speed");
	Level2stage1strength = Level2stage1->layerNamed("Strength");
	Level2stage1charspawn = Level2stage1->layerNamed("CharSpawn");
	Level2stage1turretdownspawn = Level2stage1->layerNamed("TurretDown");
	Level2stage1exit = Level2stage1->layerNamed("Exit");
	this->addChild(Level2stage1, 0, "Level2Stage1Map");
	//Level 2
	Level2stage2 = new CCTMXTiledMap();
	Level2stage2->initWithTMXFile(TilemapFileName[L2_S2]);
	Level2stage2collide = Level2stage2->layerNamed("Collide");
	Level2stage2health = Level2stage2->layerNamed("Health");
	Level2stage2speed = Level2stage2->layerNamed("Speed");
	Level2stage2strength = Level2stage2->layerNamed("Strength");
	Level2stage2charspawn = Level2stage2->layerNamed("CharSpawn");
	Level2stage2turretdownspawn = Level2stage2->layerNamed("TurretDown");
	Level2stage2exit = Level2stage2->layerNamed("Exit");
	//Level 3
	Level2stage3 = new CCTMXTiledMap();
	Level2stage3->initWithTMXFile(TilemapFileName[L2_S3]);
	Level2stage3collide = Level2stage3->layerNamed("Collide");
	Level2stage3health = Level2stage3->layerNamed("Health");
	Level2stage3speed = Level2stage3->layerNamed("Speed");
	Level2stage3strength = Level2stage3->layerNamed("Strength");
	Level2stage3charspawn = Level2stage3->layerNamed("CharSpawn");
	Level2stage3turretdownspawn = Level2stage3->layerNamed("TurretDown");
	Level2stage3exit = Level2stage3->layerNamed("Exit");
}
void Level2::InitTurrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	Level2stage1TurretDownList.clear();

	Size s = Level2stage1turretdownspawn->getLayerSize();
	unsigned int GID = 0;
	if (s.width > 0 && s.height > 0)
	{
		for (int x = 0; x < s.width; ++x)
		{
			for (int y = 0; y < s.height; ++y)
			{
				GID = Level2stage1turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID > 0)
				{
					TurretDownPos = Level2stage1turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage1turretdownspawn->setTileGID(Level2stage1turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 1);

					//Turret bullet addchild
					for (auto child : TurretDown->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage1TurretDownList.pushBack(TurretDown);
				}
			}
		}
	}
}
void Level2::InitPlayer()
{
	//Player Init
	Player = Character::createOBJ();
	Vec2 CharSpawnPos;
	Size s = Level2stage1charspawn->getLayerSize();
	unsigned int GID = 0;
	if (s.width > 0 && s.height > 0)
	{
		for (int x = 0; x < s.width; ++x)
		{
			for (int y = 0; y < s.height; ++y)
			{
				GID = Level2stage1charspawn->getTileGIDAt(Vec2(x, y));
				if (GID > Level2stage1charspawn->getTileSet()->_firstGid)
				{
					CharSpawnPos = Level2stage1charspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage1charspawn->setTileGID(Level2stage1charspawn->getTileSet()->_firstGid, Vec2(x, y));
				}
			}
		}
	}
	Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16, 100, 1, 50);
	this->addChild(Player, 0);


	//Player bullet addchild
	for (auto child : Player->getBulletList())
	{
		this->addChild(child, -1);
	}
}
void Level2::InitText()
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
void Level2::InitInputEvents()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Level2::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Level2::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Level2::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Level2::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Level2::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Level2::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Level2::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(Level2::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(Level2::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
void Level2::InitPause()
{
	paused = false;

	//pause button
	pauseButton = Button::create("pauseButton.png", "pauseButtonPressed.png");
	pauseButton->setPosition(Vec2(origin.x + visibleSize.width * 0.9f, origin.y + visibleSize.height * 0.9f));
	pauseButton->addTouchEventListener(CC_CALLBACK_2(Level2::PauseGame, this));
	this->addChild(pauseButton, 1);

	//pause window
	pauseWindow = Sprite::create("windowPanel.png");
	pauseWindow->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
	this->addChild(pauseWindow, 2);

	//resume and quit buttons
	resumeButton = Button::create("buttonNormal.png", "buttonSelected.png");
	resumeButton->setTitleText("Resume");
	resumeButton->setTitleFontName("font_motionControl.ttf");
	resumeButton->setTitleFontSize(72);
	resumeButton->setTitleColor(Color3B::WHITE);
	resumeButton->getTitleRenderer()->enableShadow(Color4B(64, 64, 64, 255), Size(4, -4), 4);
	resumeButton->getTitleRenderer()->enableOutline(Color4B(64, 64, 64, 255), 4);
	resumeButton->addTouchEventListener(CC_CALLBACK_2(Level2::ResumeGame, this));
	resumeButton->setPosition(Vec2(origin.x + visibleSize.width * 0.35f, origin.y + visibleSize.height * 0.4f));
	resumeButton->setScale(0.5);
	pauseWindow->addChild(resumeButton);

	quitButton = Button::create("buttonNormal.png", "buttonSelected.png");
	quitButton->setTitleText("Quit");
	quitButton->setTitleFontName("font_motionControl.ttf");
	quitButton->setTitleFontSize(72);
	quitButton->setTitleColor(Color3B::WHITE);
	quitButton->getTitleRenderer()->enableShadow(Color4B(64, 64, 64, 255), Size(4, -4), 4);
	quitButton->getTitleRenderer()->enableOutline(Color4B(64, 64, 64, 255), 4);
	quitButton->addTouchEventListener(CC_CALLBACK_2(Level2::ToMainMenu, this));
	quitButton->setPosition(Vec2(origin.x + visibleSize.width * 0.35f, origin.y + visibleSize.height * 0.3f));
	quitButton->setScale(0.5);
	pauseWindow->addChild(quitButton);

	//set pause window outside of game screen
	pauseWindow->setPosition(origin.x + visibleSize.width * 2, origin.y + visibleSize.height * 0.5f);
}

void Level2::update(float dt)
{
	if (!paused)
	{
		//Text value labels update
		HealthValueLabel->setString(std::to_string(Player->GetHealth()));
		StrengthValueLabel->setString(std::to_string(Player->GetStrength()));
		SpeedValueLabel->setString(std::to_string(Player->GetSpeed()));
		updatePlayer(dt);
		updateTurret(dt);
	}
}
void Level2::updatePlayer(float dt)
{
	//Player updates
	Player->update(dt);
	if (this->getChildByName("Level2Stage1Map"))
	{
		Player->CollisionCheck(Level2stage1collide);
		Player->HealthPackCheck(Level2stage1health);
		Player->SpeedPackCheck(Level2stage1speed);
		Player->StrengthPackCheck(Level2stage1strength);

		for (auto bullet : Player->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				for (auto turrets : Level2stage1TurretDownList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage1turretdownspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level2stage1exit))
		{
			//Remove relevant childs
			this->removeChildByName("Level2Stage1Map");
			for (auto bullet : Player->getBulletList())
			{
				if (bullet->getActive() == true)
				{
					bullet->destroy();
				}
			}
			for (auto turrets : Level2stage1TurretDownList)
			{
				for (auto bullet : turrets->getBulletList())
				{
					if (bullet->getActive() == true)
					{
						bullet->destroy();
					}
				}
			}

			//Set player position 
			Vec2 CharSpawnPos;
			Size s = Level2stage2charspawn->getLayerSize();
			unsigned int GID = 0;
			if (s.width > 0 && s.height > 0)
			{
				for (int x = 0; x < s.width; ++x)
				{
					for (int y = 0; y < s.height; ++y)
					{
						GID = Level2stage2charspawn->getTileGIDAt(Vec2(x, y));
						if (GID > Level2stage2charspawn->getTileSet()->_firstGid)
						{
							CharSpawnPos = Level2stage2charspawn->getTileAt(Vec2(x, y))->getPosition();
							Level2stage2charspawn->setTileGID(Level2stage2charspawn->getTileSet()->_firstGid, Vec2(x, y));
						}
					}
				}
			}
			Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16, 100, 1, 50);
			//Load next stage
			this->addChild(Level2stage2, 0, "Level2Stage2Map");
			//Turret Down Init
			Vec2 TurretDownPos;
			Level2stage2TurretDownList.clear();

			s = Level2stage2turretdownspawn->getLayerSize();
			GID = 0;
			if (s.width > 0 && s.height > 0)
			{
				for (int x = 0; x < s.width; ++x)
				{
					for (int y = 0; y < s.height; ++y)
					{
						GID = Level2stage2turretdownspawn->getTileGIDAt(Vec2(x, y));
						if (GID > 0)
						{
							TurretDownPos = Level2stage2turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
							Level2stage2turretdownspawn->setTileGID(Level2stage2turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
							Turret* TurretDown = new Turret();
							TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 1);

							//Turret bullet addchild
							for (auto child : TurretDown->getBulletList())
							{
								this->addChild(child, -1);
							}

							Level2stage2TurretDownList.pushBack(TurretDown);
						}
					}
				}
			}
		}
	}
	if (this->getChildByName("Level2Stage2Map"))
	{
		Player->CollisionCheck(Level2stage2collide);
		Player->HealthPackCheck(Level2stage2health);
		Player->SpeedPackCheck(Level2stage2speed);
		Player->StrengthPackCheck(Level2stage2strength);

		for (auto bullet : Player->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				for (auto turrets : Level2stage2TurretDownList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage2turretdownspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level2stage2exit))
		{
			//Remove relevant childs
			this->removeChildByName("Level2Stage2Map");
			for (auto bullet : Player->getBulletList())
			{
				if (bullet->getActive() == true)
				{
					bullet->destroy();
				}
			}
			for (auto turrets : Level2stage2TurretDownList)
			{
				for (auto bullet : turrets->getBulletList())
				{
					if (bullet->getActive() == true)
					{
						bullet->destroy();
					}
				}
			}

			//Set player position 
			Vec2 CharSpawnPos;
			Size s = Level2stage3charspawn->getLayerSize();
			unsigned int GID = 0;
			if (s.width > 0 && s.height > 0)
			{
				for (int x = 0; x < s.width; ++x)
				{
					for (int y = 0; y < s.height; ++y)
					{
						GID = Level2stage3charspawn->getTileGIDAt(Vec2(x, y));
						if (GID > Level2stage3charspawn->getTileSet()->_firstGid)
						{
							CharSpawnPos = Level2stage3charspawn->getTileAt(Vec2(x, y))->getPosition();
							Level2stage3charspawn->setTileGID(Level2stage3charspawn->getTileSet()->_firstGid, Vec2(x, y));
						}
					}
				}
			}
			Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16, 100, 1, 50);

			//Load next stage
			this->addChild(Level2stage3, 0, "Level2Stage3Map");
			//Turret Down Init
			Vec2 TurretDownPos;
			Level2stage2TurretDownList.clear();

			s = Level2stage3turretdownspawn->getLayerSize();
			GID = 0;
			if (s.width > 0 && s.height > 0)
			{
				for (int x = 0; x < s.width; ++x)
				{
					for (int y = 0; y < s.height; ++y)
					{
						GID = Level2stage3turretdownspawn->getTileGIDAt(Vec2(x, y));
						if (GID > 0)
						{
							TurretDownPos = Level2stage3turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
							Level2stage3turretdownspawn->setTileGID(Level2stage3turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
							Turret* TurretDown = new Turret();
							TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 1);

							//Turret bullet addchild
							for (auto child : TurretDown->getBulletList())
							{
								this->addChild(child, -1);
							}

							Level2stage3TurretDownList.pushBack(TurretDown);
						}
					}
				}
			}
		}

	}
	if (this->getChildByName("Level2Stage3Map"))
	{
		Player->CollisionCheck(Level2stage3collide);
		Player->HealthPackCheck(Level2stage3health);
		Player->SpeedPackCheck(Level2stage3speed);
		Player->StrengthPackCheck(Level2stage3strength);

		for (auto bullet : Player->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				for (auto turrets : Level2stage3TurretDownList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage3turretdownspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level2stage3exit))
		{
			//Since last stage, go back to level selection
		}
	}
}
void Level2::updateTurret(float dt)
{
	//Turret updates
	if (this->getChildByName("Level2Stage1Map"))
	{
		for (auto turrets : Level2stage1TurretDownList)
		{
			turrets->Update(dt);
			turrets->CollisionCheck(Level2stage1collide);

			for (auto bullet : turrets->getBulletList())
			{
				if (bullet->getActive() == true)
					// check if damage the player
					Player->ReceiveDamageCheck(bullet);
			}
		}
	}
	if (this->getChildByName("Level2Stage2Map"))
	{
		for (auto turrets : Level2stage2TurretDownList)
		{
			turrets->Update(dt);
			turrets->CollisionCheck(Level2stage2collide);

			for (auto bullet : turrets->getBulletList())
			{
				if (bullet->getActive() == true)
					// check if damage the player
					Player->ReceiveDamageCheck(bullet);
			}
		}
	}
	if (this->getChildByName("Level2Stage3Map"))
	{
		for (auto turrets : Level2stage3TurretDownList)
		{
			turrets->Update(dt);
			turrets->CollisionCheck(Level2stage3collide);

			for (auto bullet : turrets->getBulletList())
			{
				if (bullet->getActive() == true)
					// check if damage the player
					Player->ReceiveDamageCheck(bullet);
			}
		}
	}
}

void Level2::PauseGame(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//move the pause window down
		auto moveDown = MoveTo::create(0.5f, Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f));
		pauseWindow->runAction(EaseBackOut::create(moveDown));

		//pause all in game stuff including inputs
		paused = true;

		//pasue all button
		pauseButton->pause();

		break;
	}
}
void Level2::ResumeGame(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//move the pause window up
		auto moveUp = MoveTo::create(0.5f, Vec2(origin.x + visibleSize.width * 2, origin.y + visibleSize.height * 0.5f));
		pauseWindow->runAction(EaseBackIn::create(moveUp));

		//resume all in game stuff including inputs
		paused = false;

		//resume the buttons
		pauseButton->resume();

		break;
	}
}
void Level2::ToMainMenu(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main menu scene
		auto scene = MainMenu::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));

		break;
	}
}
void Level2::RestartGame(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main game scene
		auto scene = Level1::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, scene));

		break;
	}
}

void Level2::menuCloseCallback(Ref* pSender)
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

void Level2::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (!paused)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			Player->CharCurrentState = Character::C_WALK_UP;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			Player->CharCurrentState = Character::C_WALK_DOWN;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			Player->CharCurrentState = Character::C_WALK_LEFT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			Player->CharCurrentState = Character::C_WALK_RIGHT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{

		}
	}
}
void Level2::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (!paused)
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
}

bool Level2::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
	return true;
}
void Level2::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{

}
void Level2::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{

}
void Level2::onMouseMove(cocos2d::Event*)
{

}
void Level2::onMouseUp(cocos2d::Event*)
{

}
void Level2::onMouseDown(cocos2d::Event* event)
{

}
void Level2::onMouseScroll(cocos2d::Event*)
{

}

Level2::~Level2()
{
}