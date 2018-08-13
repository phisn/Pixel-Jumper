#include "Wall.h"
#include <Framework/Direct2D.h>
#include <Game/Elements/Factory.h>
#include <Game/Map.h>

Wall_Object::Wall_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		wallResource,
		position,
		Collision::Level::Wall)
{
}

#include <iostream>
bool Wall_Object::onCollision(
	PlayerContainer player,
	Collision::Side side)
{
	//D2D1_SIZE_F movement = (const D2D1_SIZE_F) destination;

	switch (side)
	{
	case Collision::Side::Top:
		player.position->height = getPosition().height + 1.f;
		*player.movy = 0.f;

		break;
	case Collision::Side::Left:
		player.position->width = getPosition().width + 1.f;
		*player.movx = 0.f;

		break;
	case Collision::Side::Bottom:
		player.position->height = getPosition().height - 1.f;
		*player.movy = 0.f;

		break;
	case Collision::Side::Right:
		player.position->width = getPosition().width - 1.f;
		*player.movx = 0.f;

		break;
	}

	return true;
}

Wall_Resource* Wall_Object::wallResource;
void Wall_Object::initialize()
{
	Direct2D::registerResource(wallResource = new Wall_Resource());
	ElementFactory::registerRectangleObject(
		WALL_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
		{
			return new Wall_Object(position);
		});
}
