#ifndef __SETUP_SCENE_H__
#define __SETUP_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class SetupScene : public cocos2d::Layer
{

public:

	EventListenerTouchOneByOne* listener;
	
	virtual bool onTouchBegan(const Touch* touch,Event* unused_event);
	virtual void onTouchMoved(const Touch* touch,Event* unused_event);
	virtual void onTouchEnded(const Touch* touch,Event* unused_event);

	SetupScene(){


	}
	~SetupScene(){

		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	}

    static cocos2d::Scene* createScene(){
		auto scene = Scene::create();
    
		auto layer = SetupScene::create();

		scene->addChild(layer);

		return scene;
	}

    virtual bool init();
    
    CREATE_FUNC(SetupScene);
};

#endif
