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

class FogSprite : public Sprite
{
public:
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override
	{
		int oldEquation;
		glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &oldEquation);
		//glBlendEquation(GL_FUNC_SUBTRACT);
		Sprite::draw(renderer, transform, flags);
		glBlendEquation(oldEquation);
	}

	static FogSprite* createWithSpriteFrame(SpriteFrame *spriteFrame)
	{
		FogSprite *sprite = new (std::nothrow) FogSprite();
		if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	static FogSprite* createWithSpriteFrameName(const std::string& spriteFrameName)
	{
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
		char msg[256] = { 0 };
		sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
		CCASSERT(frame != nullptr, msg);
#endif

		return createWithSpriteFrame(frame);
	}
};

int d = 0;
int s = 8;
FogSprite* sprite;
FogSprite* sprite2;
GLenum opts[] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA };

void create_clipping()
{
	auto levelSize = theLevelScene->getContentSize();
	auto w = min(levelSize.width,  MAX_LVL_WIDTH);
	auto h = min(levelSize.height, MAX_LVL_HEIGHT);

	theFog = DrawNode::create();
	theFog->drawSolidRect(Vec2(0, 0), Vec2(w, h), Color4F(0.0f, 0.0f, 0.0f, 0.0f));

	clip = ClippingNode::create(theFog);
	clip->setContentSize(Size(w, h));
	clip->setPosition(
		(levelSize.width - w) / 2,
		(levelSize.height - h) / 2
		);

	sprite = FogSprite::createWithSpriteFrameName("fog");
	sprite->setPosition(150, 150);

	sprite2 = FogSprite::createWithSpriteFrameName("fog");
	sprite2->setPosition(250, 50);

	auto ll = LayerColor::create(Color4B(0, 0, 0, 128), theMap->getContentSize().width, theMap->getContentSize().height);
	
	
	auto eventListener = EventListenerKeyboard::create();

	sprite->setBlendFunc({ opts[d], opts[s] });
	sprite2->setBlendFunc({ opts[d], opts[s] });

	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			d--;
			if (d < 0)
			{
				d = 13;
			}
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			d++;
			if (d > 13)
			{
				d = 0;
			}
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			s--;
			if (s < 0)
			{
				s = 13;
			}
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			s++;
			if (s > 13)
			{
				s = 0;
			}
			break;
		}

		sprite->setBlendFunc({ opts[d], opts[s] });
		sprite2->setBlendFunc({ opts[d], opts[s] });
	};

	theMap->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, sprite);

	clip->addChild(sprite);
	clip->addChild(sprite2);
	theMap->addChild(ll, 999);
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