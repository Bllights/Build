#include "Defaultmanager.h"

void Defaultmanager::Saving(){
	int i;
	for(i=0;i<coin_saver;i++){

		getInstance()->setIntegerForKey(savingarr[i].c_str(),*numarr[i]);

	}
}
//자동 세이빙

Defaultmanager::Defaultmanager(){
	
	coin_saver=0;

}
//생성자

void Defaultmanager::AddSaver(std::string saver,int* num){

	savingarr[coin_saver]=saver;
	numarr[coin_saver]=num;

	coin_saver++;

}
//자동 세이브할것 추가

int Defaultmanager::GetData(std::string dataname){

	return getInstance()->getIntegerForKey(dataname.c_str());

}
//xml에서 값 받아오기