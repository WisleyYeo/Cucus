#pragma once
#include <iostream>
#include "cocos2d.h"
#include "RssManager.h"
class SpriteManager
{
private:
	cocos2d::Sprite* m_Sprite;
public:
	SpriteManager();
	~SpriteManager();

	void Init (RESOURCES NewResource, USHORT x, USHORT y, bool Draw);
	cocos2d::Sprite* getSprite(void) { return m_Sprite; };
	void ChangeTexture(RESOURCES NewResource);
	void Render(USHORT x, USHORT y);
	void setY(float newY) {
		m_Sprite->setPositionY(newY);
	};
	float getY(void)
	{
		return m_Sprite->getPositionY();
	};
};

