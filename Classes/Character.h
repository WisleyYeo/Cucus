#pragma once
#include "SpriteManager.h"
#include "Bullet.h"
#include <cmath>
USING_NS_CC;

class Character : public cocos2d::Sprite
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
	
	static Character *createOBJ();

	//Character Collision Checks
	bool CollidedUp;
	bool CollidedDown;
	bool CollidedLeft;
	bool CollidedRight;

	Character();
	~Character();
	
	void Init(USHORT x, USHORT y);

	void InitAnimFrames();
	void PlayAnim(CharState state);

	//Character Update
	virtual void update(float);

	void CollisionCheck(cocos2d::CCTMXLayer *TileLayer);
	void HealthPackCheck(cocos2d::CCTMXLayer *TileLayer);
	void SpeedPackCheck(cocos2d::CCTMXLayer *TileLayer);
	void StrengthPackCheck(cocos2d::CCTMXLayer *TileLayer);
	bool ExitCheck(cocos2d::CCTMXLayer *TileLayer);

	void ReceiveDamageCheck(Bullet* bullet);

	void setDirection(Vec2 dir){ this->direction = dir; };
	void Shoot(void);

	void Walk(double dt);
	void BoolChecker();
	bool IsMoving(){ return isMoving; };

	int GetHealth(void);
	int GetSpeed(void);
	int GetStrength(void);

	cocos2d::Vector<Bullet*> getBulletList(){ return bulletList; };

	CREATE_FUNC(Character);

private:

	Vector<SpriteFrame*> WalkUpFrame, WalkDownFrame, WalkLeftFrame, WalkRightFrame;

	// list of bullet objects
	cocos2d::Vector<Bullet*> bulletList;

	Vec2 position;	
	Vec2 direction;
	bool isMoving;
	bool animTrigger;

	//Character Attributes
	int Health;
	int Strength;
	int Speed;
	float shootTimer;
	float firerate;

};

