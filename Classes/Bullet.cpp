#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
}

Bullet::~Bullet() {}

Bullet* Bullet::createOBJ()
{
	//creates a new object from its constructor
	Bullet* bullet = new Bullet();

	if (bullet->initWithFile("Bullets/0Empty.png"))
	{
		//initialize the object
		bullet->init();

		//set the object to be autorelease
		bullet->autorelease();

		//return the object
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
};

// on "init" you need to initialize your instance and link callbacks
bool Bullet::init()
{
	lifeTime = 0;
	position.setZero();
	dir.setZero();
	collided = false;
	active = false;
	bulletType = Bullet_Start;
	this->setTexture("Bullets/0Empty.png");
	return true;
}

void Bullet::update(float dt)
{
	this->setPosition(position);

	if (getActive() == true)
	{
		move(dt);
		suicide(dt);
	}
}

void Bullet::move(double dt)
{
	position += 60 * dir * dt;
}

void Bullet::suicide(double dt)
{
	lifeTime -= dt;

	if (lifeTime <= 0 || collided == true)
	{
		setActive(false);	
	}
}

void Bullet::destroy()
{
	setActive(false);
}

void Bullet::setActive(bool active, BulletType bulletType)
{
	this->active = active;
	this->bulletType = bulletType;

	if (active == true)
	{
		if (bulletType == Bullet_Player)
			this->setTexture("Bullets/BananaSlice.png");

		else if (bulletType == Bullet_Turret)
			this->setTexture("Bullets/Saw-2.png");
	}
	else
	{
		this->setTexture("Bullets/0Empty.png");
	}
}
bool Bullet::getActive(void)
{
	return active;
}

void Bullet::CollisionCheck(cocos2d::CCTMXLayer *TileLayer)
{
	//Reset to false to allow movement
	collided = false;

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
							collided = true;

						}
						if (TilePosX > CharPosX	&&
							DifferenceY < Comparison)
						{
							//Tile is on the right
							collided = true;
						}
						if (TilePosY < CharPosY &&
							DifferenceX < Comparison)
						{
							//Tile is below
							collided = true;
						}
						if (TilePosY > CharPosY &&
							DifferenceX < Comparison)
						{
							//Tile is on top
							collided = true;
						}
					}
				}
			}
		}
	}
}