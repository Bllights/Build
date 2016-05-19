#pragma once

#include "cocos2d.h"
#include "TextureFactory.h"

USING_NS_CC;

#define MAX_LUCKY 70
#define MAX_POWER 100


//���� �뵿�� 
class Labor{

public:
	//������׷��̵�
	int mine_upgrade;//1 2 3 4 5 6 7 8 9 10

	//���� ��
	int power;//1 ~ 19

	//�ۼ�Ʈ
	int lucky;
	
	//��
	int money;
	
	//������ ����
	int mines;//����

public:

	Layer* layer_labor;

	bool on;//��������

	Sprite* m_sprite;//��������Ʈ
	
	Point m_point;// ��ġ

	int number;//��ȣ 1,2,3,4,5,6,7

private:
	Texture2D* t_first;
	Texture2D* t_second;
	Texture2D* t_third;

	bool first;//ù��° �׸�����
	bool second;//�ι�° �׸�����
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
	//�뵿�� ������ �־��ֱ�

	void texture_update(float delta);
	// ���������� ���߿�

	void setPosition(const Vec2 &point);
	//������
	
	bool init();
	//init

	void dig();
	//�ı�->�ؽ��� �ƴ� ��
};