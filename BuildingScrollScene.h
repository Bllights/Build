#pragma once;
#ifndef __SCROLL_SCENE_H__
#define __SCROLL_SCENE_H__

#include "cocos2d.h"
#include "TextureFactory.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;	

class bubble{
public:
	Sprite* main;
	
	Label* text;

	int x, y;

	Rect planet_rect;

	bool visible;

	int person;//인구수
	
	int fund;//주가
	int lastfund;

	String name;//이름

	bubble(int a,int b){
		x=a;
		y=b;
	}
	void init(Node* node){
		main=Sprite::create("UI/Page.png");
		main->setPosition(x,y);
		main->setAnchorPoint(Point(0,0));
		node->addChild(main,20);
	}
	void destory(Node* node){
		
		main->setVisible(false);
		
		node->removeChild(main);
		main=nullptr;
	}
	bool IsUp(){
		if(fund>lastfund){
			return true;
		}else{
			return false;
		}
	}
};

class ScrollScene : public Layer
{
private:
	Vector<Sprite*> drawed;
	
	Sprite* touched_spr;

	bool touched_spr_bool;
private:
	int time;

private:
	bool end;

	int maked;
	
	bubble* Speech;

	Sprite* Background[10];

	Texture2D* one;
	Texture2D* two;
	Texture2D* three;

	ScrollView* scroll;
	
	Layer* Built;

	Sprite* t_Building;
	Sprite* t_Setup;
	Sprite* t_Mine;

	Sprite* Mine;
	Sprite* Setup;
	Sprite* Building;

	MenuItemSprite *_ui1,*_ui2,*_ui3;

	Menu* UI;

	int number;

public:

    static  Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(ScrollScene);

	virtual bool onTouchBegan( Touch *touch,  Event * event);
	virtual void onTouchMoved( Touch *touch,  Event * event);
	virtual void onTouchEnded( Touch *touch,  Event * event);

	void ChangeBack(float dt);

	void Planet_create(int num,int B_num);
	
	void  Menu_create();

	Texture2D* settexture(int num);

	void drawdt(float dt);

	void drawTexture(int number);

	void create_b(){
		for(int i=0;i<10;i++){
			Background[i]=Sprite::createWithTexture(i%3==0?one:i%3==1?two:three);
			Background[i]->setAnchorPoint(Point(0,0));
			Background[i]->setPosition(0,i*480);
			Built->addChild(Background[i],0);
		}
		number=1;
	}

	void Touch_building(Ref* pSender);

	void Touch_Setup(Ref* pSender);

	void Touch_Mine(Ref* pSender);

};


#endif
