#pragma once

#include"cocos2d.h"

USING_NS_CC;

#define MAX_LUCKY 70
#define MAX_POWER 100

//���� �뵿�� 
class User{
public:
#pragma region FEATURE

	//������׷��̵�
	int mine_upgrade;

	//���� ��
	int power;

	//�ۼ�Ʈ
	int lucky;
	
	//��
	int money;
	
	//������ ����
	int mines;//����

	//�� ��ü�� ��������Ʈ
	Sprite* main;
	Label* mine;// ��

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

	//��ġ�� �Ǹ�
	void Touched(Touch* touch);
	
	//���ļ� ����ä��
	void dig();
	
	//�ʱ�ȭ
	void reset();
	User();
	~User();
};