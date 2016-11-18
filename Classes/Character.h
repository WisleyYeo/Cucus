#pragma once
#include "SpriteManager.h"

USING_NS_CC;

class Character
{
public:
	enum CharState
	{
		C_IDLE,
		C_WALK_UP,
		C_WALK_DOWN,
		C_WALK_LEFT,
		C_WALK_RIGHT,
		C_TOTALSTATES
	};
	int CharCurrentState;

	Character();
	~Character();
	
	void Init(RESOURCES CharIdleSprite, RESOURCES CharMoveUpSprite, RESOURCES CharMoveDownSprite,  RESOURCES CharMoveLeftSprite, RESOURCES CharMoveRightSprite,USHORT x, USHORT y);
	//Character Update
	virtual void update(float);

	bool CollisionCheck(cocos2d::Rect checkAgainst);
	SpriteManager GetCharCurrentSprite(void);

	void Walk(Vec2 dir);

	

private:
	SpriteManager *CharacterCurrentSprite;
	RESOURCES CharacterIdleSprite;
	RESOURCES CharacterMoveUpSprite;
	RESOURCES CharacterMoveDownSprite;
	RESOURCES CharacterMoveLeftSprite;
	RESOURCES CharacterMoveRightSprite;

	Vec2 position;
	
};

