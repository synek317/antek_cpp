#include "PCH.h"
#include "graphics.h"
#include "globals.h"
#include "consts.h"
usings

AnimationCache* theAnimationCache;

void init_graphics()
{
	theAnimationCache = AnimationCache::getInstance();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/characters.plist");
	theAnimationCache->addAnimationsWithFile("res/character_animations.plist");
}

void draw_graphics()
{
	for (auto body = theWorld->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		if (body->GetUserData())
		{
			Sprite *sprite = (Sprite *)body->GetUserData();
			sprite->setPosition(Point(body->GetPosition().x * PTMRATIO, body->GetPosition().y * PTMRATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
		}
	}
}