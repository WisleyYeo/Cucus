#include "Turret.h"



Turret::Turret()
{
}


Turret::~Turret()
{
}

void Turret::Init(USHORT x, USHORT y, Vec2 TurretShootDirection, int TurretDamage, int TurretHealth, int TurretFirerate)
{
	position.set(Vec2(x, y));
	direction = TurretShootDirection;
	Damage = TurretDamage;
	Health = TurretHealth;
	Firerate = TurretFirerate;
	shootTimer = 0;

	// init bullets
	bulletList.clear();
	for (int i = 0; i < 30; ++i)
	{
		auto bullet = Bullet::createOBJ();
		bulletList.pushBack(bullet);
	}

}

void Turret::Update(float dt)
{
	//updates all bullet
	for (auto bullet : bulletList)
	{
		bullet->update(dt);
		if (bullet->getActive() == false)
		{
			bullet->setPos(position);
		}
	}

	shootTimer += dt;
	if (shootTimer >= Firerate)
	{
		Shoot();
		shootTimer = 0;
	}
}


void Turret::Shoot()
{
	for (auto child : bulletList)
	{
		if (child->getActive() == false)
		{
			child->setActive(true, Bullet::BulletType::Bullet_Turret);
			child->setPos(position);
			child->setDir(direction);
			child->setLifeTime(3.0f);
			//auto fadein = FadeIn::create(0.25);
			//child->runAction(fadein);

			//auto bulletbullet = CallFunc::create(child, callfunc_selector(Bullet::suicide));
			//auto seq = Sequence::create(/*DelayTime::create(1),*/ bulletbullet, nullptr);
			//child->runAction(seq);
			break;
		}
	}
}