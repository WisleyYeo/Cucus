#include "Character.h"

Character::Character()
{
	CharCurrentState = C_IDLE;
}

Character::~Character()
{
}

Character* Character::createOBJ()
{
	//creates a new object from its constructor
	Character* character = new Character();

	if (character->initWithFile("Characters/JaronDown.png"))
	{
		//initialize the object
		character->init();

		//set the object to be autorelease
		character->autorelease();

		//return the object
		return character;
	}
	CC_SAFE_DELETE(character);
	return NULL;
};

void Character::Init(USHORT x, USHORT y, int CharHealth, int CharStrength, int CharSpeed)
{
	InitAnimFrames();
	this->setTexture("Characters/JaronDown.png");
	CharCurrentState = C_IDLE;
	animTrigger = false;
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

void Character::InitAnimFrames()
{
	for (int i = 0; i < 9; i++)
	{
		auto frameUp = SpriteFrame::create("Characters/testracter.png", Rect(32 * i, 0, 32, 32)); //assume 32pix
		WalkUpFrame.pushBack(frameUp);

		auto frameLeft = SpriteFrame::create("Characters/testracter.png", Rect(32 * i, 32, 32, 32)); //assume 32pix
		WalkLeftFrame.pushBack(frameLeft);

		auto frameDown = SpriteFrame::create("Characters/testracter.png", Rect(32 * i, 64, 32, 32)); //assume 32pix
		WalkDownFrame.pushBack(frameDown);

		auto frameRight = SpriteFrame::create("Characters/testracter.png", Rect(32 * i, 96, 32, 32)); //assume 32pix
		WalkRightFrame.pushBack(frameRight);
	}
}

void Character::update(float dt)
{
	this->setPosition(position);
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

		animTrigger = false;
		this->stopAllActions();

		break;
	case C_WALK_UP:
		if (!CollidedUp)
		{
			PlayAnim(C_WALK_UP);
			setDirection(Vec2(0, 1));
			Walk(dt);
		}
		else
		{
			animTrigger = false;
			this->stopAllActions();
		}

		break;
	case C_WALK_DOWN:
		if (!CollidedDown)
		{
			PlayAnim(C_WALK_DOWN);
			setDirection(Vec2(0, -1));
			Walk(dt);
		}
		else
		{
			animTrigger = false;
			this->stopAllActions();
		}
		break;
	case C_WALK_LEFT:
		if (!CollidedLeft)
		{
			PlayAnim(C_WALK_LEFT);
			setDirection(Vec2(-1, 0));
			Walk(dt);
		}
		else
		{
			animTrigger = false;
			this->stopAllActions();
		}
		break;
	case C_WALK_RIGHT:
		if (!CollidedRight)
		{
			PlayAnim(C_WALK_RIGHT);
			setDirection(Vec2(1, 0));
			Walk(dt);
		}
		else
		{
			animTrigger = false;
			this->stopAllActions();
		}
		break;
	case C_SHOOT:
		Shoot();
		CharCurrentState = C_IDLE;
	}
}

void Character::PlayAnim(CharState state)
{
	if (state == C_WALK_UP && animTrigger == false)
	{
		auto animation = Animation::createWithSpriteFrames(WalkUpFrame, 0.1f);
		auto animate = Animate::create(animation);
		this->runAction(RepeatForever::create(animate));
		animTrigger = true;
	}
	else if (state == C_WALK_DOWN && animTrigger == false)
	{
		auto animation = Animation::createWithSpriteFrames(WalkDownFrame, 0.1f);
		auto animate = Animate::create(animation);
		this->runAction(RepeatForever::create(animate));
		animTrigger = true;
	}
	else if (state == C_WALK_LEFT && animTrigger == false)
	{
		auto animation = Animation::createWithSpriteFrames(WalkLeftFrame, 0.1f);
		auto animate = Animate::create(animation);
		this->runAction(RepeatForever::create(animate));
		animTrigger = true;
	}
	else if (state == C_WALK_RIGHT && animTrigger == false)
	{
		auto animation = Animation::createWithSpriteFrames(WalkRightFrame, 0.1f);
		auto animate = Animate::create(animation);
		this->runAction(RepeatForever::create(animate));
		animTrigger = true;
	}
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
bool Character::ExitCheck(cocos2d::CCTMXLayer *TileLayer)
{
	//Check if player exits current stage
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
						//Reset to false to allow movement
						CollidedUp = false;
						CollidedDown = false;
						CollidedLeft = false;
						CollidedRight = false;
						return true;
					}
					else
						return false;
				}
			}
		}
	}
	return false;
}

void Character::ReceiveDamageCheck(Bullet* bullet)
{
	cocos2d::Rect CharBoundingBox = this->getBoundingBox();
	if (bullet->getBoundingBox().intersectsRect(CharBoundingBox))
	{
		bullet->setCollided(true);
		Health -= 1;
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
					cocos2d::Rect CharBoundingBox = this->getBoundingBox();
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
					cocos2d::Rect CharBoundingBox = this->getBoundingBox();
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
					cocos2d::Rect CharBoundingBox = this->getBoundingBox();
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