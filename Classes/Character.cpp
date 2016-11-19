#include "Character.h"

Character::Character()
{
	CharacterCurrentSprite = NULL;
	CharCurrentState = C_IDLE;
}

Character::~Character()
{
}

void Character::Init(RESOURCES CharIdleSprite, RESOURCES CharMoveUpSprite, RESOURCES CharMoveDownSprite, RESOURCES CharMoveLeftSprite, RESOURCES CharMoveRightSprite, USHORT x, USHORT y)
{
	position = Vec2(x,y);

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
}

void Character::update(float dt)
{
	CharacterCurrentSprite->Render(position.x, position.y);

	switch (CharCurrentState)
	{
	case C_IDLE:
		CharacterCurrentSprite->ChangeTexture(CharacterIdleSprite);
		break;
	case C_WALK_UP:
		if (!CollidedUp)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveUpSprite);
			Walk(Vec2(0, 1));
		}
		break;
	case C_WALK_DOWN:
		if (!CollidedDown)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveDownSprite);
			Walk(Vec2(0, -1));
		}
		break;
	case C_WALK_LEFT:
		if (!CollidedLeft)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveLeftSprite);
			Walk(Vec2(-1, 0));
		}
		break;
	case C_WALK_RIGHT:
		if (!CollidedRight)
		{
			CharacterCurrentSprite->ChangeTexture(CharacterMoveRightSprite);
			Walk(Vec2(1, 0));
		}
		break;
	}
}
SpriteManager Character::GetCharCurrentSprite(void)
{
	return *CharacterCurrentSprite;
}
void Character::CollisionCheck(cocos2d::CCTMXLayer *TileLayer)
{
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

void Character::Walk(Vec2 dir)
{
	position += 2 * dir;
}