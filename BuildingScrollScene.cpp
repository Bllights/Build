#include "BuildingScrollScene.h"
#include "BuildingScene.h"
#include "MiningScene.h"

Scene* ScrollScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ScrollScene::create();

    scene->addChild(layer);

    return scene;
}
bool ScrollScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
	touched_spr_bool=false;

	Menu_create();

	end=false;

	Built=Layer::create();
	Built->setContentSize(Size(320,4800));
	scroll=ScrollView::create(Size(320,480),Built);
	scroll->setDirection(ScrollView::Direction::VERTICAL);
    scroll->setBounceable(false);
    this->addChild(scroll,0);

	one=TextureFactory::Create("Background/background2_1.png");
	two=TextureFactory::Create("Background/background2_2.png");
	three=TextureFactory::Create("Background/background2_3.png");

	create_b();

	auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(ScrollScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ScrollScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(ScrollScene::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(ScrollScene::ChangeBack),0.5f);
	this->schedule(schedule_selector(ScrollScene::drawdt),0.4f);

	maked=0;


    return true;
	
}
void ScrollScene::ChangeBack(float dt){
	if(number==1){
		for(int i=0;i<10;i++){
			Background[i]->setTexture(i%3==0?one:i%3==1?two:three);
		}
		number=2;
	}else if(number==2){
		for(int i=0;i<10;i++){
			Background[i]->setTexture(i%3==0?two:i%3==1?three:one);
		}
		number=3;
	}else if(number==3){
		for(int i=0;i<10;i++){
			Background[i]->setTexture(i%3==0?three:i%3==1?one:two);
		}
		number=1;
	}

}
bool ScrollScene::onTouchBegan( Touch *touch,  Event * event){
	int as=0;
	for(Sprite* a : drawed){
		as++;
		Rect r=a->getBoundingBox();

		Rect scroll_rect=Rect(r.origin.x+scroll->getContentOffset().x,
					r.origin.y+scroll->getContentOffset().y,
					r.size.width,r.size.height);

		if(scroll_rect.containsPoint(touch->getLocation())){
			touched_spr=a;
			touched_spr_bool=true;
			Planet_create(as,1);	
		}
		
	}
	return true;
}
void ScrollScene::onTouchMoved( Touch *touch,  Event * event){
	if(touched_spr_bool){
		Rect r=touched_spr->getBoundingBox();

		Rect scroll_rect=Rect(r.origin.x+scroll->getContentOffset().x,
					r.origin.y+scroll->getContentOffset().y,
					r.size.width,r.size.height);

		if(!scroll_rect.containsPoint(touch->getLocation())){


			Speech->destory(this);

			touched_spr_bool=false;

		}
	}

}
void ScrollScene::onTouchEnded( Touch *touch,  Event * event){

	if(touched_spr_bool){

		Speech->destory(Built);

			touched_spr_bool=false;

	}
}
Texture2D* ScrollScene::settexture(int num){
	switch (num-1)
	{
	case 0:
		return TextureFactory::Create("Planet/planet1.png");
		break;
	case 1:
		return TextureFactory::Create("Planet/planet2.png");
		break;
	case 2:
		return TextureFactory::Create("Planet/planet3.png");
		break;
	case 3:
		return TextureFactory::Create("Planet/planet4.png");
		break;
	case 4:
		return TextureFactory::Create("Planet/planet5.png");
		break;
	}

}
void ScrollScene::drawdt(float dt){
	if(!end){
		if(BuildingScene::Built_number[maked+1]==0){
			end=true;
			return;
		}
		auto spr=Sprite::createWithTexture(
			settexture(BuildingScene::Built_number[maked]));
		spr->setPosition(160,100+(maked++)*100);
		Built->addChild(spr);
		
		drawed.pushBack(spr);

	}
}
void ScrollScene::Menu_create(){
	t_Building=Sprite::create("UI/Building.png");
	t_Setup=Sprite::create("UI/Setup.png");
	t_Mine=Sprite::create("UI/Mining.png");
	Mine=Sprite::create("UI/Mining.png");
	Setup=Sprite::create("UI/Setup.png");
	Building=Sprite::create("UI/Building.png");
	t_Building->setOpacity(150);
	t_Setup->setOpacity(150);
	t_Mine->setOpacity(150);
	_ui1=MenuItemSprite::create(Building,t_Building,Building,CC_CALLBACK_1(ScrollScene::Touch_building,this));
	_ui2=MenuItemSprite::create(Setup,t_Setup,Setup,CC_CALLBACK_1(ScrollScene::Touch_Setup,this));
	_ui3=MenuItemSprite::create(Mine,t_Mine,Mine,CC_CALLBACK_1(ScrollScene::Touch_Mine,this));
	
	UI=Menu::create(_ui3,_ui1,_ui2,NULL);
	UI->alignItemsHorizontallyWithPadding(5);
	UI->setPosition(243,458);

	this->addChild(UI,10);


}
void ScrollScene::Touch_building(Ref* pSender){

	Director::getInstance()->replaceScene(BuildingScene::createScene());

}
void ScrollScene::Touch_Setup(Ref* pSender){

}
void ScrollScene::Touch_Mine(Ref* pSender){

	Director::getInstance()->replaceScene(Mining::createScene());

}
void ScrollScene::Planet_create(int num,int B_num){
			int i=	   touched_spr->getPosition().x;
			int j=		 touched_spr->getPosition().y;
	Speech=new bubble(i,j);

	Speech->init(Built);

}