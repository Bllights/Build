#include "AppDelegate.h"
#include "MiningScene.h"
#include "ShoppingScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0; 
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("My Game",Rect(0,0,320,480));
        director->setOpenGLView(glview);
    }	

	if(UserDefault::getInstance()->getIntegerForKey("a_mines")==0)
		UserDefault::getInstance()->setIntegerForKey("a_mines",0);
	if(UserDefault::getInstance()->getIntegerForKey("User_power")==0)
		UserDefault::getInstance()->setIntegerForKey("User_power",1);
	if(UserDefault::getInstance()->getIntegerForKey("User_lucky")==0)
		UserDefault::getInstance()->setIntegerForKey("User_lucky",1);
	if(UserDefault::getInstance()->getIntegerForKey("MineUpgrade")==0)
		UserDefault::getInstance()->setIntegerForKey("MineUpgrade",1);
	if(UserDefault::getInstance()->getIntegerForKey("Labornum")==0)
		UserDefault::getInstance()->setIntegerForKey("Labornum",1);

	if(UserDefault::getInstance()->getIntegerForKey("LaborPower")==0)
		UserDefault::getInstance()->setIntegerForKey("LaborPower",1);


	///////////////////////////////////////////////////////////////

	director->getOpenGLView()->setDesignResolutionSize(320,480,ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(false);

    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

	auto scene = Mining::createScene();
		
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
