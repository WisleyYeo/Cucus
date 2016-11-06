#include "SpriteManager.h"

USING_NS_CC;

SpriteManager::SpriteManager()
{
	m_Sprite = NULL;	
}

void SpriteManager::Init(RESOURCES NewResource, USHORT x, USHORT y, bool Draw)
{
	m_Sprite = cocos2d::Sprite::create(ResourceFileName[NewResource]);
	//m_Sprite->setScale(0.1875f);
	if(Draw)
		Render(x, y);
}
void SpriteManager::ChangeTexture(RESOURCES NewResource)
{
	m_Sprite->setTexture(cocos2d::Sprite::create(ResourceFileName[NewResource])->getTexture());
}
void SpriteManager::Render(USHORT x, USHORT y)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_Sprite->setPosition(Point(x,y));
}
SpriteManager::~SpriteManager()
{
}

