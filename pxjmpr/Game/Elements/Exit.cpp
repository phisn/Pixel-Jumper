#include "Exit.h"
#include <Framework/Direct2D.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>

Exit_Object::Exit_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		exitResource,
		position,
		Collision::Level::Exit)
{
}

bool Exit_Object::onCollision(
	PlayerContainer player,
	Collision::Side side)
{
	return true;
}

Exit_Resource* Exit_Object::exitResource;
void Exit_Object::initialize()
{
	Direct2D::registerResource(exitResource = new Exit_Resource());
	ElementFactory::registerRectangleObject(
		EXIT_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Exit_Object(position);
	});
}
