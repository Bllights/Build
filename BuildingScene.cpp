#include "BuildingScene.h"
#include "BuildingScrollScene.h"
#include "MiningScene.h"
#include "AdmobHelper.h"
#include "TextureFactory.h"
#include "MyBodyParser.h"

int BuildingScene::Built_number[100]={0};
int BuildingScene::Builts=0;

void BuildingScene::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
	exit(0);

#endif

}

void BuildingScene::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
		
		_back->On();
    
	}
}
void BuildingScene::Touch_book(Ref* pSender){
	
		Director::getInstance()->replaceScene(ScrollScene::createScene());

}
void BuildingScene::Touch_Setup(Ref* pSender){

	
}
void BuildingScene::Touch_Mine(Ref* pSender){
	
	Director::getInstance()->replaceScene(Mining::createScene());

}

Scene* BuildingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = BuildingScene::create();

    scene->addChild(layer);

    return scene;
}

BuildingScene::BuildingScene(){
	Poped=false;
	for(int i=0;i<100;i++) Built_number[i]=0;
	makedOb=0;
	delaynum=0;
	srand(time(NULL));
	touched=true;
	is=0;
	Builts=0;
	SavingManager = new Defaultmanager();
}
//초기화

BuildingScene::~BuildingScene()
{
	 Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

    delete _world;

    _world = nullptr;

	delete SavingManager;
	
	SavingManager=nullptr;

	delete _back;
	
	_back=nullptr;

}
//소멸자

void BuildingScene::animation_back(float dt){
	if(text==1){
		back->setTexture(background2);
		text=2;
	}else if(text==2){
		back->setTexture(background3);
		text=3;
	}else if(text==3){
		back->setTexture(background1);
		text=1;
	}
}
//뒤에 애니메이션

