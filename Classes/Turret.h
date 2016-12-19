#pragma once

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class Turret
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

private:

	Vec2 position;
	Vec2 shootDirection;

	int Damage;
	int Health;
	int Firerate;
};

