#include "User.h"

User::User(){
#pragma region reset	
	power=5;
	lucky=0;
	money=0;
	mines=0;
#pragma endregion
	
	srand(time(nullptr));

}
User::~User(){

}
void User::add_labor(int number){
	mines+=number;
}

void User::Touched(Touch* touch){
		dig();
}
void User::dig(){
	CCLOG("power : %d",power);
	mines+=power/5;
	if(rand()%100<lucky){
		mines+=rand()%(power/10+1)+1;
		CCLOG("user_lucky");
	}
	mine->setString(StringUtils::format("Mine : %d",mines));
	//광물 파기
	//액션넣어주기
}
void User::reset(){
	power=5;
	lucky=0;
	money=0;
	mines=0;
}
int User::Getmine(){
	return mines;
}
void User::Getminelabel(Label* tmp){
	mine=tmp;
}