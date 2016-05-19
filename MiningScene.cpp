#include "MiningScene.h"
#include "BuildingScene.h"

void Mining::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	exit(0);

#endif
}

void Mining::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK) {

		Savingmanager->Saving();
        Director::getInstance()->end();
   
	}
}

Mining::Mining(){
	Savingmanager=new Defaultmanager();
	uch=new UCharacter();

	for(int i=0;i<7;i++){
		labor[i]=new Labor();
		labor_on[i]=false;
	}
	n_power=1;
	m_user= new User();

	m_user->setMines(Savingmanager->GetData("a_mines"));
	m_user->power=5*(Savingmanager->GetData("User_power"));
	m_user->lucky=5*(Savingmanager->GetData("User_lucky"))-5;

	uch->n_upgrade=Savingmanager->GetData("MineUpgrade");
	uch->n_people=Savingmanager->GetData("Labornum");
	uch->n_power=Savingmanager->GetData("User_power");
	uch->n_lucky=Savingmanager->GetData("User_lucky");

	if(m_user->power<5) m_user->power=5;
	if(m_user->lucky<0) m_user->lucky=0;
	n_power=Savingmanager->GetData("LaborPower");
	delete Savingmanager;
}

Mining::~Mining(){

	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);


}

Scene* Mining::createScene()
{
	auto scene = Scene::create();
    
    auto layer = Mining::create();

    scene->addChild(layer);

    return scene;
}

bool Mining::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	int i;

	Savingmanager=new Defaultmanager();

	Background_create();

	Scroll_create();

	B_manager=new BottomManager();
	///////////////////////////////////////////////////////
	if(!DEVELOPER){
		B_manager->Setting();
		B_manager->AddSprite(Mine);
	}else{
		B_manager->DeveloperSetting();
		B_manager->DeveloperAddSprite(Mine);
	}
	Menu_create();

	Label_create();

	#pragma region Touch
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Mining::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Mining::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	this->schedule(schedule_selector(Mining::user_time), 0.1);
	this->schedule(schedule_selector(Mining::labor_texture), 0.5);
	this->scheduleUpdate();
#pragma endregion

	#pragma region Saver
	
	Savingmanager->AddSaver("a_mines",&(m_user->mines));
	Savingmanager->AddSaver("User_power",&(uch->n_power));
	Savingmanager->AddSaver("User_lucky",&(uch->n_lucky));
	Savingmanager->AddSaver("MineUpgrade",&uch->n_upgrade);
	Savingmanager->AddSaver("Labornum",&uch->n_people);
	Savingmanager->AddSaver("LaborPower",&n_power);

	///////////////////////////////////////////////////////////////

	for(int i=1;i< uch->n_people;i++){
		labor_on[i-1]=true;
		add_labor(i-1);
	}

#pragma endregion

	m_user->Getminelabel(minenumber);

	this->setKeypadEnabled( true );

    return true;

}

void Mining::add_labor(int number){

	labor[number]->init();
	std::string tmps;
	switch(number){
	case 0: tmps="Labor/labor1";
		this->addChild(labor[0]->layer_labor,mine_layer0);break;
	case 1: tmps="Labor/labor1";
		this->addChild(labor[1]->layer_labor,mine_layer1);break;
	case 2: tmps="Labor/labor1";
		this->addChild(labor[2]->layer_labor,mine_layer2);break;
	case 3: tmps="Labor/labor1";
		this->addChild(labor[3]->layer_labor,mine_layer3);break;
	case 4: tmps="Labor/labor1"; 
		this->addChild(labor[4]->layer_labor,mine_layer4);break;
	case 5: tmps="Labor/labor1";
		this->addChild(labor[5]->layer_labor,mine_layer5);break;
	case 6: tmps="Labor/labor1";
		this->addChild(labor[6]->layer_labor,mine_layer6);break;
	}
	labor[number]->setnumber(number+1);//번호부여
	labor[number]->setTexture(tmps);//이미지 저장
	labor[number]->Add();//추가
}
//노동자 추가

void Mining::labor_texture(float dt){
	if(labor_on[0]){
		labor[0]->texture_update(dt);
		m_user->add_labor(labor[0]->mines);
		labor[0]->mines=0;
	}
	if(labor_on[1]){
		labor[1]->texture_update(dt);
		m_user->add_labor(labor[1]->mines);
		labor[1]->mines=0;
	}
	
	if(labor_on[2]){
		labor[2]->texture_update(dt);
		m_user->add_labor(labor[2]->mines);
		labor[2]->mines=0;
	}
	if(labor_on[3]){
		labor[3]->texture_update(dt);
		m_user->add_labor(labor[3]->mines);
		labor[3]->mines=0;
	}
	if(labor_on[4]){
		labor[4]->texture_update(dt);
		m_user->add_labor(labor[4]->mines);
		labor[4]->mines=0;
	}
	if(labor_on[5]){
		labor[5]->texture_update(dt);
		m_user->add_labor(labor[5]->mines);
		labor[5]->mines=0;
	}
	if(labor_on[6]){
		labor[6]->texture_update(dt);
		m_user->add_labor(labor[6]->mines);
		labor[6]->mines=0;
	}
} 
//일시키기 위해서 스프라이트 바꾸기

