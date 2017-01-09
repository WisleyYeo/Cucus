#pragma once

#include "cocos2d.h"
#include "Bullet.h"
using namespace std;
using namespace cocos2d;

USING_NS_CC;

class Turret : public cocos2d::Node
{

public:

	enum TurretState
	{
		T_ACTIVE,
		T_INACTIVE,

		T_TOTALSTATES
	};
	Turret();
	~Turret();

	void Init(USHORT x, USHORT y, Vec2 TurretShootDirection, int TurretDamage, int TurretHealth, int TurretFirerate);
	void Shoot(void);
	void Update(float dt);
	void ReceiveDamageCheck(cocos2d::CCTMXLayer *TileLayer, Bullet* bullet);

	void CollisionCheck(cocos2d::CCTMXLayer *TileLayer);
	cocos2d::Vector<Bullet*> getBulletList(){ return bulletList; };

private:

	// list of bullet objects
	cocos2d::Vector<Bullet*> bulletList;

	Vec2 position;
	Vec2 direction;

	float shootTimer;

	int Damage;
	int Health;
	int Firerate;

	//turret Collision Checks
	bool CollidedUp;
	bool CollidedDown;
	bool CollidedLeft;
	bool CollidedRight;
};

