#include "Defaultmanager.h"

void Defaultmanager::Saving(){
	int i;
	for(i=0;i<coin_saver;i++){

		getInstance()->setIntegerForKey(savingarr[i].c_str(),*numarr[i]);

	}
}
//�ڵ� ���̺�

Defaultmanager::Defaultmanager(){
	
	coin_saver=0;

}
//������

void Defaultmanager::AddSaver(std::string saver,int* num){

	savingarr[coin_saver]=saver;
	numarr[coin_saver]=num;

	coin_saver++;

}
//�ڵ� ���̺��Ұ� �߰�

int Defaultmanager::GetData(std::string dataname){

	return getInstance()->getIntegerForKey(dataname.c_str());

}
//xml���� �� �޾ƿ���