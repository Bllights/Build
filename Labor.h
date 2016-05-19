#pragma once

#include "cocos2d.h"
#include "TextureFactory.h"

USING_NS_CC;

#define MAX_LUCKY 70
#define MAX_POWER 100


//메인 노동자 
class Labor{

public:
	//광산업그레이드
	int mine_upgrade;//1 2 3 4 5 6 7 8 9 10

	//힘의 량
	int power;//1 ~ 19

	//퍼센트
	int lucky;
	
	//돈
	int money;
	
	//광물의 개수
	int mines;//개수

public:

	Layer* layer_labor;

	bool on;//켜졌는지

	Sprite* m_sprite;//스프라이트
	
	Point m_point;// 위치

	int number;//번호 1,2,3,4,5,6,7

private:
	Texture2D* t_first;
	Texture2D* t_second;
	Texture2D* t_third;

	bool first;//첫번째 그림인지
	bool second;//두번째 그림인지
	bool third;

public:

	void setMines(int n){
		mines=n;
	}
	
	void setPower(int n){
		if(n>MAX_POWER) power=MAX_POWER;
		else
		power=n;
	}
	
	void setlucky(int n){
		if(n>MAX_LUCKY) lucky= MAX_LUCKY;
		else
		lucky=n;
	}

	void setnumber(int a);
	//

	void setScale(float scale);
	//default=1

	void setTexture(std::string filepath);

	void Add();
	//노동자 샀을때 넣어주기

	void texture_update(float delta);
	// 몇초인지는 나중에

	void setPosition(const Vec2 &point);
	//포지션
	
	bool init();
	//init

	void dig();
	//파기->텍스쳐 아닌 논리
};