bool BuildingScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
	//Admob
	AdmobHelper::showAd();

	_back= new Back();
	this->addChild(_back->Getlayer(),10000);
	
	Menu_create();

	addback();

    /////////////////////////////
	
	#pragma region C_World

	winSize = Director::getInstance()->getWinSize();

    next_texture= Director::getInstance()->getTextureCache()->addImage("Planet/planet1.png");

    b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

    _world = new b2World(gravity);

    _world->SetAllowSleeping(true);

    _world->SetContinuousPhysics(true);

    // 바디데프에 좌표를 설정한다.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);

    // 월드에 바디데프의 정보(좌표)로 바디를 만든다.
    b2Body *groundBody = _world->CreateBody(&groundBodyDef);


    // 가장자리(테두리) 경계선을 그릴 수 있는 모양의 객체를 만든다.
    b2EdgeShape groundEdge;
    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundEdge;


    // 에지모양의 객체에 Set( 점1 , 점2 )로 선을 만든다.
    // 그리고 바디(groundBody)에 모양(groundEdge)을 고정시킨다.
	
    // 아래쪽.
    groundEdge.Set(b2Vec2(-100, -100), b2Vec2(100, -100));
    groundBody->CreateFixture(&boxShapeDef);

    // 왼쪽
    groundEdge.Set(b2Vec2(-100, -100), b2Vec2(-100, 1000 / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);


    // 위쪽
    groundEdge.Set(b2Vec2(-100, 1000 / PTM_RATIO),
        b2Vec2(100, 1000 / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);

    // 오른쪽
    groundEdge.Set(b2Vec2(100, 1000 / PTM_RATIO),
        b2Vec2(100, -100));
    groundBody->CreateFixture(&boxShapeDef);
#pragma endregion 
	#pragma region LISTENER
	// 월드 생성 끝   --------------------------------------------------------------------------
	listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BuildingScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BuildingScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(BuildingScene::onTouchEnded,this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#pragma endregion
	#pragma region Schedule
	this->schedule(schedule_selector(BuildingScene::tick));
	this->schedule(schedule_selector(BuildingScene::animation_back),0.5);
	this->schedule(schedule_selector(BuildingScene::Create_obtacle),5);
	this->schedule(schedule_selector(BuildingScene::setdelay),0.1);
#pragma endregion

	int t=rand()%5+1;
	set_nexttexture(TextureFactory::Create(StringUtils::format("Planet/planet%d.png",t)));

	#pragma region Popup
	L_Pop= Layer::create();
	L_Pop->setContentSize(Size(320,350));
	PopUp= Sprite::create("UI/form2.png");
	Triangle=Sprite::create("UI/triangle.png");
	PopUp->setAnchorPoint(Point(0,1));
	Triangle->setAnchorPoint(Point(0.5,0));
	Triangle->setScale(0.75);
	Triangle->setPosition(160,0);
	L_Pop->addChild(Triangle,_popup);
	L_Pop->addChild(PopUp,_popup);
	this->addChild(L_Pop,_popup);
#pragma endregion
	#pragma region First
	below_sprite = Sprite::createWithTexture(next_texture);
	below_sprite->setPosition(160,100);
	below_sprite->setScale(0.8);
	this->addChild(below_sprite,n_sprite);
	
	set_nexttexture(next_texture);
	
	above_sprite=Sprite::createWithTexture(next_texture);
	above_sprite->setPosition(160,400);
	above_sprite->setScale(0.8);
	this->addChild(above_sprite);

	Add_obtacle(Point(0,250));
#pragma endregion
	return true;
}

void BuildingScene::Create_obtacle(float dt){
	if(makedOb<1){
		Add_obtacle(Point(0,250));
		makedOb++;
	}
}
void BuildingScene::setdelay(float dt){
	if(delaynum==0) touched=true;
	if(delaynum!=0) delaynum--;
}
void BuildingScene::tick(float dt)
{
		b2Body* tmp;
		bool on=false;

		b2Body* tmp2;
		bool on2=false;

		// 매뉴얼상의 권장값
		int velocityIterations = 8;
		int positionIterations = 3;

		// Step : 물리 세계를 시뮬레이션한다.
		_world->Step(dt, velocityIterations, positionIterations);


		// 모든 물리 객체들은 링크드 리스트에 저장되어 참조해 볼 수 있도록 구현되어 있다.
		// 만들어진 객체 만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다.
		b2Body *b;
		for (b= _world->GetBodyList(); b; b = b->GetNext())
		{
			if (b->GetUserData() != nullptr&& b->GetType()==b2_dynamicBody) {
				Sprite* spriteData = (Sprite*)b->GetUserData();
				int a=b->GetPosition().x * PTM_RATIO;
				int c=b->GetPosition().y * PTM_RATIO;
				spriteData->setPosition(Point(a,c));
				spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
			if (b->GetUserData() != nullptr&& b->GetType()==b2_kinematicBody) {	
				Sprite* spriteData = (Sprite*)b->GetUserData();
				if(spriteData!=nullptr){
					spriteData->setPosition(Point(b->GetPosition().x * PTM_RATIO,
						b->GetPosition().y * PTM_RATIO));
					spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
				}
			}
			if(b->GetUserData()!=nullptr&&b->GetType()==b2_dynamicBody){
				int j=b->GetPosition().y*PTM_RATIO;
				int i=b->GetPosition().x*PTM_RATIO;

				if(i!=160){
					tmp2=b;
					on2=true;
				}

				if(j<190&&j!=100&&i==160){
					tmp=b;
					on=true;
				}

			}
			if(b->GetUserData()!=nullptr&&b->GetType()==b2_kinematicBody){
				int i=b->GetPosition().x*PTM_RATIO;
				if(i>winSize.width+50){
					b->SetLinearVelocity(b2Vec2(-10.0f,-2.5f));
				}else if(i<-50){
					b->SetLinearVelocity(b2Vec2(10.0f,2.5f));
				}
			}
		}
		if(on){
			RandAction(tmp);	
		}
		if(on2){
			ParticleSystemQuad* exp = ParticleSystemQuad::create("Particle/particle.plist");
			exp->setPosition(tmp2->GetPosition().x*PTM_RATIO,tmp2->GetPosition().y*PTM_RATIO);
			exp->setScale(0.5);
			this->addChild(exp);
		
			tmp2->DestroyFixture(tmp2->GetFixtureList());
				
			//_world->DestroyBody(b);

			tmp2->SetUserData(nullptr);
		
			this->removeChild(body_sprite);
		
			tmp2=nullptr;

			set_nexttexture(previous_texture);
				
			above_sprite->setTexture(next_texture);
			above_sprite->setVisible(true);
		
		

		}	
	
}

bool BuildingScene::onTouchBegan(Touch* touch, Event* event){
	Rect rect=Triangle->getBoundingBox();
	Point layer= L_Pop->getPosition();
	rect=Rect(rect.getMinX(),rect.getMinY()+layer.y,rect.getMaxX(),rect.getMaxY()+layer.y);
		
	if(Poped){
		if(rect.containsPoint(touch->getLocation())){
				MoveBy* move= MoveBy::create(1.0,Point(0,-300));
			L_Pop->runAction(move);
				Poped=false;
		}
		return true;
	}
	if(rect.containsPoint(touch->getLocation())){
		MoveBy* move= MoveBy::create(1.0,Point(0,300));
		L_Pop->runAction(move);
		Poped=true;
	}
	_back->onTouchBegan(touch);

    return true;
}
void BuildingScene::onTouchMoved(Touch* touch, Event* event){
	

}
void BuildingScene::onTouchEnded(Touch* touch, Event* event){
	Rect rect=Triangle->getBoundingBox();
	Point layer= L_Pop->getPosition();
	rect=Rect(rect.getMinX(),rect.getMinY()+layer.y,rect.getMaxX(),rect.getMaxY()+layer.y);
	if(rect.containsPoint(touch->getLocation())){
			return;
	}
	if(Poped){
		
			return;
	}

	int t=_back->onTouchEnded(touch);
	
	if(t==1) menuCloseCallback(this);
	
	else if(t==2) return;
	
	if(!UI->getBoundingBox().containsPoint(touch->getLocation())&&touched){
		
		above_sprite->setVisible(false);

		addNewSpriteAtPosition(Point(160,400));
		
		touched=false;
		delaynum+=10;

	}

}

void BuildingScene::addNewSpriteAtPosition(Vec2 location)
{
	Sprite* pSprite = Sprite::createWithTexture(next_texture);
    pSprite->setPosition(Vec2(location.x, location.y));
	pSprite->setScale(0.8);
	this->addChild(pSprite,n_sprite);
	
	body_sprite=pSprite;

	b2BodyDef bodyDef;
	
	bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.userData = pSprite;

    b2Body* body = _world->CreateBody(&bodyDef);
    
	b2CircleShape circle;
    circle.m_radius =BODY_RADIO;

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = restitutions;

    body->CreateFixture(&fixtureDef);
	

}
void BuildingScene::Add_obtacle(Vec2 location)
{
	float slopex=10.0f+rand()%2;

	Sprite* pSprite = Sprite::create("Obstacle1.png");
    pSprite->setPosition(Vec2(location.x, location.y));
	this->addChild(pSprite);
	body_sprite=pSprite;

	b2BodyDef bodyDef;

	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO); 
	bodyDef.linearVelocity = b2Vec2(slopex,slopex/4);

	bodyDef.userData = pSprite;

    b2Body* body = _world->CreateBody(&bodyDef);

	MyBodyParser::getInstance()->parseJsonFile("Obstacle1.json");
	MyBodyParser::getInstance()->b2BodyJson(pSprite,"Obstacle2",body);

}
// 방해물 만들기

void BuildingScene::addback() {
	background1=TextureFactory::Create("Background/background2_1.png");
	background2=TextureFactory::Create("Background/background2_2.png");
	background3=TextureFactory::Create("Background/background2_3.png");

	back=Sprite::createWithTexture(background1);
	back->setAnchorPoint(Point(0,0));
	this->addChild(back,n_background);
	text=1;
}

void BuildingScene::Menu_create(){
	t_Book=Sprite::create("UI/Book.png");
	t_Setup=Sprite::create("UI/Setup.png");
	t_Mine=Sprite::create("UI/Mining.png");
	Mine=Sprite::create("UI/Mining.png");
	Setup=Sprite::create("UI/Setup.png");
	Book=Sprite::create("UI/Book.png");

	t_Book->setOpacity(150);
	t_Setup->setOpacity(150);
	t_Mine->setOpacity(150);
	_ui1=MenuItemSprite::create(Book,t_Book,Book,CC_CALLBACK_1(BuildingScene::Touch_book,this));
	_ui2=MenuItemSprite::create(Setup,t_Setup,Setup,CC_CALLBACK_1(BuildingScene::Touch_Setup,this));
	_ui3=MenuItemSprite::create(Mine,t_Mine,Mine,CC_CALLBACK_1(BuildingScene::Touch_Mine,this));
	
	UI=Menu::create(_ui3,_ui1,_ui2,NULL);
	UI->alignItemsHorizontallyWithPadding(5);
	//UI->setAnchorPoint(Point(1,1));
	UI->setPosition(243,458);

	this->addChild(UI,100);

}
void BuildingScene::set_nexttexture(Texture2D* texture2D){
		#pragma region NEXTTEXTURE
	previous_texture=texture2D;
	switch (rand()%5)
	{
	case 0:
		next_texture=TextureFactory::Create("Planet/planet1.png");
		Built_number[Builts]=1;
		break;
	case 1:
		next_texture=TextureFactory::Create("Planet/planet2.png");
		Built_number[Builts]=2;
		break;
	case 2:
		next_texture=TextureFactory::Create("Planet/planet3.png");
		Built_number[Builts]=3;
		break;
	case 3:
		next_texture=TextureFactory::Create("Planet/planet4.png");
		Built_number[Builts]=4;
		break;
	case 4:
		next_texture=TextureFactory::Create("Planet/planet5.png");
		Built_number[Builts]=5;
		break;
	}
#pragma endregion
	if(Builts==0) Builts++;


}

void BuildingScene::RandAction(b2Body* b){
	if(b->GetType()==b2_kinematicBody) return;

	if(rand()%100<LUCKY_PERCENT){
		#pragma region NOBOOM
		b->DestroyFixture(b->GetFixtureList());
		//_world->DestroyBody(b);
		b->SetUserData(nullptr);
		action_sprite=Sprite::createWithTexture(body_sprite->getTexture());
		
		this->removeChild(body_sprite);
		body_sprite=nullptr;		
		b=nullptr;
		action_sprite->setPosition(160,190);
		action_sprite->setScale(0.8);
		this->addChild(action_sprite);
		action_sprite->runAction(MoveBy::create(1.0,Point(0,-90)));
		below_sprite->runAction(MoveBy::create(1.0,Point(0,-90)));
		
		if(is==1){
			below2_sprite->runAction(MoveBy::create(1.0,Point(0,-90)));
			
		}
		is=1;
		
		below2_sprite=below_sprite;
		
		below_sprite=action_sprite;
		
		Builts++;

		//touched=true;
		
		delaynum+=10;
#pragma endregion//안터짐
	}else{
		#pragma region BOOM
		
		b->DestroyFixture(b->GetFixtureList());

		b->SetUserData(nullptr);
		
		this->removeChild(body_sprite);
		
		b=nullptr;
#pragma endregion//터짐
	}
	//다음 텍스쳐로 바꾸기
	set_nexttexture(previous_texture);
	above_sprite->setTexture(next_texture);
	above_sprite->setVisible(true);

	
}