#pragma once
#include "SpriteManager.h"
#include "Bullet.h"
#include <cmath>
USING_NS_CC;

class Character
{
public:
	enum CharState
	{
		C_IDLE,
		C_WALK_UP,
		C_WALK_DOWN,
		C_WALK_LEFT,
		C_WALK_RIGHT,

		C_SHOOT,

		C_TOTALSTATES
	};
	int CharCurrentState;
	
	//Character Collision Checks
	bool CollidedUp;
	bool CollidedDown;
	bool CollidedLeft;
	bool CollidedRight;

	Character();
	~Character();
	
	void Init(RESOURCES CharIdleSprite, RESOURCES CharMoveUpSprite, RESOURCES CharMoveDownSprite,  RESOURCES CharMoveLeftSprite, RESOURCES CharMoveRightSprite,USHORT x, USHORT y,
			int CharHealth, int CharStrength, int CharSpeed);
	//Character Update
	virtual void update(float);

	void CollisionCheck(cocos2d::CCTMXLayer *TileLayer);
	void HealthPackCheck(cocos2d::CCTMXLayer *TileLayer);
	void SpeedPackCheck(cocos2d::CCTMXLayer *TileLayer);
	void StrengthPackCheck(cocos2d::CCTMXLayer *TileLayer);

	void setDirection(Vec2 dir){ this->direction = dir; };
	void Shoot(void);

	SpriteManager GetCharCurrentSprite(void);

	void Walk(double dt);
	void BoolChecker();
	bool IsMoving(){ return isMoving; };

	int GetHealth(void);
	int GetSpeed(void);
	int GetStrength(void);

	cocos2d::Vector<Bullet*> getBulletList(){ return bulletList; };

private:
	SpriteManager *CharacterCurrentSprite;
	RESOURCES CharacterIdleSprite;
	RESOURCES CharacterMoveUpSprite;
	RESOURCES CharacterMoveDownSprite;
	RESOURCES CharacterMoveLeftSprite;
	RESOURCES CharacterMoveRightSprite;

	// list of bullet objects
	cocos2d::Vector<Bullet*> bulletList;

	Vec2 position;	
	Vec2 direction;
	bool isMoving;

	//Character Attributes
	int Health;
	int Strength;
	int Speed;

};

