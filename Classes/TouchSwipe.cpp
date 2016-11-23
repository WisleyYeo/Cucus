#include "TouchSwipe.h"

TouchSwipe::TouchSwipe() {}
TouchSwipe::~TouchSwipe() {}

TouchSwipe* TouchSwipe::createTouch()
{
	//creates a new object from its constructor
	TouchSwipe* touch = new TouchSwipe();

	//initialize the object
	touch->init();

	//set the object to be autorelease
	touch->autorelease();

	//return the object
	return touch;
}

bool TouchSwipe::init()
{	
	// set background from level selection
	mainBackground = Sprite::create("LevelSelect/LVS_Background-01.png");
	mainBackground->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
	mainBackground->setScaleX((ratio.width / mainBackground->getContentSize().width));
	mainBackground->setScaleY((ratio.height / mainBackground->getContentSize().height));

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(TouchSwipe::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TouchSwipe::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TouchSwipe::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(TouchSwipe::onTouchCancelled, this);

	// give the background the listener
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, mainBackground);

	isTouchDown = false;
	swipedLeft = false;
	swipedRight = false;

	initialTouchPos[0] = 0;
	initialTouchPos[1] = 0;

	this->scheduleUpdate();

	return true;
}

void TouchSwipe::update(float dt)
{
	auto rangeX = origin.x + visibleSize.width * 0.1;

	if (isTouchDown == true)
	{
		// if current pos is right of initial pos
		if (currentTouchPos[0] - initialTouchPos[0] > rangeX)
		{
			swipedRight = true;
			swipedLeft = false;
		}
		// if current pos is left of initial pos
		else if (currentTouchPos[0] - initialTouchPos[0] < -rangeX)
		{
			swipedLeft = true;
			swipedRight = false;
		}
	}
}

void TouchSwipe::setSwipedLeft(bool swipedLeft)
{
	this->swipedLeft = swipedLeft;
}
bool TouchSwipe::getSwipedLeft()
{
	return swipedLeft;
}
void TouchSwipe::setSwipedRight(bool swipedRight)
{
	this->swipedRight = swipedRight;
}
bool TouchSwipe::getSwipedRight()
{
	return swipedRight;
}

bool TouchSwipe::getIsTouchedDown()
{
	return isTouchDown;
}

bool TouchSwipe::onTouchBegan(Touch *touch, Event *event)
{
	initialTouchPos[0] = touch->getLocation().x;
	initialTouchPos[1] = touch->getLocation().y;
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;

	isTouchDown = true;

	return true;
}
void TouchSwipe::onTouchMoved(Touch *touch, Event *event)
{
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;
}
void TouchSwipe::onTouchEnded(Touch *touch, Event *event)
{
	isTouchDown = false;
}
void TouchSwipe::onTouchCancelled(Touch *touch, Event *event)
{
	onTouchEnded(touch, event);
}