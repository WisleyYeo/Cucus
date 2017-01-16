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
	cocos2d::CCTMXTiledMap *Level3stage1;
	cocos2d::CCTMXLayer *Level3stage1collide;
	cocos2d::CCTMXLayer *Level3stage1health;
	cocos2d::CCTMXLayer *Level3stage1speed;
	cocos2d::CCTMXLayer *Level3stage1strength;
	cocos2d::CCTMXLayer *Level3stage1charspawn;
	cocos2d::CCTMXLayer *Level3stage1turretdownspawn;
	cocos2d::CCTMXLayer *Level3stage1exit;

	//Stage 2
	cocos2d::CCTMXTiledMap *Level3stage2;
	cocos2d::CCTMXLayer *Level3stage2collide;
	cocos2d::CCTMXLayer *Level3stage2health;
	cocos2d::CCTMXLayer *Level3stage2speed;
	cocos2d::CCTMXLayer *Level3stage2strength;
	cocos2d::CCTMXLayer *Level3stage2charspawn;
	cocos2d::CCTMXLayer *Level3stage2turretdownspawn;
	cocos2d::CCTMXLayer *Level3stage2exit;

	//Stage 3
	cocos2d::CCTMXTiledMap *Level3stage3;
	cocos2d::CCTMXLayer *Level3stage3collide;
	cocos2d::CCTMXLayer *Level3stage3health;
	cocos2d::CCTMXLayer *Level3stage3speed;
	cocos2d::CCTMXLayer *Level3stage3strength;
	cocos2d::CCTMXLayer *Level3stage3charspawn;
	cocos2d::CCTMXLayer *Level3stage3turretdownspawn;
	cocos2d::CCTMXLayer *Level3stage3exit;

	cocos2d::Vector<Turret*> Level3stage1TurretDownList;
	cocos2d::Vector<Turret*> Level3stage2TurretDownList;
	cocos2d::Vector<Turret*> Level3stage3TurretDownList;
};

#endif // __HELLOWORLD_SCENE_H__
