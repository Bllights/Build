#include "Labor.h"

bool Labor::init(){

	m_sprite=Sprite::create("Labor/labor1_1.png");

	m_point=Point(0,0);

	layer_labor=Layer::create();
	layer_labor->addChild(m_sprite);
	first=true;
	second=false;
	third=false;

	on=false;
	
	lucky=0;
	power=5;
	mines=0;

	return true;
}

void Labor::setTexture(std::string filepath){
	t_first=TextureFactory::Create(filepath+"_1.png");
	t_second=TextureFactory::Create(filepath+"_2.png");
	t_third=TextureFactory::Create(filepath+"_3.png");
}
void Labor::setPosition(const Vec2 &point){
	m_sprite->setPosition(point);
	
	m_point=point;
}
void Labor::setScale(float scale){

	m_sprite->setScale(scale);

}
void Labor::texture_update(float delta){
	if(!on) return;
	if(first){
	
		m_sprite->setTexture(t_first); 
		dig();
		first=false;
		second=true;
	}else
	if(second){
		m_sprite->setTexture(t_second);
		second=false;
		third=true;
	}else {
		m_sprite->setTexture(t_third);
		third=false;
		first=true;
	}

}
void Labor::Add(){
	int x[7]={50,80,110,140,170,200,230};
	setPosition(Point(x[number-1],300));
	setScale(0.75);
	on=true;
}
void Labor::dig(){

	mines+=power/5;

	if(rand()%100<lucky){
		mines+=rand()%(power/10+1)+1;
		CCLOG("lucky");
	}
	
	CCLOG("labor%d : %d",number,mines);
}
void Labor::setnumber(int a){
	number=a;
}