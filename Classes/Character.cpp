#include "Character.h"

USING_NS_CC;

Character::Character()
{
	CharacterCurrentSprite = NULL;
	CharCurrentState = C_IDLE;
}

void Character::Init(RESOURCES CharIdleSprite, RESOURCES CharMoveUpSprite, RESOURCES CharMoveDownSprite,
	RESOURCES CharMoveLeftSprite, RESOURCES CharMoveRightSprite, USHORT x, USHORT y)
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

}

void Character::update(float dt)
{

	switch (CharCurrentState)
	{
	case C_IDLE:
		CharacterCurrentSprite->ChangeTexture(CharacterIdleSprite);
		break;
	case C_UP:
		CharacterCurrentSprite->ChangeTexture(CharacterMoveUpSprite);
		break;
	case C_DOWN:
		CharacterCurrentSprite->ChangeTexture(CharacterMoveDownSprite);
		break;
	case C_LEFT:
		CharacterCurrentSprite->ChangeTexture(CharacterMoveLeftSprite);
		break;
	case C_RIGHT:
		CharacterCurrentSprite->ChangeTexture(CharacterMoveRightSprite);
		break;

	}
}
SpriteManager Character::GetCharCurrentSprite(void)
{
	return *CharacterCurrentSprite;
}
Character::~Character()
{
}
