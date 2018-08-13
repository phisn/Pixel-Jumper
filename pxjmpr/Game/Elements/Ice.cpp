#include "Ice.h"
#include <Framework/Direct2D.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>
#include <Game/Player.h>

Ice_Object::Ice_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		IceResource,
		position,
		Collision::Level::Ice
	)
{
}

bool Ice_Object::onCollision(
	PlayerContainer player,
	Collision::Side side)
{
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

	return false;
}

Ice_Resource* Ice_Object::IceResource;
void Ice_Object::initialize()
{
	Direct2D::registerResource(IceResource = new Ice_Resource());
	ElementFactory::registerRectangleObject(
		ICE_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Ice_Object(position);
	});
}