void Mining::user_time(float dt){

	minenumber->setString(StringUtils::format("Mine : %d",m_user->mines));
}
//계속 마인 넘버 바꾸기

bool Mining::onTouchBegan(Touch* touch, Event* unused_event){
	//터치가 시작되었을 때
	if(Rect(0,0,320,240).containsPoint(touch->getLocation())){
		B_manager->onTouchBegan(touch,Mine_scroll,DEVELOPER);
	}
	if(Rect(0,240,320,480).containsPoint(touch->getLocation())){
			m_user->Touched(touch);
	}
	return true;
}
void Mining::onTouchEnded(Touch* touch, Event* unused_event){
	if(Rect(0,0,320,240).containsPoint(touch->getLocation()))
	{
		Rect r[5];
		r[4]=B_manager->u_Button->Lucky->getBoundingBox();
		r[3]=B_manager->u_Button->Power->getBoundingBox();
		r[2]=B_manager->u_Button->Upgrade->getBoundingBox();
		r[1]=B_manager->u_Button->People->getBoundingBox();
		r[0]=B_manager->u_Button->Power1->getBoundingBox();

		
		Rect scroll_rect[5];
		for(int i=0;i<5;i++)
		scroll_rect[i]=Rect(r[i].origin.x+Mine_scroll->getContentOffset().x,
			r[i].origin.y+Mine_scroll->getContentOffset().y,
			r[i].size.width,r[i].size.height);

		if(scroll_rect[4].containsPoint(touch->getLocation()))
		{
			Up_Lucky();
			Lv[4]->setString(StringUtils::format("Lv%d",uch->n_lucky));

		}else if(scroll_rect[3].containsPoint(touch->getLocation()))
		{
			Up_Power(0);
			Lv[3]->setString(StringUtils::format("Lv%d",uch->n_power));

		}else  if(scroll_rect[2].containsPoint(touch->getLocation()))
		{
			Up_Upgrade();
			Lv[2]->setString(StringUtils::format("Lv%d",uch->n_upgrade));
					

		}else if(scroll_rect[1].containsPoint(touch->getLocation()))
		{
			Up_People();
			Lv[1]->setString(StringUtils::format("Lv%d",uch->n_people));

		}else if(scroll_rect[0].containsPoint(touch->getLocation())&&labor_on[0])
		{
			Up_Power(1);
			Lv[0]->setString(StringUtils::format("Lv%d",n_power));
		
		}
		B_manager->u_Button->Power1->setOpacity(255);
		B_manager->u_Button->Power->setOpacity(255);
		B_manager->u_Button->People->setOpacity(255);
		B_manager->u_Button->Upgrade->setOpacity(255);
		B_manager->u_Button->Lucky->setOpacity(255);
		if (DEVELOPER)
		{
			r[4]=B_manager->Develop_Setting->Lucky->getBoundingBox();
			r[3]=B_manager->Develop_Setting->Power->getBoundingBox();
			r[2]=B_manager->Develop_Setting->Upgrade->getBoundingBox();
			r[1]=B_manager->Develop_Setting->People->getBoundingBox();
			r[0]=B_manager->Develop_Setting->Power1->getBoundingBox();

			for(int i=0;i<5;i++)
			scroll_rect[i]=Rect(r[i].origin.x+Mine_scroll->getContentOffset().x,
				r[i].origin.y+Mine_scroll->getContentOffset().y,
				r[i].size.width,r[i].size.height);

			if(scroll_rect[4].containsPoint(touch->getLocation()))
			{
				//Up_Lucky();
				Lv[4]->setString(StringUtils::format("Lv%d",uch->n_lucky));

			}else if(scroll_rect[3].containsPoint(touch->getLocation()))
			{
				//Up_Power(0);
				Lv[3]->setString(StringUtils::format("Lv%d",uch->n_power));

			}else  if(scroll_rect[2].containsPoint(touch->getLocation()))
			{
				//Up_Upgrade();
				Lv[2]->setString(StringUtils::format("Lv%d",uch->n_upgrade));
					

			}else if(scroll_rect[1].containsPoint(touch->getLocation()))
			{
				//Up_People();
				Lv[1]->setString(StringUtils::format("Lv%d",uch->n_people));

			}else if(scroll_rect[0].containsPoint(touch->getLocation())&&labor_on[0])
			{
				//Up_Power(1);
				Lv[0]->setString(StringUtils::format("Lv%d",n_power));
		
			}
			B_manager->Develop_Setting->Power1->setOpacity(255);
			B_manager->Develop_Setting->Power->setOpacity(255);
			B_manager->Develop_Setting->People->setOpacity(255);
			B_manager->Develop_Setting->Upgrade->setOpacity(255);
			B_manager->Develop_Setting->Lucky->setOpacity(255);
		}
	}
}

