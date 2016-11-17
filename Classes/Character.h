#pragma once
#include "SpriteManager.h"
class Character
{
public:
	enum CharState
	{
		C_IDLE,
		C_UP,
		C_DOWN,
		C_LEFT,
		C_RIGHT,
		C_TOTALSTATES
	};
	int CharCurrentState;
	Character();
	~Character();
	SpriteManager *CharacterCurrentSprite;
	RESOURCES CharacterIdleSprite;
	RESOURCES CharacterMoveUpSprite;
	RESOURCES CharacterMoveDownSprite;
	RESOURCES CharacterMoveLeftSprite;
	RESOURCES CharacterMoveRightSprite;
	void Init(RESOURCES CharIdleSprite, RESOURCES CharMoveUpSprite, RESOURCES CharMoveDownSprite, 
		RESOURCES CharMoveLeftSprite, RESOURCES CharMoveRightSprite,USHORT x, USHORT y);
	bool CollisionCheck(cocos2d::Rect checkAgainst);
	SpriteManager GetCharCurrentSprite(void);

	//Character Update
	virtual void update(float);


	
};

