#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		// Create sprite and add it to the layer
	_ball = CCSprite::create("ball.png" ,CCRectMake(0, 0, 52, 52));
	_ball->setPosition(ccp(100, 300));
	this->addChild(_ball);

	// Create a world
	b2Vec2 gravity = b2Vec2(0.0f, -8.0f);
	_world = new b2World(gravity);


	// Create edges around the entire screen
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//wall definitions
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);


	// Create ball body and shape
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(100 / PTM_RATIO, 300 / PTM_RATIO);
	ballBodyDef.userData = _ball;
	_body = _world->CreateBody(&ballBodyDef);

	b2CircleShape circle;
	circle.m_radius = 26.0 / PTM_RATIO;
	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.8f;
	_body->CreateFixture(&ballShapeDef);

	this->schedule(schedule_selector(HelloWorld::tick));
	//this->schedule(schedule_selector(HelloWorld::kick),5.0f);

	setTouchEnabled(true);
	setAccelerometerEnabled(true);
	return true;
}

void HelloWorld::tick(float dt)
{
	_world->Step(dt, 10, 10);
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			CCSprite *ballData = (CCSprite *)b->GetUserData();
			ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void HelloWorld::kick(float dt){
	b2Vec2 force = b2Vec2(30, 30);
	_body->ApplyLinearImpulse(force, _body->GetPosition());
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{	
	CCLog("Touch began.");
	b2Vec2 force = b2Vec2(-30, 30);
	_body->ApplyLinearImpulse(force, _body->GetPosition());
}


void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
	b2Vec2 gravity(pAccelerationValue->x * 30, pAccelerationValue->y * 30);
	_world->SetGravity(gravity);
	//float distFraction = visibleSize.height* pAccelerationValue->x;
}

HelloWorld::~HelloWorld()
{
	delete _world;
	_body = NULL;
	_world = NULL;
}

