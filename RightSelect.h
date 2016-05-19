#pragma once

#include "cocos2d.h"

USING_NS_CC;

class RightLayer : public Layer{
private:

	Sprite* triangle;

	Sprite* main;

	Sprite* planet[5];

public:
	RightLayer();

	bool TouchedTriangle;

	void onTouchBegan(Touch* touch);

	int onTouchEnded(Touch* touch);
	
};