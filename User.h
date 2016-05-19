#pragma once

#include"cocos2d.h"

USING_NS_CC;

#define MAX_LUCKY 70
#define MAX_POWER 100

//메인 노동자 
class User{
public:
#pragma region FEATURE

	//광산업그레이드
	int mine_upgrade;

	//힘의 량
	int power;

	//퍼센트
	int lucky;
	
	//돈
	int money;
	
	//광물의 개수
	int mines;//개수

	//이 객체의 스프라이트
	Sprite* main;
	Label* mine;// 라벨

#pragma endregion
	
public:
	void setimport(){
		power=UserDefault::getInstance()->getIntegerForKey("User_power")*5;
		lucky=UserDefault::getInstance()->getIntegerForKey("User_lucky")*5-5;
	}

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

	void Getminelabel(Label* tmp);

	int Getmine();

	void add_labor(int number);

	//터치가 되면
	void Touched(Touch* touch);
	
	//땅파서 광물채취
	void dig();
	
	//초기화
	void reset();
	User();
	~User();
};