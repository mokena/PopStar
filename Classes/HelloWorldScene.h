#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Star.h"

class HelloWorld : public cocos2d::Layer
{
public:
	static const float STAR_GAP;

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	static const int NUM_OF_STAR_ROW = 10;
	static const int COLOR_NUM = 6;

	Star* stars[10][10];
	Vector<Star*>* sameStars;
	Vector<Star*>* getRoundSameStars(Star* center);

	void addStars();
	Star* getTouchedStar(Vec2 p);
	void getAllSameStars(Star* center);
	void getSameStarsIterator(Vector<Star*>* input);
	void dismissStar(Star* star);
	bool isGameOver();
	void cleanStars();
};

#endif // __HELLOWORLD_SCENE_H__
