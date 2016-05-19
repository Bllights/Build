#pragma once;
#ifndef __SHOPPING_SCENE_H__
#define __SHOPPING_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BottomShopper{
public:
	BottomShopper(){
		L_Bottom=Layer::create();

		//Shopping=Sprite::create("");
		Money=Sprite::create("Money.png");
		//L_Bottom->addChild(Shopping);
		L_Bottom->addChild(Money);
		Money->setAnchorPoint(Point(0,0));
		Money->setPosition(160,0);

	}

	Sprite* Shopping;
	Sprite* Money;
	
	Label* S_Money;

	int money;

	Layer* L_Bottom;

public:

	bool IsTouchEndedMoney(Touch* touch){
		if(Money->getBoundingBox().containsPoint(touch->getLocation())) return true; else return false;
	}

	inline Layer* Return_layer(){ return L_Bottom;}
};

class ShoppingScene : public Layer
{
private:
	Sprite* background2;
	Sprite* background1;

	BottomShopper* L[5];

public:
	ShoppingScene();
	~ShoppingScene();
    static  Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(ShoppingScene);
	
	//ÅÍÄ¡    
	EventListenerTouchOneByOne* listener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch,  Event* event);

};
#endif
