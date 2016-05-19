#include "ShoppingScene.h"

Scene* ShoppingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ShoppingScene::create();

    scene->addChild(layer);

    return scene;
}
ShoppingScene::ShoppingScene(){
	
	background1=Sprite::create("UI/form.png");
	background1->setAnchorPoint(Point(0,0));
	background1->setPosition(0,400);

	background2=Sprite::create("UI/form1_1.png");
	background2->setAnchorPoint(Point(0,0));

}
ShoppingScene::~ShoppingScene(){

}
bool ShoppingScene::init()
{
    
	if (!Layer::init())
    {
        return false;
    }
	this->addChild(background2);
	this->addChild(background1);
	return true;
}

bool ShoppingScene::onTouchBegan(Touch* touch, Event* event)
{
	
    return true;
}
void ShoppingScene::onTouchMoved(Touch* touch, Event* event){
	

}
void ShoppingScene::onTouchEnded(Touch* touch, Event* event){
	

}
