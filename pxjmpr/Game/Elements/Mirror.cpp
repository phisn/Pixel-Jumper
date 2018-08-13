#include "Mirror.h"
#include <Framework/Direct2D.h>
#include <Framework/Timer.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>
#include <Game/Player.h>

Mirror_Object::Mirror_Object(
	D2D1_SIZE_F position,
	bool invert)
	:
	Rectangle_Object(
		MirrorResource,
		position,
		Collision::Level::Mirror
	),
	invert(invert)
{
}

bool Mirror_Object::onCollision(
	PlayerContainer player,
	Collision::Side side)
{
	float time = Timer::getMicroTime();
	if (lastTime + triggerRate < time)
	{
		lastTime = time;

		float temp = *player.movx;
		if (invert)
		{
			*player.movx = -*player.movy;
			*player.movy = -temp;
		}
		else
		{
			*player.movx = *player.movy;
			*player.movy = temp;
		}
	}

	return false;
}

Mirror_Resource* Mirror_Object::MirrorResource;
void Mirror_Object::initialize()
{
	Direct2D::registerResource(MirrorResource = new Mirror_Resource());
	ElementFactory::registerRectangleObject(
		MIRROR_RIGHT_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Mirror_Object(position, false);
	});

	ElementFactory::registerRectangleObject(
		MIRROR_LEFT_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Mirror_Object(position, true);
	});
}
