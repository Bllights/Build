#pragma once

#include "cocos2d.h"

USING_NS_CC;
//==savingmanager
class Defaultmanager : UserDefault{
private:

	std::string savingarr[100];
	int* numarr[100];

	int coin_saver;

public:
	
	Defaultmanager();

	void Saving();

	void AddSaver(std::string saver,int* num);

	int GetData(std::string dataname);


};