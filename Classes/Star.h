#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Star : public Sprite {
private:
	Color3B color;
	Vec2 pos;

public:
	static const int DIRECTION_DOWN = 100;
	static const int DIRECTION_LEFT = 101;

	static Star* createWithArgs(Color3B color, Size size, Vec2 pos);

	virtual bool init();

	bool initWithArgs(Color3B color, Size size, Vec2 pos);

	Color3B getColor();
	Point getPos();
	void setPos(Vec2 position);
	void move(int direction);
};
