#include "Boost.h"
#include <Framework/Direct2D.h>
#include <Framework/Timer.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>
#include <Game/Player.h>

Boost_Object::Boost_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		BoostResource,
		position,
		Collision::Level::Boost
	)
{
}

bool Boost_Object::onCollision(
	PlayerContainer player,
	Collision::Side side)
{
	float time = Timer::getMicroTime();
	if (lastTime + triggerRate < time)
	{
		lastTime = time;

		*player.movx *= 1.5f;
		*player.movy *= 1.5f;
	}

	return false;
}

Boost_Resource* Boost_Object::BoostResource;
void Boost_Object::initialize()
{
	Direct2D::registerResource(BoostResource = new Boost_Resource());
	ElementFactory::registerRectangleObject(
		BOOST_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Boost_Object(position);
	});
}
