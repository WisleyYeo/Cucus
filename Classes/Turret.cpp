#include "Turret.h"



Turret::Turret()
{
}


Turret::~Turret()
{
}
void Turret::Init(USHORT x, USHORT y, Vec2 TurretShootDirection, int TurretDamage, int TurretHealth, int TurretFirerate)
{
	shootDirection = TurretShootDirection;
	Damage = TurretDamage;
	Health = TurretHealth;
	Firerate = TurretFirerate;
}