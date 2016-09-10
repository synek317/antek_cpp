#include "PCH.h"
#include "map.h"
#include "globals.h"
#include "consts.h"
#include "level_scene.h"
#include "drag_drop.h"
#include "GL/glew.h"
usings

TMXTiledMap* theMap;
DrawNode* theFog;

static ClippingNode* clip;

void cleanup()
{
	theLevelScene->removeChild(clip);
}

void create_clipping()
{
	auto levelSize = theLevelScene->getContentSize();
	auto w = min(levelSize.width,  MAX_LVL_WIDTH);
	auto h = min(levelSize.height, MAX_LVL_HEIGHT);

	theFog = DrawNode::create();
	theFog->drawSolidRect(Vec2(0, 0), Vec2(w/2, h/2), Color4F(0.2f, 0.2f, 0.2f, 0.2f));

	clip = ClippingNode::create(theFog);
	clip->setContentSize(Size(w, h));
	clip->setPosition(
		(levelSize.width - w) / 2,
		(levelSize.height - h) / 2
		);

	//RenderTexture* renderTexture = RenderTexture::create(w, h,
	//	Texture2D::PixelFormat::RGBA8888,
	//	GL_DEPTH24_STENCIL8); // configure for clipping node

	//renderTexture->beginWithClear(0, 0, 0, 0, 1.0f);
	//clip->Node::visit();
	//renderTexture->end();
}

void scroll_map(float dx, float dy)
{
	auto minX = clip->getContentSize().width - theMap->getContentSize().width;
	auto minY = clip->getContentSize().height - theMap->getContentSize().height;

	theMap->setPosition(
		clampf(theMap->getPosition().x + dx, minX, 0),
		clampf(theMap->getPosition().y + dy, minY, 0)
	);
}

void load_map(const string& tmxPath)
{
	if (theMap != nullptr) cleanup();

	auto background = LayerColor::create(LVL_BG_COLOR);

	theMap = TMXTiledMap::create(tmxPath);

	create_clipping();

	clip->addChild(background);
	clip->addChild(theMap);
	theLevelScene->addChild(clip);

	on_drag_drop(clip, &scroll_map);
}