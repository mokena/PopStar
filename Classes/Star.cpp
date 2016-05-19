#include "Star.h"

Star* Star::createWithArgs(Color3B color, Size size, Point pos) {
	Star* star = new Star();
	if (star->init()) {
		star->autorelease();
		star->initWithArgs(color, size, pos);
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
	setTextureRect(Rect(0, 0, size.width, size.height));
	setColor(color);
	setContentSize(size);

	return true;
}

Color3B Star::getColor() {
	return color;
}

Point Star::getPosition() {
	return pos;
}

void Star::setPosition(Point position) {
	pos = position;

}