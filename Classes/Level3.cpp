﻿#include "Level3.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
Level3::Level3()
{
	Player = NULL;
	//collectablelayer = NULL;
}
Scene* Level3::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Level3::create();

	layer->setCameraMask(2, true);
	// add layer as a child to scene
	scene->addChild(layer, 0, "Layer");

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool Level3::init()
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

void Level3::InitTileMaps()
{
	//Tilemap Init
	//Level 1
	Level3stage1 = new CCTMXTiledMap();
	Level3stage1->initWithTMXFile(TilemapFileName[L3_S1]);
	Level3stage1collide = Level3stage1->layerNamed("Collide");
	Level3stage1health = Level3stage1->layerNamed("Health");
	Level3stage1speed = Level3stage1->layerNamed("Speed");
	Level3stage1strength = Level3stage1->layerNamed("Strength");
	Level3stage1charspawn = Level3stage1->layerNamed("CharSpawn");
	Level3stage1turretdownspawn = Level3stage1->layerNamed("TurretDown");
	Level3stage1turretleftspawn = Level3stage1->layerNamed("TurretLeft");
	Level3stage1turretrightspawn = Level3stage1->layerNamed("TurretRight");
	Level3stage1turretupspawn = Level3stage1->layerNamed("TurretUp");
	Level3stage1exit = Level3stage1->layerNamed("Exit");
	this->addChild(Level3stage1, 0, "Level3Stage1Map");
	//Level 2
	Level3stage2 = new CCTMXTiledMap();
	Level3stage2->initWithTMXFile(TilemapFileName[L3_S2]);
	Level3stage2collide = Level3stage2->layerNamed("Collide");
	Level3stage2health = Level3stage2->layerNamed("Health");
	Level3stage2speed = Level3stage2->layerNamed("Speed");
	Level3stage2strength = Level3stage2->layerNamed("Strength");
	Level3stage2charspawn = Level3stage2->layerNamed("CharSpawn");
	Level3stage2turretdownspawn = Level3stage2->layerNamed("TurretDown");
	Level3stage2turretleftspawn = Level3stage2->layerNamed("TurretLeft");
	Level3stage2turretrightspawn = Level3stage2->layerNamed("TurretRight");
	Level3stage2turretupspawn = Level3stage2->layerNamed("TurretUp");
	Level3stage2exit = Level3stage2->layerNamed("Exit");
	//Level 3
	Level3stage3 = new CCTMXTiledMap();
	Level3stage3->initWithTMXFile(TilemapFileName[L3_S3]);
	Level3stage3collide = Level3stage3->layerNamed("Collide");
	Level3stage3health = Level3stage3->layerNamed("Health");
	Level3stage3speed = Level3stage3->layerNamed("Speed");
	Level3stage3strength = Level3stage3->layerNamed("Strength");
	Level3stage3charspawn = Level3stage3->layerNamed("CharSpawn");
	Level3stage3turretdownspawn = Level3stage3->layerNamed("TurretDown");
	Level3stage3turretleftspawn = Level3stage3->layerNamed("TurretLeft");
	Level3stage3turretrightspawn = Level3stage3->layerNamed("TurretRight");
	Level3stage3turretupspawn = Level3stage3->layerNamed("TurretUp");
	Level3stage3exit = Level3stage3->layerNamed("Exit");
}
void Level3::InitStage1Turrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	Level3stage1TurretDownList.clear();

	Size s1 = Level3stage1turretdownspawn->getLayerSize();
	unsigned int GID1 = 0;
	if (s1.width > 0 && s1.height > 0)
	{
		for (int x = 0; x < s1.width; ++x)
		{
			for (int y = 0; y < s1.height; ++y)
			{
				GID1 = Level3stage1turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID1 > 0)
				{
					TurretDownPos = Level3stage1turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage1turretdownspawn->setTileGID(Level3stage1turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretDown->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage1TurretDownList.pushBack(TurretDown);
				}
			}
		}
	}

	//Turret Left Init
	Vec2 TurretLeftPos;
	Level3stage1TurretLeftList.clear();

	Size s2 = Level3stage1turretleftspawn->getLayerSize();
	unsigned int GID2 = 0;
	if (s2.width > 0 && s2.height > 0)
	{
		for (int x = 0; x < s2.width; ++x)
		{
			for (int y = 0; y < s2.height; ++y)
			{
				GID2 = Level3stage1turretleftspawn->getTileGIDAt(Vec2(x, y));
				if (GID2 > 0)
				{
					TurretLeftPos = Level3stage1turretleftspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage1turretleftspawn->setTileGID(Level3stage1turretleftspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretLeft = new Turret();
					TurretLeft->Init(TurretLeftPos.x + 16, TurretLeftPos.y + 16, Vec2(-1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretLeft->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage1TurretDownList.pushBack(TurretLeft);
				}
			}
		}
	}

	//Turret Right Init
	Vec2 TurretRightPos;
	Level3stage1TurretRightList.clear();

	Size s3 = Level3stage1turretrightspawn->getLayerSize();
	unsigned int GID3 = 0;
	if (s3.width > 0 && s3.height > 0)
	{
		for (int x = 0; x < s3.width; ++x)
		{
			for (int y = 0; y < s3.height; ++y)
			{
				GID3 = Level3stage1turretrightspawn->getTileGIDAt(Vec2(x, y));
				if (GID3 > 0)
				{
					TurretRightPos = Level3stage1turretrightspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage1turretrightspawn->setTileGID(Level3stage1turretrightspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretright = new Turret();
					Turretright->Init(TurretRightPos.x + 16, TurretRightPos.y + 16, Vec2(1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretright->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage1TurretRightList.pushBack(Turretright);
				}
			}
		}
	}

	//Turret Up Init
	Vec2 TurretUpPos;
	Level3stage1TurretUpList.clear();

	Size s4 = Level3stage1turretupspawn->getLayerSize();
	unsigned int GID4 = 0;
	if (s4.width > 0 && s4.height > 0)
	{
		for (int x = 0; x < s4.width; ++x)
		{
			for (int y = 0; y < s4.height; ++y)
			{
				GID4 = Level3stage1turretupspawn->getTileGIDAt(Vec2(x, y));
				if (GID4 > 0)
				{
					TurretUpPos = Level3stage1turretupspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage1turretupspawn->setTileGID(Level3stage1turretupspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretup = new Turret();
					Turretup->Init(TurretUpPos.x + 16, TurretUpPos.y + 16, Vec2(0, 1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretup->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage1TurretUpList.pushBack(Turretup);
				}
			}
		}
	}
}
void Level3::InitStage2Turrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	Level3stage2TurretDownList.clear();

	Size s1 = Level3stage2turretdownspawn->getLayerSize();
	unsigned int GID1 = 0;
	if (s1.width > 0 && s1.height > 0)
	{
		for (int x = 0; x < s1.width; ++x)
		{
			for (int y = 0; y < s1.height; ++y)
			{
				GID1 = Level3stage2turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID1 > 0)
				{
					TurretDownPos = Level3stage2turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage2turretdownspawn->setTileGID(Level3stage2turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretDown->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage2TurretDownList.pushBack(TurretDown);
				}
			}
		}
	}

	//Turret Left Init
	Vec2 TurretLeftPos;
	Level3stage2TurretLeftList.clear();

	Size s2 = Level3stage2turretleftspawn->getLayerSize();
	unsigned int GID2 = 0;
	if (s2.width > 0 && s2.height > 0)
	{
		for (int x = 0; x < s2.width; ++x)
		{
			for (int y = 0; y < s2.height; ++y)
			{
				GID2 = Level3stage2turretleftspawn->getTileGIDAt(Vec2(x, y));
				if (GID2 > 0)
				{
					TurretLeftPos = Level3stage2turretleftspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage2turretleftspawn->setTileGID(Level3stage2turretleftspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretLeft = new Turret();
					TurretLeft->Init(TurretLeftPos.x + 16, TurretLeftPos.y + 16, Vec2(-1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretLeft->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage2TurretLeftList.pushBack(TurretLeft);
				}
			}
		}
	}

	//Turret Right Init
	Vec2 TurretRightPos;
	Level3stage2TurretRightList.clear();

	Size s3 = Level3stage2turretrightspawn->getLayerSize();
	unsigned int GID3 = 0;
	if (s3.width > 0 && s3.height > 0)
	{
		for (int x = 0; x < s3.width; ++x)
		{
			for (int y = 0; y < s3.height; ++y)
			{
				GID3 = Level3stage2turretrightspawn->getTileGIDAt(Vec2(x, y));
				if (GID3 > 0)
				{
					TurretRightPos = Level3stage2turretrightspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage2turretrightspawn->setTileGID(Level3stage2turretrightspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretright = new Turret();
					Turretright->Init(TurretRightPos.x + 16, TurretRightPos.y + 16, Vec2(1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretright->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage2TurretRightList.pushBack(Turretright);
				}
			}
		}
	}

	//Turret Up Init
	Vec2 TurretUpPos;
	Level3stage2TurretUpList.clear();

	Size s4 = Level3stage2turretupspawn->getLayerSize();
	unsigned int GID4 = 0;
	if (s4.width > 0 && s4.height > 0)
	{
		for (int x = 0; x < s4.width; ++x)
		{
			for (int y = 0; y < s4.height; ++y)
			{
				GID4 = Level3stage2turretupspawn->getTileGIDAt(Vec2(x, y));
				if (GID4 > 0)
				{
					TurretUpPos = Level3stage2turretupspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage2turretupspawn->setTileGID(Level3stage2turretupspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretup = new Turret();
					Turretup->Init(TurretUpPos.x + 16, TurretUpPos.y + 16, Vec2(0, 1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretup->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage2TurretUpList.pushBack(Turretup);
				}
			}
		}
	}
}
void Level3::InitStage3Turrets()
{
	//Turret Down Init
	Vec2 TurretDownPos;
	Level3stage3TurretDownList.clear();

	Size s1 = Level3stage3turretdownspawn->getLayerSize();
	unsigned int GID1 = 0;
	if (s1.width > 0 && s1.height > 0)
	{
		for (int x = 0; x < s1.width; ++x)
		{
			for (int y = 0; y < s1.height; ++y)
			{
				GID1 = Level3stage3turretdownspawn->getTileGIDAt(Vec2(x, y));
				if (GID1 > 0)
				{
					TurretDownPos = Level3stage3turretdownspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage3turretdownspawn->setTileGID(Level3stage3turretdownspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretDown = new Turret();
					TurretDown->Init(TurretDownPos.x + 16, TurretDownPos.y + 16, Vec2(0, -1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretDown->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage3TurretDownList.pushBack(TurretDown);
				}
			}
		}
	}

	//Turret Left Init
	Vec2 TurretLeftPos;
	Level3stage3TurretLeftList.clear();

	Size s2 = Level3stage3turretleftspawn->getLayerSize();
	unsigned int GID2 = 0;
	if (s2.width > 0 && s2.height > 0)
	{
		for (int x = 0; x < s2.width; ++x)
		{
			for (int y = 0; y < s2.height; ++y)
			{
				GID2 = Level3stage3turretleftspawn->getTileGIDAt(Vec2(x, y));
				if (GID2 > 0)
				{
					TurretLeftPos = Level3stage3turretleftspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage3turretleftspawn->setTileGID(Level3stage3turretleftspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* TurretLeft = new Turret();
					TurretLeft->Init(TurretLeftPos.x + 16, TurretLeftPos.y + 16, Vec2(-1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : TurretLeft->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage3TurretLeftList.pushBack(TurretLeft);
				}
			}
		}
	}

	//Turret Right Init
	Vec2 TurretRightPos;
	Level3stage3TurretRightList.clear();

	Size s3 = Level3stage3turretrightspawn->getLayerSize();
	unsigned int GID3 = 0;
	if (s3.width > 0 && s3.height > 0)
	{
		for (int x = 0; x < s3.width; ++x)
		{
			for (int y = 0; y < s3.height; ++y)
			{
				GID3 = Level3stage3turretrightspawn->getTileGIDAt(Vec2(x, y));
				if (GID3 > 0)
				{
					TurretRightPos = Level3stage3turretrightspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage3turretrightspawn->setTileGID(Level3stage3turretrightspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretright = new Turret();
					Turretright->Init(TurretRightPos.x + 16, TurretRightPos.y + 16, Vec2(1, 0), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretright->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage3TurretRightList.pushBack(Turretright);
				}
			}
		}
	}

	//Turret Up Init
	Vec2 TurretUpPos;
	Level3stage3TurretUpList.clear();

	Size s4 = Level3stage3turretupspawn->getLayerSize();
	unsigned int GID4 = 0;
	if (s4.width > 0 && s4.height > 0)
	{
		for (int x = 0; x < s4.width; ++x)
		{
			for (int y = 0; y < s4.height; ++y)
			{
				GID4 = Level3stage3turretupspawn->getTileGIDAt(Vec2(x, y));
				if (GID4 > 0)
				{
					TurretUpPos = Level3stage3turretupspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage3turretupspawn->setTileGID(Level3stage3turretupspawn->getTileSet()->_firstGid, Vec2(x, y));
					Turret* Turretup = new Turret();
					Turretup->Init(TurretUpPos.x + 16, TurretUpPos.y + 16, Vec2(0, 1), 1, 100, 2.5);

					//Turret bullet addchild
					for (auto child : Turretup->getBulletList())
					{
						this->addChild(child, -1);
					}

					Level3stage3TurretUpList.pushBack(Turretup);
				}
			}
		}
	}
}
void Level3::InitPlayer()
{
	//Player Init
	Player = Character::createOBJ();
	Vec2 CharSpawnPos;
	Size s = Level3stage1charspawn->getLayerSize();
	unsigned int GID = 0;
	if (s.width > 0 && s.height > 0)
	{
		for (int x = 0; x < s.width; ++x)
		{
			for (int y = 0; y < s.height; ++y)
			{
				GID = Level3stage1charspawn->getTileGIDAt(Vec2(x, y));
				if (GID > Level3stage1charspawn->getTileSet()->_firstGid)
				{
					CharSpawnPos = Level3stage1charspawn->getTileAt(Vec2(x, y))->getPosition();
					Level3stage1charspawn->setTileGID(Level3stage1charspawn->getTileSet()->_firstGid, Vec2(x, y));
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
void Level3::InitText()
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
void Level3::InitInputEvents()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Level3::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Level3::keyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Level3::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Level3::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Level3::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Level3::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Level3::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(Level3::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(Level3::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
void Level3::InitPause()
{
	paused = false;

	//pause button
	pauseButton = Button::create("pauseButton.png", "pauseButtonPressed.png");
	pauseButton->setScale(0.3);
	pauseButton->addTouchEventListener(CC_CALLBACK_2(Level3::PauseGame, this));
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
	resumeButton->addTouchEventListener(CC_CALLBACK_2(Level3::ResumeGame, this));
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
	quitButton->addTouchEventListener(CC_CALLBACK_2(Level3::ToMainMenu, this));
	quitButton->setPosition(Vec2(origin.x + visibleSize.width * 0.35f, origin.y + visibleSize.height * 0.3f));
	quitButton->setScale(0.5);
	pauseWindow->addChild(quitButton);
}
void Level3::InitZoomedCamera()
{
	auto ss = Director::getInstance()->getWinSize();
	auto cam = Camera::createOrthographic(ss.width * 0.5f, ss.height * 0.5f, 1, 1000);

	cam->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
	cam->setCameraFlag(CameraFlag::USER1);

	this->addChild(cam, 1, "Camera");
}

void Level3::DestroyStage1Bullets()
{
	for (auto bullet : Player->getBulletList())
	{
		if (bullet->getActive() == true)
		{
			bullet->destroy();
		}
	}
	for (auto turrets : Level3stage1TurretDownList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage1TurretLeftList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage1TurretRightList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage1TurretUpList)
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
void Level3::DestroyStage2Bullets()
{
	for (auto bullet : Player->getBulletList())
	{
		if (bullet->getActive() == true)
		{
			bullet->destroy();
		}
	}
	for (auto turrets : Level3stage2TurretDownList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage2TurretLeftList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage2TurretRightList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage2TurretUpList)
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
void Level3::DestroyStage3Bullets()
{
	for (auto bullet : Player->getBulletList())
	{
		if (bullet->getActive() == true)
		{
			bullet->destroy();
		}
	}
	for (auto turrets : Level3stage3TurretDownList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage3TurretLeftList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage3TurretRightList)
	{
		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				bullet->destroy();
			}
		}
	}
	for (auto turrets : Level3stage3TurretUpList)
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

void Level3::update(float dt)
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
void Level3::updatePlayer(float dt)
{
	//Player updates
	Player->update(dt);
	updateHUD(dt);
	if (this->getChildByName("Level3Stage1Map"))
	{

		auto ss = Director::getInstance()->getWinSize();
		this->getChildByName("Camera")->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
		Player->CollisionCheck(Level3stage1collide);
		Player->HealthPackCheck(Level3stage1health);
		Player->SpeedPackCheck(Level3stage1speed);
		Player->StrengthPackCheck(Level3stage1strength);

		for (auto bullet : Player->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				for (auto turrets : Level3stage1TurretDownList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage1turretdownspawn, bullet);
				}
				for (auto turrets : Level3stage1TurretLeftList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage1turretleftspawn, bullet);
				}
				for (auto turrets : Level3stage1TurretRightList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage1turretrightspawn, bullet);
				}
				for (auto turrets : Level3stage1TurretUpList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage1turretupspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level3stage1exit))
		{
			//Remove relevant childs
			this->removeChildByName("Level3Stage1Map");
			this->removeChildByName("Camera");
			this->getScene()->getChildByName("Layer")->setCameraMask(2, false);

			DestroyStage1Bullets();

			//Set player position 
			Vec2 CharSpawnPos;
			Size s = Level3stage2charspawn->getLayerSize();
			unsigned int GID = 0;
			if (s.width > 0 && s.height > 0)
			{
				for (int x = 0; x < s.width; ++x)
				{
					for (int y = 0; y < s.height; ++y)
					{
						GID = Level3stage2charspawn->getTileGIDAt(Vec2(x, y));
						if (GID > Level3stage2charspawn->getTileSet()->_firstGid)
						{
							CharSpawnPos = Level3stage2charspawn->getTileAt(Vec2(x, y))->getPosition();
							Level3stage2charspawn->setTileGID(Level3stage2charspawn->getTileSet()->_firstGid, Vec2(x, y));
						}
					}
				}
			}

			Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16);
			//Load next stage
			this->addChild(Level3stage2, 0, "Level3Stage2Map");

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
	if (this->getChildByName("Level3Stage2Map"))
	{
		auto ss = Director::getInstance()->getWinSize();
		this->getChildByName("Camera")->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
		Player->CollisionCheck(Level3stage2collide);
		Player->HealthPackCheck(Level3stage2health);
		Player->SpeedPackCheck(Level3stage2speed);
		Player->StrengthPackCheck(Level3stage2strength);

		for (auto bullet : Player->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				for (auto turrets : Level3stage2TurretDownList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage2turretdownspawn, bullet);
				}
				for (auto turrets : Level3stage2TurretLeftList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage2turretleftspawn, bullet);
				}
				for (auto turrets : Level3stage2TurretRightList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage2turretrightspawn, bullet);
				}
				for (auto turrets : Level3stage2TurretUpList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage2turretupspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level3stage2exit))
		{
			//Remove relevant childs
			this->removeChildByName("Level3Stage1Map");
			this->removeChildByName("Camera");
			this->getScene()->getChildByName("Layer")->setCameraMask(2, false);
			this->removeChildByName("Level3Stage2Map");

			DestroyStage2Bullets();

			//Set player position 
			Vec2 CharSpawnPos;
			Size s = Level3stage3charspawn->getLayerSize();
			unsigned int GID = 0;
			if (s.width > 0 && s.height > 0)
			{
				for (int x = 0; x < s.width; ++x)
				{
					for (int y = 0; y < s.height; ++y)
					{
						GID = Level3stage3charspawn->getTileGIDAt(Vec2(x, y));
						if (GID > Level3stage3charspawn->getTileSet()->_firstGid)
						{
							CharSpawnPos = Level3stage3charspawn->getTileAt(Vec2(x, y))->getPosition();
							Level3stage3charspawn->setTileGID(Level3stage3charspawn->getTileSet()->_firstGid, Vec2(x, y));
						}
					}
				}
			}
			Player->Init(CharSpawnPos.x + 16, CharSpawnPos.y + 16);

			//Load next stage
			this->addChild(Level3stage3, 0, "Level3Stage3Map");

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
	if (this->getChildByName("Level3Stage3Map"))
	{
		auto ss = Director::getInstance()->getWinSize();
		this->getChildByName("Camera")->setPosition3D(Vec3(Player->GetPosition().x - ss.width * 0.5f * 0.5f, Player->GetPosition().y - ss.height * 0.5f * 0.5f, 800));
		Player->CollisionCheck(Level3stage3collide);
		Player->HealthPackCheck(Level3stage3health);
		Player->SpeedPackCheck(Level3stage3speed);
		Player->StrengthPackCheck(Level3stage3strength);

		for (auto bullet : Player->getBulletList())
		{
			if (bullet->getActive() == true)
			{
				for (auto turrets : Level3stage3TurretDownList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage3turretdownspawn, bullet);
				}
				for (auto turrets : Level3stage3TurretLeftList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage3turretleftspawn, bullet);
				}
				for (auto turrets : Level3stage3TurretRightList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage3turretrightspawn, bullet);
				}
				for (auto turrets : Level3stage3TurretUpList)
				{
					// check if damage the player
					turrets->ReceiveDamageCheck(Level3stage3turretupspawn, bullet);
				}
			}
		}
		if (Player->ExitCheck(Level3stage3exit))
		{
			//Since last stage, go back to level selection
			auto scene = createScene();
			scene = LevelSelection::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
		}
	}
}

void Level3::updateStage1Turrets(float dt)
{
	for (auto turrets : Level3stage1TurretDownList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage1collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage1TurretLeftList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage1collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage1TurretRightList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage1collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage1TurretUpList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage1collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
}
void Level3::updateStage2Turrets(float dt)
{
	for (auto turrets : Level3stage2TurretDownList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage2collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage2TurretLeftList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage2collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage2TurretRightList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage2collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage2TurretUpList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage2collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
}
void Level3::updateStage3Turrets(float dt)
{
	for (auto turrets : Level3stage3TurretDownList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage3collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage3TurretLeftList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage3collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage3TurretRightList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage3collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
	for (auto turrets : Level3stage3TurretUpList)
	{
		turrets->Update(dt);
		turrets->CollisionCheck(Level3stage3collide);

		for (auto bullet : turrets->getBulletList())
		{
			if (bullet->getActive() == true)
				// check if damage the player
				Player->ReceiveDamageCheck(bullet);
		}
	}
}

void Level3::updateTurret(float dt)
{
	//Turret updates
	if (this->getChildByName("Level3Stage1Map"))
	{
		updateStage1Turrets(dt);
	}
	if (this->getChildByName("Level3Stage2Map"))
	{
		updateStage2Turrets(dt);
	}
	if (this->getChildByName("Level3Stage3Map"))
	{
		updateStage3Turrets(dt);
	}
}
void Level3::updateHUD(float dt)
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
void Level3::PauseGame(Ref* pSender, Widget::TouchEventType type)
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
void Level3::ResumeGame(Ref* pSender, Widget::TouchEventType type)
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
void Level3::ToMainMenu(Ref *pSender, Widget::TouchEventType type)
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
void Level3::RestartGame(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:

		//replace the scene with the main game scene
		auto scene = Level3::createScene();
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, scene));

		break;
	}
}


void Level3::menuCloseCallback(Ref* pSender)
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

void Level3::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
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
void Level3::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
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

bool Level3::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
	return true;
}
void Level3::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{

}
void Level3::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{

}
void Level3::onMouseMove(cocos2d::Event*)
{

}
void Level3::onMouseUp(cocos2d::Event*)
{

}
void Level3::onMouseDown(cocos2d::Event* event)
{

}
void Level3::onMouseScroll(cocos2d::Event*)
{

}

Level3::~Level3()
{
}