#pragma once
#include "PCH.h"

void init_physics();
void update_physics(float);
float px2m(float);
float m2px(float);
b2Vec2 px2m(const cocos2d::Vec2&);
cocos2d::Vec2 px2m(const b2Vec2&);