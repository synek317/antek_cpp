#include "PCH.h"
#include "body_creator.h"
#include "globals.h"
#include "physics.h"
usings

static b2Body* body;
static b2BodyDef bodyDef;
static b2FixtureDef fixtureDef;
static b2PolygonShape polygonShape;
static b2CircleShape circleShape;
static b2ChainShape chainShape;
static b2Vec2 vertices[32];
static int vertexCount;

b2Body* createBody(Sprite* sprite, b2BodyType type)
{
	bodyDef.~b2BodyDef();
	new (&bodyDef) b2BodyDef();
	
	auto x = sprite->getPosition().x;
	auto y = sprite->getPosition().y;

	bodyDef.position.x = px2m(sprite->getPosition().x);
	bodyDef.position.y = px2m(sprite->getPosition().y);
	bodyDef.type       = type;
	bodyDef.userData   = sprite;

	body = theWorld->CreateBody(&bodyDef);
	
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.4f;
	fixtureDef.restitution = 0.1f;

	return body;
}

b2Body* createRectBody(Sprite* sprite, b2BodyType type)
{
	createBody(sprite, type);
	if (sprite != nullptr)
	{
  		setRectShape(sprite->getContentSize().width, sprite->getContentSize().height);
	}

	return body;
}

void startBuildingPolygonShape()
{
	vertexCount = 0;
}

void addPolygonVertex(float x, float y)
{
	vertices[vertexCount].x = px2m(x);
	vertices[vertexCount].y = px2m(y);
	++vertexCount;
}

void endBuildingPolygonShape()
{
	polygonShape.Set(vertices, vertexCount);
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
}

void endBuildingPolylineShape()
{
	chainShape.CreateChain(vertices, vertexCount);
	fixtureDef.shape = &chainShape;
	body->CreateFixture(&fixtureDef);
}

void setRectShape(float width_px, float height_px)
{
	vertexCount = 4;
	vertices[0].x = 0;
	vertices[0].y = 0;
	vertices[1].x = 0;
	vertices[1].y = px2m(height_px);
	vertices[2].x = px2m(width_px);
	vertices[2].y = px2m(height_px);
	vertices[3].x = px2m(width_px);
	vertices[3].y = 0;

	polygonShape.Set(vertices, vertexCount);
	
	fixtureDef.shape = &polygonShape;
	body->CreateFixture(&fixtureDef);
}

void setCircleShape(float x, float y, float r)
{
	circleShape.m_radius = r;
	circleShape.m_p.Set(x + r, y + r);
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);
}