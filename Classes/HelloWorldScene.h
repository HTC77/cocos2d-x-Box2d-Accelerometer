#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define PTM_RATIO 32.0

#include "cocos2d.h"
#include <Box2D\Box2D.h>
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	CCSize visibleSize;
	b2World* _world;
	b2Body* _body;
	CCSprite* _ball;

	void tick(float dt);
	~HelloWorld();

	void kick(float dt);
	void ccTouchesBegan(CCSet* pTouches, CCEvent* event);

	void didAccelerate(CCAcceleration* pAccelerationValue);
};

#endif // __HELLOWORLD_SCENE_H__
