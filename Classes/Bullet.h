#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h" 
#include "ui\CocosGUI.h"
#include <string>
using namespace std;
using namespace cocos2d;
using namespace ui;

class Bullet : public cocos2d::Sprite
{
public:

	static Bullet *createOBJ();

	Bullet();
	~Bullet();

	virtual bool init();
	virtual void update(float dt);

	void setActive(bool active);
	bool getActive(void);
	Vec2 getPosition(){ return position; };

	void setDir(Vec2 dir){ this->dir = dir; };
	void setPos(Vec2 pos){ this->position = pos; };
	void setLifeTime(float lifetime){ this->lifeTime = lifetime; };

	void CollisionCheck(cocos2d::CCTMXLayer *TileLayer);

	void move(double dt);
	void suicide(double dt);

	CREATE_FUNC(Bullet);

private:

	bool collided;
	bool active;
	Vec2 position;
	Vec2 dir;
	float lifeTime;

	// Setting 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

};



#endif