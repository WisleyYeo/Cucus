#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SpriteManager.h"
#include "Character.h"
#include "Tilemap.h"
class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();

	CREATE_FUNC(HelloWorld);
    static cocos2d::Scene* createScene();

    virtual bool init();
	void InitInputEvents();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	virtual void update(float);

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

	//Tilemap
	//Level 1
	cocos2d::CCTMXTiledMap *level1collidemap;
	cocos2d::CCTMXLayer *level1collidelayer;
	cocos2d::CCTMXTiledMap *level1collectmap;
	cocos2d::CCTMXLayer *level1collectlayer;
};

#endif // __HELLOWORLD_SCENE_H__
