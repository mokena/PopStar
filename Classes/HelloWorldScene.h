#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Star.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	static const int NUM_OF_STAR_ROW = 10;
	static const int COLOR_NUM = 6;
	static const float STAR_GAP;

	Star* stars[10][10];

	void addStars();
	Star* getTouchedStar(Point p);
};

#endif // __HELLOWORLD_SCENE_H__
