#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SplashScene.h"

USING_NS_CC;

typedef struct tagResource
{
	cocos2d::CCSize size;
	char directory[100];
}   Resource;

static Resource smallResource = { cocos2d::CCSizeMake(480, 320), "SD" };
static Resource mediumResource = { cocos2d::CCSizeMake(960, 640), "HD" };
static Resource largeResource = { cocos2d::CCSizeMake(1024, 768), "HDR" };
static cocos2d::Size designResolution = cocos2d::Size(1024, 768);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	// turn on display FPS
	//director->setDisplayStats(true);
	// set FPS. the default value is 1.0/60 if you don't call this
	//director->setAnimationInterval(1.0f / 60);

	if (!glview)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		{
			// Creates an application with window if using a PC to run
			glview = GLViewImpl::createWithRect("PC Version", cocos2d::Rect(0, 0, mediumResource.size.width, mediumResource.size.height));
		}
#else
		{
		// Creates the application; Window size I assume take from mobile
		glview = GLViewImpl::create("Mobile Version");
	}
#endif
		director->setOpenGLView(glview);
	}

	// Set your designResolution (Fixed ratio of your game)
	glview->setDesignResolutionSize(designResolution.width, designResolution.height, ResolutionPolicy::EXACT_FIT);

	register_all_packages();
	auto scene = HelloWorld::createScene();
	director->runWithScene(scene);
	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
