#include "RightSelect.h"
RightLayer::RightLayer(){

	triangle=Sprite::create("UI/scroll.png");
	triangle->setAnchorPoint(Point(1,0.5));
	triangle->setPosition(0,75);
	
	main=Sprite::create("UI/Right.png");
	main->setAnchorPoint(Point(0,0));
	this->addChild(triangle);
	this->addChild(main);

	TouchedTriangle=false;

}
void RightLayer::onTouchBegan(Touch* touch){
	
	Point a= touch->getLocation();
	if(TouchedTriangle){
		for(int i=0;i<5;i++){
			if(planet[i]->getBoundingBox().containsPoint(a))
				planet[i]->setOpacity(200);
			
		}
	}else{
		if(triangle->getBoundingBox().containsPoint(a))
			triangle->setOpacity(200);
		
	}
}
int RightLayer::onTouchEnded(Touch* touch){
	Point a= touch->getLocation();
	int tmp=-1;
	if(TouchedTriangle){
		
		if(triangle->getBoundingBox().containsPoint(a)){

			triangle->setOpacity(255);
			TouchedTriangle=false;
			//액션
			return tmp;
		}
		for(int i=0;i<5;i++){
			if(planet[i]->getBoundingBox().containsPoint(a))
				tmp=i;
			
			planet[i]->setOpacity(255);
		}

	}else{
		if(triangle->getBoundingBox().containsPoint(a)){

			triangle->setOpacity(255);
			//액션
		}
	}
	return tmp;
}
