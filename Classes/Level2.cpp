#include "Level2.h"
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

	layer->setCameraMask(2, true);
	// add layer as a child to scene
	scene->addChild(layer, 0, "Layer");

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool Level2::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	InitTileMaps();
	InitStage1Turrets();
	InitPlayer();
	InitZoomedCamera();
	InitPause();
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
	Level2stage1turretleftspawn = Level2stage1->layerNamed("TurretLeft");
	Level2stage1turretrightspawn = Level2stage1->layerNamed("TurretRight");
	Level2stage1turretupspawn = Level2stage1->layerNamed("TurretUp");
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
	Level2stage2turretleftspawn = Level2stage2->layerNamed("TurretLeft");
	Level2stage2turretrightspawn = Level2stage2->layerNamed("TurretRight");
	Level2stage2turretupspawn = Level2stage2->layerNamed("TurretUp");
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
	Level2stage3turretleftspawn = Level2stage3->layerNamed("TurretLeft");
	Level2stage3turretrightspawn = Level2stage3->layerNamed("TurretRight");
	Level2stage3turretupspawn = Level2stage3->layerNamed("TurretUp");
	Level2stage3exit = Level2stage3->layerNamed("Exit");
}
void Level2::InitStage1Turrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	Level2stage1TurretDownList.clear();

	Size s1 = Level2stage1turretdownspawn->getLayerSize();
	unsigned int GID1 = 0;
	if (s1.width > 0 && s1.height > 0)
	{
		for (int x = 0; x < s1.width; ++x)
		{
			for (int y = 0; y < s1.height; ++y)
			{
				GID1 = Level2stage1turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID1 > 0)
				{
					TurretDownPos = Level2stage1turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage1turretdownspawn->setTileGID(Level2stage1turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 2.5);

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

	//Turret Left Init
	Vec2 TurretLeftPos;
	Level2stage1TurretLeftList.clear();

	Size s2 = Level2stage1turretleftspawn->getLayerSize();
	unsigned int GID2 = 0;
	if (s2.width > 0 && s2.height > 0)
	{
		for (int x = 0; x < s2.width; ++x)
		{
			for (int y = 0; y < s2.height; ++y)
			{
				GID2 = Level2stage1turretleftspawn->getTileGIDAt(Vec2(x, y));
				if (GID2 > 0)
				{
					TurretLeftPos = Level2stage1turretleftspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage1turretleftspawn->setTileGID(Level2stage1turretleftspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretLeft = new Turret();
					TurretLeft->Init(TurretLeftPos.x + 16, TurretLeftPos.y + 16, Vec2(-1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretLeft->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage1TurretDownList.pushBack(TurretLeft);
				}
			}
		}
	}

	//Turret Right Init
	Vec2 TurretRightPos;
	Level2stage1TurretRightList.clear();

	Size s3 = Level2stage1turretrightspawn->getLayerSize();
	unsigned int GID3 = 0;
	if (s3.width > 0 && s3.height > 0)
	{
		for (int x = 0; x < s3.width; ++x)
		{
			for (int y = 0; y < s3.height; ++y)
			{
				GID3 = Level2stage1turretrightspawn->getTileGIDAt(Vec2(x, y));
				if (GID3 > 0)
				{
					TurretRightPos = Level2stage1turretrightspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage1turretrightspawn->setTileGID(Level2stage1turretrightspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretright = new Turret();
					Turretright->Init(TurretRightPos.x + 16, TurretRightPos.y + 16, Vec2(1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretright->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage1TurretRightList.pushBack(Turretright);
				}
			}
		}
	}

	//Turret Up Init
	Vec2 TurretUpPos;
	Level2stage1TurretUpList.clear();

	Size s4 = Level2stage1turretupspawn->getLayerSize();
	unsigned int GID4 = 0;
	if (s4.width > 0 && s4.height > 0)
	{
		for (int x = 0; x < s4.width; ++x)
		{
			for (int y = 0; y < s4.height; ++y)
			{
				GID4 = Level2stage1turretupspawn->getTileGIDAt(Vec2(x, y));
				if (GID4 > 0)
				{
					TurretUpPos = Level2stage1turretupspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage1turretupspawn->setTileGID(Level2stage1turretupspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretup = new Turret();
					Turretup->Init(TurretUpPos.x + 16, TurretUpPos.y + 16, Vec2(0, 1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretup->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage1TurretUpList.pushBack(Turretup);
				}
			}
		}
	}
}
void Level2::InitStage2Turrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	Level2stage2TurretDownList.clear();

	Size s1 = Level2stage2turretdownspawn->getLayerSize();
	unsigned int GID1 = 0;
	if (s1.width > 0 && s1.height > 0)
	{
		for (int x = 0; x < s1.width; ++x)
		{
			for (int y = 0; y < s1.height; ++y)
			{
				GID1 = Level2stage2turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID1 > 0)
				{
					TurretDownPos = Level2stage2turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage2turretdownspawn->setTileGID(Level2stage2turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 2.5);

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

	//Turret Left Init
	Vec2 TurretLeftPos;
	Level2stage2TurretLeftList.clear();

	Size s2 = Level2stage2turretleftspawn->getLayerSize();
	unsigned int GID2 = 0;
	if (s2.width > 0 && s2.height > 0)
	{
		for (int x = 0; x < s2.width; ++x)
		{
			for (int y = 0; y < s2.height; ++y)
			{
				GID2 = Level2stage2turretleftspawn->getTileGIDAt(Vec2(x, y));
				if (GID2 > 0)
				{
					TurretLeftPos = Level2stage2turretleftspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage2turretleftspawn->setTileGID(Level2stage2turretleftspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretLeft = new Turret();
					TurretLeft->Init(TurretLeftPos.x + 16, TurretLeftPos.y + 16, Vec2(-1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretLeft->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage2TurretLeftList.pushBack(TurretLeft);
				}
			}
		}
	}

	//Turret Right Init
	Vec2 TurretRightPos;
	Level2stage2TurretRightList.clear();

	Size s3 = Level2stage2turretrightspawn->getLayerSize();
	unsigned int GID3 = 0;
	if (s3.width > 0 && s3.height > 0)
	{
		for (int x = 0; x < s3.width; ++x)
		{
			for (int y = 0; y < s3.height; ++y)
			{
				GID3 = Level2stage2turretrightspawn->getTileGIDAt(Vec2(x, y));
				if (GID3 > 0)
				{
					TurretRightPos = Level2stage2turretrightspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage2turretrightspawn->setTileGID(Level2stage2turretrightspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretright = new Turret();
					Turretright->Init(TurretRightPos.x + 16, TurretRightPos.y + 16, Vec2(1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretright->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage2TurretRightList.pushBack(Turretright);
				}
			}
		}
	}

	//Turret Up Init
	Vec2 TurretUpPos;
	Level2stage2TurretUpList.clear();

	Size s4 = Level2stage2turretupspawn->getLayerSize();
	unsigned int GID4 = 0;
	if (s4.width > 0 && s4.height > 0)
	{
		for (int x = 0; x < s4.width; ++x)
		{
			for (int y = 0; y < s4.height; ++y)
			{
				GID4 = Level2stage2turretupspawn->getTileGIDAt(Vec2(x, y));
				if (GID4 > 0)
				{
					TurretUpPos = Level2stage2turretupspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage2turretupspawn->setTileGID(Level2stage2turretupspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretup = new Turret();
					Turretup->Init(TurretUpPos.x + 16, TurretUpPos.y + 16, Vec2(0, 1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretup->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage2TurretUpList.pushBack(Turretup);
				}
			}
		}
	}
}
void Level2::InitStage3Turrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	Level2stage3TurretDownList.clear();

	Size s1 = Level2stage3turretdownspawn->getLayerSize();
	unsigned int GID1 = 0;
	if (s1.width > 0 && s1.height > 0)
	{
		for (int x = 0; x < s1.width; ++x)
		{
			for (int y = 0; y < s1.height; ++y)
			{
				GID1 = Level2stage3turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID1 > 0)
				{
					TurretDownPos = Level2stage3turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage3turretdownspawn->setTileGID(Level2stage3turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 2.5);

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

	//Turret Left Init
	Vec2 TurretLeftPos;
	Level2stage3TurretLeftList.clear();

	Size s2 = Level2stage3turretleftspawn->getLayerSize();
	unsigned int GID2 = 0;
	if (s2.width > 0 && s2.height > 0)
	{
		for (int x = 0; x < s2.width; ++x)
		{
			for (int y = 0; y < s2.height; ++y)
			{
				GID2 = Level2stage3turretleftspawn->getTileGIDAt(Vec2(x, y));
				if (GID2 > 0)
				{
					TurretLeftPos = Level2stage3turretleftspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage3turretleftspawn->setTileGID(Level2stage3turretleftspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretLeft = new Turret();
					TurretLeft->Init(TurretLeftPos.x + 16, TurretLeftPos.y + 16, Vec2(-1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretLeft->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage3TurretLeftList.pushBack(TurretLeft);
				}
			}
		}
	}

	//Turret Right Init
	Vec2 TurretRightPos;
	Level2stage3TurretRightList.clear();

	Size s3 = Level2stage3turretrightspawn->getLayerSize();
	unsigned int GID3 = 0;
	if (s3.width > 0 && s3.height > 0)
	{
		for (int x = 0; x < s3.width; ++x)
		{
			for (int y = 0; y < s3.height; ++y)
			{
				GID3 = Level2stage3turretrightspawn->getTileGIDAt(Vec2(x, y));
				if (GID3 > 0)
				{
					TurretRightPos = Level2stage3turretrightspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage3turretrightspawn->setTileGID(Level2stage3turretrightspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretright = new Turret();
					Turretright->Init(TurretRightPos.x + 16, TurretRightPos.y + 16, Vec2(1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretright->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage3TurretRightList.pushBack(Turretright);
				}
			}
		}
	}

	//Turret Up Init
	Vec2 TurretUpPos;
	Level2stage3TurretUpList.clear();

	Size s4 = Level2stage3turretupspawn->getLayerSize();
	unsigned int GID4 = 0;
	if (s4.width > 0 && s4.height > 0)
	{
		for (int x = 0; x < s4.width; ++x)
		{
			for (int y = 0; y < s4.height; ++y)
			{
				GID4 = Level2stage3turretupspawn->getTileGIDAt(Vec2(x, y));
				if (GID4 > 0)
				{
					TurretUpPos = Level2stage3turretupspawn->getTileAt(Vec2(x, y))->getPosition();
					Level2stage3turretupspawn->setTileGID(Level2stage3turretupspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretup = new Turret();
					Turretup->Init(TurretUpPos.x + 16, TurretUpPos.y + 16, Vec2(0, 1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretup->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level2stage3TurretUpList.pushBack(Turretup);
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
	Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16);
	this->addChild(Player, 0, "Player");

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
	HealthLabel->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 50.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));
	this->addChild(HealthLabel, 2, 42);

	HealthValueLabel = CCLabelTTF::create(std::to_string(Player->GetHealth()), "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	HealthValueLabel->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 100.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));
	this->addChild(HealthValueLabel, 1, 43);

	CCLabelTTF* StrengthLabel = CCLabelTTF::create("Strength: ", "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	StrengthLabel->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 200.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));
	this->addChild(StrengthLabel, 1, 44);

	StrengthValueLabel = CCLabelTTF::create(std::to_string(Player->GetStrength()), "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	StrengthValueLabel->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 250.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));
	this->addChild(StrengthValueLabel, 1, 45);

	CCLabelTTF* SpeedLabel = CCLabelTTF::create("Speed: ", "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	SpeedLabel->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 350.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));
	this->addChild(SpeedLabel, 1, 46);

	SpeedValueLabel = CCLabelTTF::create(std::to_string(Player->GetSpeed()), "Fixedsys", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);
	SpeedValueLabel->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 400.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));
	this->addChild(SpeedValueLabel, 1, 47);

	for (int i = 42; i <= 47; i++)
	{
		LabelTags.push_back(i);
	}

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
	pauseButton->setScale(0.3);
	pauseButton->addTouchEventListener(CC_CALLBACK_2(Level2::PauseGame, this));
	this->addChild(pauseButton, 1, "PauseButton");
	pauseButton->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 450.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f + 350.0f));

	//pause window
	pauseWindow = Sprite::create("windowPanel.png");
	pauseWindow->setScale(0.5);
	pauseWindow->setPosition(Player->GetPosition().x * 2, Player->GetPosition().y);
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
}
void Level2::InitZoomedCamera()
{
	auto ss = Director::getInstance()->getWinSize();
	auto cam = Camera::createOrthographic(ss.width * 0.5f, ss.height * 0.5f, 1, 1000);

	cam->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
	cam->setCameraFlag(CameraFlag::USER1);

	this->addChild(cam, 1, "Camera");
}

void Level2::DestroyStage1Bullets()
{
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
	for (auto turrets : Level2stage1TurretLeftList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level2stage1TurretRightList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level2stage1TurretUpList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
}
void Level2::DestroyStage2Bullets()
{
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
	for (auto turrets : Level2stage2TurretLeftList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level2stage2TurretRightList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level2stage2TurretUpList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
}
void Level2::DestroyStage3Bullets()
{
	for (auto bullet : Player->getBulletList())
	{
		if (bullet->getActive() == true)
		{
			bullet->destroy();
		}
	}
	for (auto turrets : Level2stage3TurretDownList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level2stage3TurretLeftList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level2stage3TurretRightList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level2stage3TurretUpList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
}

void Level2::update(float dt)
{
	if (!paused)
	{
		//Text value labels update
		HealthValueLabel->setString(std::to_string(Player->GetHealth()));
		StrengthValueLabel->setString(std::to_string(Player->GetStrength()));
		SpeedValueLabel->setString(std::to_string(Player->GetSpeed()));
		if (this->getChildByName("Player"))
			updatePlayer(dt);
		updateTurret(dt);
	}
}
void Level2::updatePlayer(float dt)
{
	//Player updates
	Player->update(dt);
	updateHUD(dt);
	if (this->getChildByName("Level2Stage1Map"))
	{

		auto ss = Director::getInstance()->getWinSize();
		this->getChildByName("Camera")->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
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
				for (auto turrets : Level2stage1TurretLeftList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage1turretleftspawn, bullet);
				}
				for (auto turrets : Level2stage1TurretRightList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage1turretrightspawn, bullet);
				}
				for (auto turrets : Level2stage1TurretUpList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage1turretupspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level2stage1exit))
		{
			//Remove relevant childs
			this->removeChildByName("Level2Stage1Map");
			this->removeChildByName("Camera");
			this->getScene()->getChildByName("Layer")->setCameraMask(2, false);

			DestroyStage1Bullets();

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

			Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16);
			//Load next stage
			this->addChild(Level2stage2, 0, "Level2Stage2Map");

			InitStage2Turrets();

			auto ss = Director::getInstance()->getWinSize();
			auto cam = Camera::createOrthographic(ss.width * 0.5f, ss.height * 0.5f, 1, 1000);

			cam->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
			cam->setCameraFlag(CameraFlag::USER1);

			this->addChild(cam, 1, "Camera");
			this->getScene()->getChildByName("Layer")->setCameraMask(2, true);

			//Move Text Labels
			this->getChildByTag(42)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 50.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(43)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 100.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(44)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 200.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(45)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 250.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(46)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 350.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(47)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 400.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			//Move Pause Button
			this->getChildByName("PauseButton")->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 450.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f + 350.0f));
		}
	}
	if (this->getChildByName("Level2Stage2Map"))
	{
		auto ss = Director::getInstance()->getWinSize();
		this->getChildByName("Camera")->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
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
				for (auto turrets : Level2stage2TurretLeftList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage2turretleftspawn, bullet);
				}
				for (auto turrets : Level2stage2TurretRightList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage2turretrightspawn, bullet);
				}
				for (auto turrets : Level2stage2TurretUpList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage2turretupspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level2stage2exit))
		{
			//Remove relevant childs
			this->removeChildByName("Level2Stage1Map");
			this->removeChildByName("Camera");
			this->getScene()->getChildByName("Layer")->setCameraMask(2, false);
			this->removeChildByName("Level2Stage2Map");

			DestroyStage2Bullets();

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
			Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16);

			//Load next stage
			this->addChild(Level2stage3, 0, "Level2Stage3Map");

			InitStage3Turrets();

			auto ss = Director::getInstance()->getWinSize();
			auto cam = Camera::createOrthographic(ss.width * 0.5f, ss.height * 0.5f, 1, 1000);

			cam->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
			cam->setCameraFlag(CameraFlag::USER1);

			this->addChild(cam, 1, "Camera");

			this->getScene()->getChildByName("Layer")->setCameraMask(2, true);

			//Move Text Labels
			this->getChildByTag(42)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 50.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(43)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 100.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(44)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 200.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(45)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 250.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(46)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 350.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			this->getChildByTag(47)->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 400.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f));

			//Move Pause Button
			this->getChildByName("PauseButton")->setPosition(Vec2(Player->GetPosition().x - Director::getInstance()->getWinSize().width * 0.5f * 0.5f + 450.0f, Player->GetPosition().y - Director::getInstance()->getWinSize().height * 0.5f * 0.5f + 350.0f));
		}

	}
	if (this->getChildByName("Level2Stage3Map"))
	{
		auto ss = Director::getInstance()->getWinSize();
		this->getChildByName("Camera")->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
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
				for (auto turrets : Level2stage3TurretLeftList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage3turretleftspawn, bullet);
				}
				for (auto turrets : Level2stage3TurretRightList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage3turretrightspawn, bullet);
				}
				for (auto turrets : Level2stage3TurretUpList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level2stage3turretupspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level2stage3exit))
		{
			//Since last stage, go back to level selection
			auto scene = createScene();
			scene = LevelSelection::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	}
}

void Level2::updateStage1Turrets(float dt)
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
	for (auto turrets : Level2stage1TurretLeftList)
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
	for (auto turrets : Level2stage1TurretRightList)
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
	for (auto turrets : Level2stage1TurretUpList)
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
void Level2::updateStage2Turrets(float dt)
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
	for (auto turrets : Level2stage2TurretLeftList)
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
	for (auto turrets : Level2stage2TurretRightList)
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
	for (auto turrets : Level2stage2TurretUpList)
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
void Level2::updateStage3Turrets(float dt)
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
	for (auto turrets : Level2stage3TurretLeftList)
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
	for (auto turrets : Level2stage3TurretRightList)
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
	for (auto turrets : Level2stage3TurretUpList)
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

void Level2::updateTurret(float dt)
{
	//Turret updates
	if (this->getChildByName("Level2Stage1Map"))
	{
		updateStage1Turrets(dt);
	}
	if (this->getChildByName("Level2Stage2Map"))
	{
		updateStage2Turrets(dt);
	}
	if (this->getChildByName("Level2Stage3Map"))
	{
		updateStage3Turrets(dt);
	}
}
void Level2::updateHUD(float dt)
{
	if (Player->Moving())
	{
		//Move Text Labels
		for (int i = 0; i < LabelTags.size(); i++)
		{
			Vec2 newPosition = this->getChildByTag(LabelTags[i])->getPosition();
			newPosition += (Player->GetDirection() * Player->GetSpeed() * dt);
			this->getChildByTag(LabelTags[i])->setPosition(newPosition);
		}
		//Move Pause Button
		Vec2 newPosition = this->getChildByName("PauseButton")->getPosition();
		newPosition += (Player->GetDirection() * Player->GetSpeed() * dt);
		this->getChildByName("PauseButton")->setPosition(newPosition);
	}
}
void Level2::PauseGame(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		Player->CharCurrentState = Character::C_IDLE;
		//move the pause window down
		pauseWindow->setPosition(Vec2(Player->GetPosition().x * 2, Player->GetPosition().y));
		auto moveDown = MoveTo::create(0.5f, Vec2(Player->GetPosition().x, Player->GetPosition().y));
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
		auto moveUp = MoveTo::create(0.5f, Vec2(Player->GetPosition().x * 2, Player->GetPosition().y));
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
		auto scene = Level2::createScene();
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
			Player->stopAllActions();
			Player->SetAnimTrigger(false);
			Player->CharCurrentState = Character::C_WALK_UP;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			Player->stopAllActions();
			Player->SetAnimTrigger(false);
			Player->CharCurrentState = Character::C_WALK_DOWN;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			Player->stopAllActions();
			Player->SetAnimTrigger(false);
			Player->CharCurrentState = Character::C_WALK_LEFT;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			Player->stopAllActions();
			Player->SetAnimTrigger(false);
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