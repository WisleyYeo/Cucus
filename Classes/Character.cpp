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
		CharacterCurrentSprite->ChangeTexture(CharacterMoveUpSprite);
		Walk(Vec2(0, 1));
		break;
	case C_WALK_DOWN:
		CharacterCurrentSprite->ChangeTexture(CharacterMoveDownSprite);
		Walk(Vec2(0, -1));
		break;
	case C_WALK_LEFT:
		CharacterCurrentSprite->ChangeTexture(CharacterMoveLeftSprite);
		Walk(Vec2(-1, 0));
		break;
	case C_WALK_RIGHT:
		CharacterCurrentSprite->ChangeTexture(CharacterMoveRightSprite);
		Walk(Vec2(1,0));
		break;
	}
}
SpriteManager Character::GetCharCurrentSprite(void)
{
	return *CharacterCurrentSprite;
}
void Character::CollisionCheck(cocos2d::CCTMXLayer *TileLayer)
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
					if (TileLayer->getTileAt(Vec2(x, y))->getBoundingBox().intersectsRect(CharacterCurrentSprite->getSprite()->getBoundingBox()))
					{
						//If Collision Check returns true
						CharCurrentState = C_IDLE;
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