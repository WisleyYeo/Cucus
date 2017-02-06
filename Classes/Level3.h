#ifndef __LEVEL3_H__
#define __LEVEL3_H__

#include "cocos2d.h"
#include "SpriteManager.h"
#include "Character.h"
#include "Tilemap.h"
#include "MainMenuScene.h"
#include "Turret.h"

class Level3 : public cocos2d::Layer
{
public:
	Level3();
	~Level3();

	CREATE_FUNC(Level3);
	static cocos2d::Scene* createScene();

	virtual bool init();
	void InitTileMaps();
	void InitStage1Turrets();
	void InitStage2Turrets();
	void InitStage3Turrets();
	void InitPlayer();
	void InitText();
	void InitPause();
	void InitInputEvents();
	void InitZoomedCamera();

	void DestroyStage1Bullets();
	void DestroyStage2Bullets();
	void DestroyStage3Bullets();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void update(float dt);
	void updatePlayer(float dt);
	void updateTurret(float dt);
	void updateStage1Turrets(float dt);
	void updateStage2Turrets(float dt);
	void updateStage3Turrets(float dt);

	void updateHUD(float dt);

	//pause button callback
	void PauseGame(Ref* pSender, Widget::TouchEventType type);
	void ResumeGame(Ref* pSender, Widget::TouchEventType type);
	void ToMainMenu(Ref* pSender, Widget::TouchEventType type);
	void RestartGame(Ref* pSender, Widget::TouchEventType type);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);

	virtual void onMouseMove(cocos2d::Event*);
	virtual void onMouseUp(cocos2d::Event*);
	virtual void onMouseDown(cocos2d::Event*);
	virtual void onMouseScroll(cocos2d::Event*);

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

private:
	//Player
	Character *Player;
	// Setting 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size ratio = Director::getInstance()->getWinSize();

	//Text Value Labels
	CCLabelTTF* HealthValueLabel;
	CCLabelTTF* SpeedValueLabel;
	CCLabelTTF* StrengthValueLabel;
	vector<int> LabelTags;

	//pause button and pause window
	Button* pauseButton;
	bool paused;
	Sprite* pauseWindow;
	Button* resumeButton;
	Button* quitButton;

	//Tilemap
	//Stage 1
	cocos2d::CCTMXTiledMap *Level3stage1;
	cocos2d::CCTMXLayer *Level3stage1collide;
	cocos2d::CCTMXLayer *Level3stage1health;
	cocos2d::CCTMXLayer *Level3stage1speed;
	cocos2d::CCTMXLayer *Level3stage1strength;
	cocos2d::CCTMXLayer *Level3stage1charspawn;
	cocos2d::CCTMXLayer *Level3stage1turretdownspawn;
	cocos2d::CCTMXLayer *Level3stage1turretleftspawn;
	cocos2d::CCTMXLayer *Level3stage1turretrightspawn;
	cocos2d::CCTMXLayer *Level3stage1turretupspawn;
	cocos2d::CCTMXLayer *Level3stage1exit;

	//Stage 2
	cocos2d::CCTMXTiledMap *Level3stage2;
	cocos2d::CCTMXLayer *Level3stage2collide;
	cocos2d::CCTMXLayer *Level3stage2health;
	cocos2d::CCTMXLayer *Level3stage2speed;
	cocos2d::CCTMXLayer *Level3stage2strength;
	cocos2d::CCTMXLayer *Level3stage2charspawn;
	cocos2d::CCTMXLayer *Level3stage2turretdownspawn;
	cocos2d::CCTMXLayer *Level3stage2turretleftspawn;
	cocos2d::CCTMXLayer *Level3stage2turretrightspawn;
	cocos2d::CCTMXLayer *Level3stage2turretupspawn;
	cocos2d::CCTMXLayer *Level3stage2exit;

	//Stage 3
	cocos2d::CCTMXTiledMap *Level3stage3;
	cocos2d::CCTMXLayer *Level3stage3collide;
	cocos2d::CCTMXLayer *Level3stage3health;
	cocos2d::CCTMXLayer *Level3stage3speed;
	cocos2d::CCTMXLayer *Level3stage3strength;
	cocos2d::CCTMXLayer *Level3stage3charspawn;
	cocos2d::CCTMXLayer *Level3stage3turretdownspawn;
	cocos2d::CCTMXLayer *Level3stage3turretleftspawn;
	cocos2d::CCTMXLayer *Level3stage3turretrightspawn;
	cocos2d::CCTMXLayer *Level3stage3turretupspawn;
	cocos2d::CCTMXLayer *Level3stage3exit;

	cocos2d::Vector<Turret*> Level3stage1TurretDownList;
	cocos2d::Vector<Turret*> Level3stage2TurretDownList;
	cocos2d::Vector<Turret*> Level3stage3TurretDownList;

	cocos2d::Vector<Turret*> Level3stage1TurretLeftList;
	cocos2d::Vector<Turret*> Level3stage2TurretLeftList;
	cocos2d::Vector<Turret*> Level3stage3TurretLeftList;

	cocos2d::Vector<Turret*> Level3stage1TurretRightList;
	cocos2d::Vector<Turret*> Level3stage2TurretRightList;
	cocos2d::Vector<Turret*> Level3stage3TurretRightList;

	cocos2d::Vector<Turret*> Level3stage1TurretUpList;
	cocos2d::Vector<Turret*> Level3stage2TurretUpList;
	cocos2d::Vector<Turret*> Level3stage3TurretUpList;
};

#endif // __HELLOWORLD_SCENE_H__
