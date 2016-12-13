#pragma once
#include "SpriteManager.h"
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


	SpriteManager GetCharCurrentSprite(void);

	void Walk(Vec2 dir, double dt);
	void BoolChecker();
	bool IsMoving(){ return isMoving; };

	int GetHealth(void);
	int GetSpeed(void);
	int GetStrength(void);

private:
	SpriteManager *CharacterCurrentSprite;
	RESOURCES CharacterIdleSprite;
	RESOURCES CharacterMoveUpSprite;
	RESOURCES CharacterMoveDownSprite;
	RESOURCES CharacterMoveLeftSprite;
	RESOURCES CharacterMoveRightSprite;

	Vec2 position;	
	bool isMoving;

	//Character Attributes
	int Health;
	int Strength;
	int Speed;

};

