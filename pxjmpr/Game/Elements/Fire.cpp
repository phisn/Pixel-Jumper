#include "Fire.h"
#include <Framework/Direct2D.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>
#include <Game/Player.h>

Fire_Object::Fire_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		fireResource,
		position,
		Collision::Level::Fire
	)
{
}

bool Fire_Object::onCollision(
	PlayerContainer player, 
	Collision::Side side)
{
	Game::getPlayer()->reset();

	return false;
}

Fire_Resource* Fire_Object::fireResource;
void Fire_Object::initialize()
{
	Direct2D::registerResource(fireResource = new Fire_Resource());
	ElementFactory::registerRectangleObject(
		FIRE_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Fire_Object(position);
	});
}
