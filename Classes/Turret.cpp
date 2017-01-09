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

	CollidedUp = false;
	CollidedDown = false;
	CollidedLeft = false;
	CollidedRight = false;

	// init bullets
	bulletList.clear();
	for (int i = 0; i < 15; ++i)
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

void Turret::CollisionCheck(cocos2d::CCTMXLayer *TileLayer)
{
	//temp bullet
	for (auto child : bulletList)
	{
		if (child->getActive() == true)
		{
			child->CollisionCheck(TileLayer);
		}
	}

	//Reset to false to allow movement
	CollidedUp = false;
	CollidedDown = false;
	CollidedLeft = false;
	CollidedRight = false;
	//Collision Check Player Against other entities
	Size s = TileLayer->getLayerSize();
	Vec2 TilePosition = Vec2(0, 0);
	unsigned int GID = 0;
	if (s.width > 0 && s.height > 0)
	{
		for (int x = 0; x < s.width; ++x)
		{
			for (int y = 0; y < s.height; ++y)
			{
				GID = TileLayer->getTileGIDAt(Vec2(x, y));
				if (GID > 0)
				{

					TilePosition = TileLayer->getTileAt(Vec2(x, y))->getPosition();
					cocos2d::Rect CharBoundingBox = this->getBoundingBox();
					if (TileLayer->getTileAt(Vec2(x, y))->getBoundingBox().intersectsRect(CharBoundingBox))
					{
						float TilePosX = TileLayer->getTileAt(Vec2(x, y))->getPositionX() + TileLayer->getTileAt(Vec2(x, y))->getContentSize().width * 0.5f;
						float TilePosY = TileLayer->getTileAt(Vec2(x, y))->getPositionY() + TileLayer->getTileAt(Vec2(x, y))->getContentSize().height * 0.5f;
						float CharPosX = this->getPositionX();
						float CharPosY = this->getPositionY();
						float TileSize = TileLayer->getTileAt(Vec2(x, y))->getContentSize().height;
						float CharSize = this->getContentSize().height;
						float Comparison = CharSize * 0.5f + TileSize * 0.5f;
						float offset = 5.0f;
						float DifferenceX = abs(TilePosX - CharPosX) + offset;
						float DifferenceY = abs(TilePosY - CharPosY) + offset;
						//If Player is within Tile's Bounding Box, Check where Tile is relative to player
						if (TilePosX < CharPosX &&
							DifferenceY < Comparison)
						{
							//Tile is on the left
							CollidedLeft = true;

						}
						if (TilePosX > CharPosX	&&
							DifferenceY < Comparison)
						{
							//Tile is on the right
							CollidedRight = true;
						}
						if (TilePosY < CharPosY &&
							DifferenceX < Comparison)
						{
							//Tile is below
							CollidedDown = true;
						}
						if (TilePosY > CharPosY &&
							DifferenceX < Comparison)
						{
							//Tile is on top
							CollidedUp = true;
						}
					}
				}
			}
		}
	}
}

void Turret::ReceiveDamageCheck(cocos2d::CCTMXLayer *TileLayer, Bullet* bullet)
{
	//Collision Check Player Against other entities
	Size s = TileLayer->getLayerSize();
	Vec2 TilePosition = Vec2(0, 0);
	unsigned int GID = 0;
	if (s.width > 0 && s.height > 0)
	{
		for (int x = 0; x < s.width; ++x)
		{
			for (int y = 0; y < s.height; ++y)
			{
				GID = TileLayer->getTileGIDAt(Vec2(x, y));
				if (GID > 0)
				{
					TilePosition = TileLayer->getTileAt(Vec2(x, y))->getPosition();
					cocos2d::Rect BulletBox = bullet->getBoundingBox();

					if (TileLayer->getTileAt(Vec2(x, y))->getBoundingBox().intersectsRect(BulletBox))
					{
						bullet->setCollided(true);
						//Increase character health
						Health -= 1;
					}
				}
			}
		}
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
			break;
		}
	}
}