void Mining::Touch_book(Ref* pSender){

	//도감으로 가기
	CCLOG("book");
	Savingmanager->Saving();
}
void Mining::Touch_Setup(Ref* pSender){

	//setup보이기
	CCLOG("setup");
	Savingmanager->Saving();
}
void Mining::Touch_Building(Ref* pSender){
	Director::getInstance()->replaceScene(BuildingScene::createScene());
	Savingmanager->Saving();
}

void Mining::Up_Lucky(){
	if(uch->n_lucky<MAX_LUCKYNUM){
		uch->n_lucky++;
		m_user->setlucky(uch->n_lucky*5);
	}
}
void Mining::Up_Power(int a){
	if(a==1){
		if(n_power<MAX_POWERNUM){ 
			n_power++;
			for(int i=0;i<7;i++)
			labor[i]->setPower(n_power*5);
			Lv[0]->setString(StringUtils::format("Lv%d",n_power));
		}
	}else{
		if(uch->n_power<MAX_POWERNUM){ 
			uch->n_power++;
			m_user->setPower(uch->n_power*5);
			Lv[3]->setString(StringUtils::format("Lv%d",uch->n_power));
		}
	}
}
void Mining::Up_Upgrade(){
	if(uch->n_upgrade<MAX_UPGRADENUM){
		uch->n_upgrade++;
		m_user->mine_upgrade=uch->n_upgrade;
		for(int i=0;i<uch->n_people-1;i++) labor[i]->mine_upgrade=uch->n_upgrade;
	}
}
void Mining::Up_People(){
	if(uch->n_people<=MAX_PEOPLENUM){
		add_labor(uch->n_people-1);
		labor[uch->n_people-1]->mine_upgrade=uch->n_upgrade;
		labor_on[uch->n_people-1]=true;
		uch->n_people++;
	}
	//레이어 만들기
}

void Mining::Label_create(){
	int i;

	for( i=0;i<5;i++){
		Lv[i]=Label::createWithTTF("Lv1",FONT,15);
		Lv[i]->setPosition(100,45+i*65);
		Mine->addChild(Lv[i],2);
	}
	Lv[4]->setString(StringUtils::format("Lv%d",uch->n_lucky));
	Lv[3]->setString(StringUtils::format("Lv%d",uch->n_power));
	Lv[2]->setString(StringUtils::format("Lv%d",uch->n_upgrade));
	Lv[1]->setString(StringUtils::format("Lv%d",uch->n_people));
	Lv[0]->setString(StringUtils::format("Lv%d",n_power));	

	///////////////////////////////////////////////////////////////
 	minenumber=Label::createWithTTF("Mine : 0","fonts/arial.ttf",20);
	minenumber->setString(StringUtils::format("Mine : %d",Savingmanager->GetData("a_mines")));

	minenumber->setPosition(10,470);
	minenumber->setAnchorPoint(Point(0,1));
	
	this->addChild(minenumber,ui);
}
void Mining::Menu_create(){
	auto Book=Sprite::create("UI/Book.png");
	auto t_Book=Sprite::create("UI/Book.png");
	auto Setup=Sprite::create("UI/Setup.png");
	auto t_Setup=Sprite::create("UI/Setup.png");
	auto Building=Sprite::create("UI/Building.png");
	auto t_Building=Sprite::create("UI/Building.png");
	Building->setAnchorPoint(Point(0,0));
	t_Building->setAnchorPoint(Point(0,0));
	t_Book->setOpacity(150);
	t_Setup->setOpacity(150);
	t_Building->setOpacity(150);
	auto _ui1=MenuItemSprite::create(Book,t_Book,Book,CC_CALLBACK_1(Mining::Touch_book,this));
	auto _ui2=MenuItemSprite::create(Setup,t_Setup,Setup,CC_CALLBACK_1(Mining::Touch_Setup,this));
	auto _ui3=MenuItemSprite::create(Building,t_Building,Building,CC_CALLBACK_1(Mining::Touch_Building,this));
	
	auto UI=Menu::create(_ui3,_ui1,_ui2,NULL);
	UI->alignItemsHorizontallyWithPadding(5);
	//UI->setAnchorPoint(Point(1,1));
	UI->setPosition(243,458);

	this->addChild(UI,ui);
}
void Mining::Background_create(){
	Background=Sprite::create("Background/Mining_Back.png");
	Background->setScaleY(0.875f);
	Background->setAnchorPoint(Point(0,0));
	Background->setPosition(0,235);
	this->addChild(Background,mine_background);
}
void Mining::Scroll_create(){
	auto tmp_layer = LayerColor::create(Color4B::WHITE);
	tmp_layer->setContentSize(Size(320, 240));
	tmp_layer->setAnchorPoint(Point(0,0));
	this->addChild(tmp_layer,tmp_layers);


	Mine = LayerColor::create(Color4B::WHITE);
		
	Mine->setContentSize(Size(320,330));

	//스크롤 뷰                       스크롤뷰(layer)가 보이는 영역
	Mine_scroll = ScrollView::create(Size(320, 240), Mine);
    Mine_scroll->setDirection(ScrollView::Direction::VERTICAL);
    Mine_scroll->setBounceable(true);
    this->addChild(Mine_scroll,scroll);
	Mine_scroll->setContentOffset(Vec2(0.0f,-90.0f));
}
