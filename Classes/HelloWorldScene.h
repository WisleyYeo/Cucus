#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SpriteManager.h"
#include "Character.h"
#include "Tilemap.h"
#include "Turret.h"

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();

	CREATE_FUNC(HelloWorld);
    static cocos2d::Scene* createScene();

    virtual bool init();
	void InitInputEvents();
	void InitTileMaps();
	void InitTurrets();
	void InitPlayer();
	void InitText();
    
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
	//Level 1 
	cocos2d::CCTMXTiledMap *level1stage1, *level1stage2; 
	cocos2d::CCTMXLayer *level1stage1collide, *level1stage1health, *level1stage1speed, *level1stage1strength, *level1stage1charspawn, *level1stage1turretdownspawn, *level1stage1exit;

	cocos2d::Vector<Turret*> level1stage1TurretDownList;
};

#endif // __HELLOWORLD_SCENE_H__
