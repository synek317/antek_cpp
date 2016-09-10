#pragma once
#include "PCH.h"

b2Body* createBody(cocos2d::Sprite*, b2BodyType type = b2_dynamicBody);
b2Body* createRectBody(cocos2d::Sprite*, b2BodyType);
void startBuildingPolygonShape();
void addPolygonVertex(float, float);
void endBuildingPolygonShape();
#define startBuildingPolylineShape startBuildingPolygonShape
#define addPolylineVertex		   addPolygonVertex
void endBuildingPolylineShape();
void setRectShape(float, float);
void setCircleShape(float, float, float);