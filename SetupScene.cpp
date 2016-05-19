#include"SetupScene.h"

bool SetupScene::init(){
	
	if ( !Layer::init() )
    {
        return false;
    }

	listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan=(CC_CALLBACK_2(SetupScene::onTouchBegan,this));
	listener->onTouchMoved=(CC_CALLBACK_2(SetupScene::onTouchMoved,this));
	listener->onTouchEnded=(CC_CALLBACK_2(SetupScene::onTouchEnded,this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);




}
bool SetupScene::onTouchBegan(const Touch* touch,Event* unused_event){


	return true;
}
void SetupScene::onTouchMoved(const Touch* touch,Event* unused_event){



}
void SetupScene::onTouchEnded(const Touch* touch,Event* unused_event){



}