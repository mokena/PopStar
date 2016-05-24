#include "Star.h"

Star* Star::createWithArgs(Color3B color, Size size, Point pos) {
	Star* star = new Star();
	if (star&&star->init()) {
		star->initWithArgs(color, size, pos);

		star->autorelease();
		return star;
	}

	CC_SAFE_DELETE(star);
	return NULL;
}

bool Star::init() {
	return Sprite::init();
}

bool Star::initWithArgs(Color3B color, Size size, Point pos) {
	this->color = color;
	this->pos = pos;

	//draw rect
	setContentSize(size);
	setTextureRect(Rect(0, 0, size.width, size.height));
	setColor(color);
	setAnchorPoint(Vec2::ZERO);

	return true;
}

Color3B Star::getColor() {
	return color;
}

//Point Star::getPosition() {
//	return pos;
//}
//
//void Star::setPosition(Point position) {
//	pos = position;
//	setPosition(Vec2(pos.x, pos.y));
//}