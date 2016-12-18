#pragma once

#include "SpriteManager.h"

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

	void Init(RESOURCES TurretSprite, USHORT x, USHORT y, Vec2 TurretShootDirection, int TurretDamage, int TurretHealth, int TurretFirerate);

private:
	SpriteManager *TurretSprite;

	Vec2 position;
	Vec2 shootDirection;

	int Damage;
	int Health;
	int Firerate;
};

