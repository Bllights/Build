#pragma once;
#ifndef __BUILDING_SCENE_H__
#define __BUILDING_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Defaultmanager.h"
#include "Backmanager.h"

#define PTM_RATIO 32

#define BODY_RADIO 1.1

#define restitutions 0.3f
			
#define LUCKY_PERCENT 100

USING_NS_CC;

//build_spr[0]->맨처음꺼
//

class BuildingScene : public Layer
{
public:
	
	void setdelay(float dt);

	void Create_obtacle(float dt);
	
	//함수들
	void RandAction(b2Body* b);

	//스케쥴러
	void animation_back(float dt);

	void tick(float dt);

	void Touch_book(Ref* pSender);
	
	void Touch_Setup(Ref* pSender);
	
	void Touch_Mine(Ref* pSender);

	void addback();

	void Menu_create();

	void addNewSpriteAtPosition( Vec2 location);

	void Add_obtacle(Vec2 location);

	void set_nexttexture(Texture2D* texture2D);

	void  menuCloseCallback(Ref* sender);

	void onKeyReleased( EventKeyboard::KeyCode keycode, Event *event);

private://Menu
	Sprite* t_Book;
	Sprite* Book;

	Sprite* Mine;
	Sprite* t_Mine;

	Sprite* Setup;
	Sprite* t_Setup;

	MenuItemSprite* _ui1;
	MenuItemSprite* _ui2;
	MenuItemSprite* _ui3;

	Menu* UI;
public:
	Sprite* above_sprite;

	Sprite* body_sprite;

	int is;
	Sprite* below2_sprite;
	Sprite* below_sprite;
	Sprite *action_sprite;

	bool touched;
public:
	Layer* L_Pop;

	Sprite* PopUp;
	Sprite* Triangle;
	
	bool Poped;


	int makedOb;

	static int Built_number[100];
	static int Builts;

	Back* _back;

	enum{
		n_background=0,
		n_sprite=1,
		_layers=2,
		_popup=3
	};

    static  Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(BuildingScene);
	
	//생성자 소멸자
	BuildingScene();    
	~BuildingScene();
	
	//터치    
	EventListenerTouchOneByOne* listener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch,  Event* event);

private:
	int delaynum;

	Defaultmanager* SavingManager;

	Size winSize;

    b2World* _world;
	
	Sprite* back;

	int text;

	Texture2D* background1;
	Texture2D* background2;
	Texture2D* background3;
	
	Texture2D* previous_texture;

	Texture2D* next_texture;

};
#endif
