#include "Star.h"

Star* Star::createWithArgs(Color3B color, Size size, Vec2 pos) {
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

bool Star::initWithArgs(Color3B color, Size size, Vec2 pos) {
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

Vec2 Star::getPos() {
	return pos;
}

void Star::setPos(Vec2 position) {
	pos = position;
	//setPosition(Vec2(pos.x, pos.y));
}