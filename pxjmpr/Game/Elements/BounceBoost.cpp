#include "BounceBoost.h"
#include <Framework/Direct2D.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>
#include <Game/Player.h>

BounceBoost_Object::BounceBoost_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		BounceBoostResource,
		position,
		Collision::Level::BounceBoost
	)
{
}

bool BounceBoost_Object::onCollision(
	PlayerContainer player,
	Collision::Side side)
{
	switch (side)
	{
	case Collision::Side::Top:
		*player.movy = -*player.movy * 1.5f;
		player.position->height = getPosition().height + 1.f + (
			(getPosition().height + 1.f) - player.position->height
			);

		break;
	case Collision::Side::Bottom:
		*player.movy = -*player.movy * 1.5f;
		player.position->height = getPosition().height - 1.f - (
			(player.position->height + 1.f) - getPosition().height
			);

		break;
	case Collision::Side::Left:
		*player.movx = -*player.movx * 1.5f;
		player.position->width = getPosition().width + 1.f + (
			(getPosition().width + 1.f) - player.position->width
			);

		break;
	case Collision::Side::Right:
		*player.movx = -*player.movx * 1.5f;
		player.position->width = getPosition().width - 1.f - (
			(player.position->width + 1.f) - getPosition().width
			);

		break;
	}

	return false;
}

BounceBoost_Resource* BounceBoost_Object::BounceBoostResource;
void BounceBoost_Object::initialize()
{
	Direct2D::registerResource(BounceBoostResource = new BounceBoost_Resource());
	ElementFactory::registerRectangleObject(
		BOUNCEBOOST_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new BounceBoost_Object(position);
	});
}
