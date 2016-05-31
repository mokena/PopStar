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
		getAllSameStars(star);

		if (sameStars->size() > 1) {
			for (auto it = sameStars->begin(); it != sameStars->end(); it++) {
				//(*it)->setColor(Color3B::GRAY);
				dismissStar(*it);
			}
		}
		
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
	Vector<Star*>* roundStars = new Vector<Star*>();
	
	int cx = center->getPos().x;
	int cy = center->getPos().y;
	
	//upper
	if (cy < NUM_OF_STAR_ROW - 1 && stars[cx][cy + 1] && stars[cx][cy + 1]->getColor() == center->getColor()) {
		if (!sameStars->contains(stars[cx][cy + 1])) { 
			sameStars->pushBack(stars[cx][cy + 1]); 
			roundStars->pushBack(stars[cx][cy + 1]);
		}
	}

	//lower
	if (cy > 0 && stars[cx][cy - 1] && stars[cx][cy - 1]->getColor() == center->getColor()) {
		if (!sameStars->contains(stars[cx][cy - 1])) { 
			sameStars->pushBack(stars[cx][cy - 1]); 
			roundStars->pushBack(stars[cx][cy - 1]);
		}
	}

	//right
	if (cx < NUM_OF_STAR_ROW - 1 && stars[cx + 1][cy] && stars[cx + 1][cy]->getColor() == center->getColor()) {
		if (!sameStars->contains(stars[cx + 1][cy])) { 
			sameStars->pushBack(stars[cx + 1][cy]);
			roundStars->pushBack(stars[cx + 1][cy]);
		}
	}

	//left
	if (cx > 0 && stars[cx - 1][cy] && stars[cx - 1][cy]->getColor() == center->getColor()) {
		if (!sameStars->contains(stars[cx - 1][cy])) { 
			sameStars->pushBack(stars[cx - 1][cy]);
			roundStars->pushBack(stars[cx - 1][cy]);
		}
	}

	return roundStars;
}

/*
	getAllSameStars: get all of the stars in the same color with the giving center star, 
	push them into sameStars, including the giving center star
*/
void HelloWorld::getAllSameStars(Star* center) {
	sameStars = new Vector<Star*>();
	Vector<Star*>* first = new Vector<Star*>();
	first->pushBack(center);
	sameStars->pushBack(center);
	getSameStarsIterator(first);
}

/*
	getSameStarsIterator: iteratively get the stars in the same color by the giving vector of stars
*/
void HelloWorld::getSameStarsIterator(Vector<Star*>* input) {
	if (!input || input->size() == 0) {
		return;
	}

	for (auto it = input->begin(); it != input->end(); it++) {
		Vector<Star*>* round = getRoundSameStars(*it);
		getSameStarsIterator(round);
	}
}

/*
	dismissStar: dismiss the giving star, upper stars go down, right stars go left
*/
void HelloWorld::dismissStar(Star* star) {
	Vec2 pos = star->getPos();

	stars[(int)pos.x][(int)pos.y] = nullptr;	
	
	for (int i = (int)pos.y + 1; i < NUM_OF_STAR_ROW; i++) {
		if (stars[(int)pos.x][i]) {
			stars[(int)pos.x][i]->move(Star::DIRECTION_DOWN);
			stars[(int)pos.x][i - 1] = stars[(int)pos.x][i];
			stars[(int)pos.x][i] = nullptr;
		}
	}

	if (stars[(int)pos.x][0] == nullptr) {
		CCLOG("pos [%d][0] is null", (int)pos.x);
		for (int i = (int)pos.x + 1; i < NUM_OF_STAR_ROW; i++) {
			for (int j = 0; j < NUM_OF_STAR_ROW; j++) {
				if (stars[i][j]) {
					stars[i][j]->move(Star::DIRECTION_LEFT);
					stars[i - 1][j] = stars[i][j];
					stars[i][j] = nullptr;
				}
			}
		}
	}
	else {
		CCLOG("pos [%d][0] is not null", (int)pos.x);
	}
		
	star->setVisible(false);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
