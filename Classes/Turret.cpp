#include "Turret.h"



Turret::Turret()
{
}


Turret::~Turret()
{
}
void Turret::Init(RESOURCES TurretSprite, USHORT x, USHORT y, Vec2 TurretShootDirection, int TurretDamage, int TurretHealth, int TurretFirerate)
{
	this->TurretSprite = new SpriteManager();
	this->TurretSprite->Init(TurretSprite, x, y, true);
	shootDirection = TurretShootDirection;
	Damage = TurretDamage;
	Health = TurretHealth;
	Firerate = TurretFirerate;
}