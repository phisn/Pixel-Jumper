#include "Bounce.h"
#include <Framework/Direct2D.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>
#include <Game/Player.h>

Bounce_Object::Bounce_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		BounceResource,
		position,
		Collision::Level::Bounce
	)
{
}

bool Bounce_Object::onCollision(
	PlayerContainer player,
	Collision::Side side)
{
	switch (side)
	{
	case Collision::Side::Top:
		*player.movy = -*player.movy;
		player.position->height = getPosition().height + 1.f + (
			(getPosition().height + 1.f) - player.position->height
		);

		break;
	case Collision::Side::Bottom:
		*player.movy = -*player.movy;
		player.position->height = getPosition().height - 1.f - (
			(player.position->height + 1.f) - getPosition().height
		);

		break;
	case Collision::Side::Left:
		*player.movx = -*player.movx;
		player.position->width = getPosition().width + 1.f + (
			(getPosition().width + 1.f) - player.position->width
			);

		break;
	case Collision::Side::Right:
		*player.movx = -*player.movx;
		player.position->width = getPosition().width - 1.f - (
			(player.position->width + 1.f) - getPosition().width
		);

		break;
	}

	return false;
}

Bounce_Resource* Bounce_Object::BounceResource;
void Bounce_Object::initialize()
{
	Direct2D::registerResource(BounceResource = new Bounce_Resource());
	ElementFactory::registerRectangleObject(
		BOUNCE_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Bounce_Object(position);
	});
}
