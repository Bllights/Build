#pragma once

#include"cocos2d.h"

USING_NS_CC;

//메인 노동자 
class TextureFactory{
public:

	static Texture2D* Create(std::string filepath);


};

