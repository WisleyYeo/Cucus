#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "cocos2d.h"
#include "SpriteManager.h"
#include "Character.h"
#include "Tilemap.h"
#include "Turret.h"

class Level1 : public cocos2d::Layer
{
public:
	Level1();
	~Level1();

	CREATE_FUNC(Level1);
    static cocos2d::Scene* createScene();

    virtual bool init();
	void InitInputEvents();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	virtual void update(float dt);
	void updatePlayer(float dt);
	void updateTurret(float dt);

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

	//Text Value Labels
	CCLabelTTF* HealthValueLabel;
	CCLabelTTF* SpeedValueLabel; 
	CCLabelTTF* StrengthValueLabel;

	//Tilemap
	//Stage 1
	cocos2d::CCTMXTiledMap *level1stage1;
	cocos2d::CCTMXLayer *level1stage1collide;
	cocos2d::CCTMXLayer *level1stage1health;
	cocos2d::CCTMXLayer *level1stage1speed;
	cocos2d::CCTMXLayer *level1stage1strength;
	cocos2d::CCTMXLayer *level1stage1charspawn;
	cocos2d::CCTMXLayer *level1stage1turretdownspawn;
	cocos2d::CCTMXLayer *level1stage1exit;

	//Stage 2
	cocos2d::CCTMXTiledMap *level1stage2;
	cocos2d::CCTMXLayer *level1stage2collide;
	cocos2d::CCTMXLayer *level1stage2health;
	cocos2d::CCTMXLayer *level1stage2speed;
	cocos2d::CCTMXLayer *level1stage2strength;
	cocos2d::CCTMXLayer *level1stage2charspawn;
	cocos2d::CCTMXLayer *level1stage2turretdownspawn;
	cocos2d::CCTMXLayer *level1stage2exit;

	//Stage 3
	cocos2d::CCTMXTiledMap *level1stage3;
	cocos2d::CCTMXLayer *level1stage3collide;
	cocos2d::CCTMXLayer *level1stage3health;
	cocos2d::CCTMXLayer *level1stage3speed;
	cocos2d::CCTMXLayer *level1stage3strength;
	cocos2d::CCTMXLayer *level1stage3charspawn;
	cocos2d::CCTMXLayer *level1stage3turretdownspawn;
	cocos2d::CCTMXLayer *level1stage3exit;

	cocos2d::Vector<Turret*> level1stage1TurretDownList;
	cocos2d::Vector<Turret*> level1stage2TurretDownList;
	cocos2d::Vector<Turret*> level1stage3TurretDownList;
};

#endif // __HELLOWORLD_SCENE_H__
