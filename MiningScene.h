#ifndef __MINING_SCENE_H__
#define __MINING_SCENE_H__

#include "cocos2d.h"
#include "User.h"
#include "Labor.h"
#include "cocos-ext.h"

#include "Defaultmanager.h"
#include "MBottomManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_POWERNUM 19
#define MAX_LUCKYNUM 14
#define MAX_PEOPLENUM 7
#define MAX_UPGRADENUM 10

#define DEVELOPER false
#define FONT "fonts/arial.ttf"
#if 1
//user
class UCharacter{
public:
	int n_people;
	int n_upgrade;

	int n_power;
	int n_lucky;

	UCharacter(){
		n_power=1;
		n_lucky=1;
		n_people=1;
		n_upgrade=1;
	}

};

#endif // 1
//class icharacter ucharacter

class Mining : public cocos2d::Layer
{
public:
	#pragma region enum
	enum{
		mine_background=0,
		tmp_layers,
		scroll,
		mine_layer0,
		mine_layer1,
		mine_layer2,
		mine_layer3,
		mine_layer4,
		mine_layer5,
		mine_layer6,
		ui
	};
#pragma endregion

	UCharacter* uch;
	int n_power;

	User *m_user;
	Labor *labor[7];

	ScrollView* Mine_scroll;

	LayerColor* Mine;
	
/////////////////////////////////////////////////
	void Up_Lucky();

	void Up_Power(int a);
	
	void Up_Upgrade();
	
	void Up_People();
/////////////////////////////////////////////////
	Label* Lv[11];//Lv1 라벨 아래에서 부터 0,1,2,3

	Label* l_Lv_lucky[7];
	Label* l_Lv_power[7];

	Label* minenumber;

private:
	bool labor_on[7];

	Sprite* Background;
private:
	void Scroll_create();

	void Background_create();

	void Menu_create();

	void Label_create();

public:
	BottomManager* B_manager;

	Defaultmanager* Savingmanager;

	EventListenerTouchOneByOne* listener;

	void add_labor(int number);
	//노동자 추가

	void Touch_book(Ref* pSender);
	//BookScene으로

	void Touch_Setup(Ref* pSender);
	//setupscene으로

	void Touch_Building(Ref* pSender);
	//BuildingScene으로

	void labor_texture(float dt);
	//노동자 텍스쳐 바꾸기

	Mining();

	~Mining();

	void user_time(float dt);
	//시간 돌리기 0.0초

	bool onTouchBegan(Touch* touch, Event *unused_event);
	//터치 began

	void onTouchEnded(Touch* touch, Event *unused_event);
	//터치end

    static Scene* createScene();
	//신 생성
	
    virtual bool init();
	//생성

	void  menuCloseCallback(Ref* sender);

	void onKeyReleased( EventKeyboard::KeyCode keycode, Event *event);


    CREATE_FUNC(Mining);
};

#endif
