#include "HelloWorldScene.h"

USING_NS_CC;

const float HelloWorld::STAR_GAP = 4.0f;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	srand(time(NULL));
	auto colorLayer = LayerColor::create(Color4B(188, 143,143, 255));
	addChild(colorLayer);
    
	addStars();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* t, Event* e) {
		Star* star = getTouchedStar(t->getLocation());
		getRoundSameStars(star);
		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

/*
	addStars: create star matrix
*/
void HelloWorld::addStars() {
	Size size = Director::getInstance()->getVisibleSize();

	int len = size.width / NUM_OF_STAR_ROW - STAR_GAP;

	Color3B colors[COLOR_NUM] = {Color3B::YELLOW, Color3B::BLUE, Color3B::GREEN, Color3B::RED, Color3B::MAGENTA, Color3B::ORANGE};

	for (int i = 0; i < NUM_OF_STAR_ROW; i++) {
		for (int j = 0; j < NUM_OF_STAR_ROW; j++) {
			int cn = rand() % COLOR_NUM;
			Point pos = Point(i*(len + STAR_GAP) + STAR_GAP/2, j*(len + STAR_GAP) + STAR_GAP/2);
			Star* star = Star::createWithArgs(colors[cn], Size(len, len), Vec2(i, j));
			addChild(star);
			star->setPosition(Vec2(pos.x, pos.y));
			stars[i][j] = star;
		}
	}
}

/*
	getTouchedStar: get the touched star by touch point
*/
Star* HelloWorld::getTouchedStar(Vec2 p) {
	Size size = Director::getInstance()->getVisibleSize();
	int len = size.width / NUM_OF_STAR_ROW;
	int row = p.x / len;
	int col = p.y / len;
	CCLOG("touched %d, %d", row, col);
	return stars[row][col];
}

/*
	getRoundSameStars: get the same star with the center around the center.
*/
Vector<Star*>* HelloWorld::getRoundSameStars(Star* center) {
	int cx = center->getPos().x;
	int cy = center->getPos().y;
	CCLOG("get round of  %d, %d", cx, cy);
	Vector<Star*>* sameStars = new Vector<Star*>();
	sameStars->pushBack(center);
	
	//get upper stars in the same color with center star
	for (int i = cy+1; i < NUM_OF_STAR_ROW; i++) {
		if (stars[cx][i]->getColor() == center->getColor()) {
			stars[cx][i]->setColor(Color3B::GRAY);
			sameStars->pushBack(stars[cx][i]);
		}
		else { break; }
	}

	//get lower stars in the same color with center star
	for (int i = cy - 1; i >= 0; i--) {
		if (stars[cx][i]->getColor() == center->getColor()) {
			stars[cx][i]->setColor(Color3B::GRAY);
			sameStars->pushBack(stars[cx][i]);
		}
		else { break; }
	}

	//get right stars in the same color with center star
	for (int i = cx + 1; i < NUM_OF_STAR_ROW; i++) {
		if (stars[i][cy]->getColor() == center->getColor()) {
			stars[i][cy]->setColor(Color3B::GRAY);
			sameStars->pushBack(stars[i][cy]);
		}
		else { break; }
	}

	//get left stars in the same color with center star
	for (int i = cx - 1; i >= 0; i--) {
		if (stars[i][cy]->getColor() == center->getColor()) {
			stars[i][cy]->setColor(Color3B::GRAY);
			sameStars->pushBack(stars[i][cy]);
		}
		else { break; }
	}
	return sameStars;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
