#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Star : public Sprite {
private:
	Color3B color;
	Point pos;

public:
	static Star* createWithArgs(Color3B color, Size size, Point pos);

	virtual bool init();

	bool initWithArgs(Color3B color, Size size, Point pos);

	Color3B getColor();
	Point getPosition();
	void setPosition(Point position);
};
