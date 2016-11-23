#ifndef __Touch_Swipe_H__
#define __Touch_Swipe_H__
#include "cocos2d.h" 
#define COCOS2D_DEBUG 1
using std::vector;
using namespace cocos2d;

class TouchSwipe : public cocos2d::Node
{

public:

	//static override create function
	TouchSwipe *createTouch();

	TouchSwipe();
	~TouchSwipe();

	//touch events
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void onTouchCancelled(Touch *touch, Event *event);

	void setSwipedLeft(bool swipedLeft);
	bool getSwipedLeft();
	void setSwipedRight(bool swipedRight);
	bool getSwipedRight();

	bool getIsTouchedDown();

	virtual bool init();
	void update(float dt);

	CREATE_FUNC(TouchSwipe);

	Sprite* mainBackground;

private:

	Size ratio = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//toggle touch
	bool isTouchDown;

	// Where you swipe bro
	bool swipedLeft, swipedRight;

	//touch position storage
	float initialTouchPos[2];
	float currentTouchPos[2];
};


#endif