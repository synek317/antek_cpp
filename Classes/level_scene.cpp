#include "PCH.h"
#include "level_scene.h"
#include "B2DebugDrawLayer.h"
#include "physics.h"
#include "graphics.h"
#include "body_creator.h"
#include "consts.h"
#include "globals.h"
#include "map.h"
#include "map_physics.h"

LevelScene* theLevelScene;
B2DebugDrawLayer* debugLayer;

Scene* LevelScene::createScene()
{
    auto scene = Scene::create();
	
	LevelScene::create();

	scene->addChild(theLevelScene);
	
    return scene;
}

bool LevelScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	theLevelScene = this;

	init_physics();
	init_graphics();

	load_map("res/l/0.tmx");
	createMapBodies();

	debugLayer = B2DebugDrawLayer::create(theWorld, PTMRATIO);
	//theMap->addChild(debugLayer, 9999);
	scheduleUpdate();

	auto sprite = Sprite::create();
	sprite->setPosition(100, 350);
	
	sprite->runAction(RepeatForever::create(Animate::create(theAnimationCache->getAnimation("d/build"))));
	createBody(sprite);
	startBuildingPolygonShape();
	addPolygonVertex(-30 / Director::getInstance()->getContentScaleFactor(), 50 / Director::getInstance()->getContentScaleFactor());
	addPolygonVertex(30 / Director::getInstance()->getContentScaleFactor(), 50 / Director::getInstance()->getContentScaleFactor());
	addPolygonVertex(30 / Director::getInstance()->getContentScaleFactor(), -35 / Director::getInstance()->getContentScaleFactor());
	addPolygonVertex(-30 / Director::getInstance()->getContentScaleFactor(), -35 / Director::getInstance()->getContentScaleFactor());
	endBuildingPolygonShape();

	theMap->addChild(sprite);
    return true;
}

void LevelScene::update(float dt)
{
	update_physics(dt);
}

void LevelScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	draw_graphics();
}

