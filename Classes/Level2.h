#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "cocos2d.h"
#include "SpriteManager.h"
#include "Character.h"
#include "Tilemap.h"
#include "MainMenuScene.h"
#include "Turret.h"

class Level2 : public cocos2d::Layer
{
public:
	Level2();
	~Level2();

	CREATE_FUNC(Level2);
    static cocos2d::Scene* createScene();

    virtual bool init();
	void InitTileMaps();
	void InitTurrets();
	void InitPlayer();
	void InitText();
	void InitPause();
	void InitInputEvents();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	virtual void update(float dt);
	void updatePlayer(float dt);
	void updateTurret(float dt);

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

	//pause button and pause window
	Button* pauseButton;
	bool paused;
	Sprite* pauseWindow;
	Button* resumeButton;
	Button* quitButton;

	//Tilemap
	//Stage 1
	cocos2d::CCTMXTiledMap *Level2stage1;
	cocos2d::CCTMXLayer *Level2stage1collide;
	cocos2d::CCTMXLayer *Level2stage1health;
	cocos2d::CCTMXLayer *Level2stage1speed;
	cocos2d::CCTMXLayer *Level2stage1strength;
	cocos2d::CCTMXLayer *Level2stage1charspawn;
	cocos2d::CCTMXLayer *Level2stage1turretdownspawn;
	cocos2d::CCTMXLayer *Level2stage1exit;

	//Stage 2
	cocos2d::CCTMXTiledMap *Level2stage2;
	cocos2d::CCTMXLayer *Level2stage2collide;
	cocos2d::CCTMXLayer *Level2stage2health;
	cocos2d::CCTMXLayer *Level2stage2speed;
	cocos2d::CCTMXLayer *Level2stage2strength;
	cocos2d::CCTMXLayer *Level2stage2charspawn;
	cocos2d::CCTMXLayer *Level2stage2turretdownspawn;
	cocos2d::CCTMXLayer *Level2stage2exit;

	//Stage 3
	cocos2d::CCTMXTiledMap *Level2stage3;
	cocos2d::CCTMXLayer *Level2stage3collide;
	cocos2d::CCTMXLayer *Level2stage3health;
	cocos2d::CCTMXLayer *Level2stage3speed;
	cocos2d::CCTMXLayer *Level2stage3strength;
	cocos2d::CCTMXLayer *Level2stage3charspawn;
	cocos2d::CCTMXLayer *Level2stage3turretdownspawn;
	cocos2d::CCTMXLayer *Level2stage3exit;

	cocos2d::Vector<Turret*> Level2stage1TurretDownList;
	cocos2d::Vector<Turret*> Level2stage2TurretDownList;
	cocos2d::Vector<Turret*> Level2stage3TurretDownList;
};

#endif // __HELLOWORLD_SCENE_H__
