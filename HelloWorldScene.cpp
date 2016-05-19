#include "HelloWorldScene.h"

HelloWorld::HelloWorld(){


}
HelloWorld::~HelloWorld(){


}
Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	m_back=Sprite::create("Main/back.png");
	m_back->setPosition(160,240);
	m_back->setScale(0.402);


	this->addChild(m_back);
  
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
