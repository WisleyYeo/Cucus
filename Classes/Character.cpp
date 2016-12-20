#include "Character.h"

Character::Character()
{
	CharacterCurrentSprite = NULL;
	CharCurrentState = C_IDLE;
}

Character::~Character()
{
}

void Character::Init(RESOURCES CharIdleSprite, RESOURCES CharMoveUpSprite, RESOURCES CharMoveDownSprite, RESOURCES CharMoveLeftSprite, RESOURCES CharMoveRightSprite, USHORT x, USHORT y, int CharHealth, int CharStrength, int CharSpeed)
{
	//Character state sprite init
	CharacterIdleSprite = CharIdleSprite;
	CharacterMoveUpSprite = CharMoveUpSprite;
	CharacterMoveDownSprite = CharMoveDownSprite;
	CharacterMoveLeftSprite = CharMoveLeftSprite;
	CharacterMoveRightSprite = CharMoveRightSprite;

	CharacterCurrentSprite = new SpriteManager();
	CharacterCurrentSprite->Init(CharacterIdleSprite, x, y, true);
	CharCurrentState = C_IDLE;
	CollidedUp = false;
	CollidedDown = false;
	CollidedLeft = false;
	CollidedRight = false;

	// init bullets
	bulletList.clear();
	for (int i = 0; i < 30; ++i)
	{
		auto bullet = Bullet::createOBJ();
		bulletList.pushBack(bullet);
	}

	position = Vec2(x, y);
	direction.setZero();
	isMoving = false;

	//Character Attributes init
	Health = CharHealth;
	Strength = CharStrength;
	Speed = CharSpeed;

}

void Character::update(float dt)
{
	CharacterCurrentSprite->Render(position.x, position.y);
	BoolChecker();

	//updates all bullet
	for (auto bullet : bulletList)
	{
		bullet->update(dt);
		if (bullet->getActive() == false)
		{
			bullet->setPos(position);
		}
	}

	switch (CharCurrentState)
	{
	case C_IDLE:
		//CharacterCurrentSprite->ChangeTexture(CharacterIdleSprite);
		break;
	case C_WALK_UP:
		if (!CollidedUp)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveUpSprite);
			setDirection(Vec2(0, 1));
			Walk(dt);
		}
		break;
	case C_WALK_DOWN:
		if (!CollidedDown)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveDownSprite);
			setDirection(Vec2(0, -1));
			Walk(dt);
		}
		break;
	case C_WALK_LEFT:
		if (!CollidedLeft)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveLeftSprite);
			setDirection(Vec2(-1, 0));
			Walk(dt);
		}
		break;
	case C_WALK_RIGHT:
		if (!CollidedRight)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveRightSprite);
			setDirection(Vec2(1, 0));
			Walk(dt);
		}
		break;
	case C_SHOOT:
		Shoot();
		CharCurrentState = C_IDLE;
	}
}
SpriteManager Character::GetCharCurrentSprite(void)
{
	return *CharacterCurrentSprite;
}

void Character::CollisionCheck(cocos2d::CCTMXLayer *TileLayer)
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
					cocos2d::Rect CharBoundingBox = CharacterCurrentSprite->getSprite()->getBoundingBox();
					if (TileLayer->getTileAt(Vec2(x, y))->getBoundingBox().intersectsRect(CharBoundingBox))
					{
						float TilePosX = TileLayer->getTileAt(Vec2(x, y))->getPositionX() + TileLayer->getTileAt(Vec2(x, y))->getContentSize().width * 0.5f;
						float TilePosY = TileLayer->getTileAt(Vec2(x, y))->getPositionY() + TileLayer->getTileAt(Vec2(x, y))->getContentSize().height * 0.5f;
						float CharPosX = CharacterCurrentSprite->getSprite()->getPositionX();
						float CharPosY = CharacterCurrentSprite->getSprite()->getPositionY();
						float TileSize = TileLayer->getTileAt(Vec2(x, y))->getContentSize().height;
						float CharSize = CharacterCurrentSprite->getSprite()->getContentSize().height;
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

void Character::HealthPackCheck(cocos2d::CCTMXLayer *TileLayer)
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
				if (GID > TileLayer->getTileSet()->_firstGid)
				{
					TilePosition = TileLayer->getTileAt(Vec2(x, y))->getPosition();
					cocos2d::Rect CharBoundingBox = CharacterCurrentSprite->getSprite()->getBoundingBox();
					if (TileLayer->getTileAt(Vec2(x, y))->getBoundingBox().intersectsRect(CharBoundingBox))
					{
						//Change tile to empty tile, usually tile GID 1, so only tile GID 2 onwards will be accounted for collision
						TileLayer->setTileGID(TileLayer->getTileSet()->_firstGid, Vec2(x, y));
						//Increase character health
						Health += 10;
					}
				}
			}
		}
	}
}
void Character::SpeedPackCheck(cocos2d::CCTMXLayer *TileLayer)
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
				if (GID > TileLayer->getTileSet()->_firstGid)
				{
					TilePosition = TileLayer->getTileAt(Vec2(x, y))->getPosition();
					cocos2d::Rect CharBoundingBox = CharacterCurrentSprite->getSprite()->getBoundingBox();
					if (TileLayer->getTileAt(Vec2(x, y))->getBoundingBox().intersectsRect(CharBoundingBox))
					{
						//Change tile to empty tile, usually tile GID 1, so only tile GID 2 onwards will be accounted for collision
						TileLayer->setTileGID(TileLayer->getTileSet()->_firstGid, Vec2(x, y));
						//Increase character health
						Speed += 10;
					}
				}
			}
		}
	}
}
void Character::StrengthPackCheck(cocos2d::CCTMXLayer *TileLayer)
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
				if (GID > TileLayer->getTileSet()->_firstGid)
				{
					TilePosition = TileLayer->getTileAt(Vec2(x, y))->getPosition();
					cocos2d::Rect CharBoundingBox = CharacterCurrentSprite->getSprite()->getBoundingBox();
					if (TileLayer->getTileAt(Vec2(x, y))->getBoundingBox().intersectsRect(CharBoundingBox))
					{
						//Change tile to empty tile, usually tile GID 1, so only tile GID 2 onwards will be accounted for collision
						TileLayer->setTileGID(TileLayer->getTileSet()->_firstGid, Vec2(x, y));
						//Increase character health
						Strength++;
					}
				}
			}
		}
	}
}
void Character::Walk(double dt)
{
	isMoving = true;
	position += 2 * direction * Speed * dt;
}
void Character::BoolChecker()
{
	if (CharCurrentState != C_WALK_UP ||
		CharCurrentState != C_WALK_DOWN ||
		CharCurrentState != C_WALK_LEFT ||
		CharCurrentState != C_WALK_RIGHT) 
	{
		isMoving = false;
	}
}

void Character::Shoot()
{
	for (auto child : bulletList)
	{
		if (child->getActive() == false)
		{
			child->setActive(true, Bullet::BulletType::Bullet_Player);
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

int Character::GetHealth(){
	return Health;
}
int Character::GetSpeed(){
	return Speed;
}
int Character::GetStrength(){
	return Strength;
}