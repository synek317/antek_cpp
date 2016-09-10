#include "PCH.h"
#include "globals.h"
#include "map_physics.h"
#include "body_creator.h"
usings

void createMapBodies()
{
	auto tileLayer = theMap->getLayer("tiles");
	auto tileSize = theMap->getTileSize();
	Vec2 pos;

	for (pos.y = 0; pos.y < theMap->getMapSize().height; pos.y++)
	{
		for (pos.x = 0; pos.x < theMap->getMapSize().width; pos.x++)
		{
			auto tile = tileLayer->getTileAt(pos);

			if (tile != nullptr && tile->getResourceType() != 0)
			{
				createRectBody(tile, b2_staticBody);
			}
		}
	}
}