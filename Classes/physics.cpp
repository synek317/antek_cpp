#include "PCH.h"
#include "physics.h"
#include "consts.h"
usings

b2World* theWorld;

static const b2Vec2 gravity(0.0f, -1.0f);
static const int positionIterations = 10;
static const int velocityIterations = 10;

float  px2m(float px)       { return px / PTMRATIO; }
float  m2px(float m)        { return m *  PTMRATIO; }
b2Vec2 px2m(const Vec2& v)   { return b2Vec2(px2m(v.x), px2m(v.y)); }
Vec2   px2m(const b2Vec2& v) { return Vec2(m2px(v.x),   m2px(v.y)); }

void cleanup_physics()
{
	delete theWorld;
}

void init_physics()
{
	if (theWorld != nullptr) cleanup_physics();

	theWorld = new b2World(gravity);
	theWorld->SetAllowSleeping(true);
	theWorld->SetContinuousPhysics(true);
}

void update_physics(float dt)
{
	theWorld->Step(dt, velocityIterations, positionIterations);
	theWorld->ClearForces();
}