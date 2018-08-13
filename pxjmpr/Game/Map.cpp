#include "Map.h"

#include <Framework/Direct2D.h>

#include <Game/Elements/Border.h>
#include <Game/Elements/Boost.h>
#include <Game/Elements/Bounce.h>
#include <Game/Elements/BounceBoost.h>
#include <Game/Elements/Entry.h>
#include <Game/Elements/Exit.h>
#include <Game/Elements/Fire.h>
#include <Game/Elements/Ice.h>
#include <Game/Elements/Mirror.h>
#include <Game/Elements/Wall.h>

#include <Game/Game.h>

namespace
{
	Level* level;

	float
		tile,
		vertBorder,
		horzBorder;
	void doLayout()
	{
		horzBorder = 0.f;
		vertBorder = 0.f;

		D2D1_SIZE_F windowSize = Direct2D::getHwndRenderTarget()->GetSize();
		float winWHFactor = windowSize.width / windowSize.height,
			mapWHFactor = (float)level->getSize().width / (float)level->getSize().height;

		if (winWHFactor > mapWHFactor)
		{
			horzBorder = windowSize.width - windowSize.height *
				mapWHFactor;
		}
		else if (winWHFactor < mapWHFactor)
		{
			vertBorder = windowSize.height - windowSize.width *
				((float)level->getSize().height / (float)level->getSize().width);
		}

		tile = (windowSize.height - vertBorder) / level->getSize().height;
	}
}

namespace Map
{
	bool initialize()
	{
		Border_Object::initialize();
		Wall_Object::initialize();
		Entry_Object::initialize();
		Exit_Object::initialize();
		Fire_Object::initialize();
		Bounce_Object::initialize();
		Boost_Object::initialize();
		BounceBoost_Object::initialize();
		Mirror_Object::initialize();
		Ice_Object::initialize();

		return true;
	}

	bool loadLevel(Level* level)
	{
		::level = level;

		Direct2D::removeAllObjects();
		doLayout();
//		Direct2D::createCharacterFormat(tile);

		Direct2D::registerD2Object(new Border_Object(
			horzBorder / 2.f,
			vertBorder / 2.f));
		for (Rectangle_Object* object : level->getRectangleObjects())
		{
			object->reloadRect();

			Direct2D::registerD2Object(object);
		}

		Game::resetExternalObjects();
		Direct2D::recreateResources();

		return true;
	}

	D2D1_SIZE_F getSize()
	{
		return ::level->getSize();
	}

	D2D1_SIZE_F getEntry()
	{
		return ::level->getEntry();
	}

	D2D1_RECT_F positionToRect(
		D2D1_SIZE_F position)
	{
		return D2D1::RectF(
			position.width * tile + horzBorder / 2,
			position.height * tile + vertBorder / 2,
			(position.width + 1) * tile + horzBorder / 2 + 1,
			(position.height + 1) * tile + vertBorder / 2 + 1);
	}

#define COLLISION_STEPS 4
	Collision checkCollision(
		PlayerContainer player)
	{
		Collision collision = {};

		*player.movx /= (4.f * COLLISION_STEPS);
		*player.movy /= (4.f * COLLISION_STEPS);

		for (int i = 0; i < COLLISION_STEPS; ++i)
		{
			player.position->width += *player.movx;
			player.position->height += *player.movy;

			for (Rectangle_Object* object : ::level->getRectangleObjects())
			{
				object->checkCollisionEdge(
					player,
					&collision);
			}

			for (Rectangle_Object* object : ::level->getRectangleObjects())
			{
				object->checkCollisionCorner(
					player,
					&collision);
			}
		}

		*player.movx *= (4.f * COLLISION_STEPS);
		*player.movy *= (4.f * COLLISION_STEPS);

		return collision;
	}

	bool falling(
		const D2D1_SIZE_F position)
	{
		for (Rectangle_Object* object : ::level->getRectangleObjects())
			if (object->getPosition().height == position.height + 1.f &&
				object->checkFallingCornerHorizontal(position))
			{
				return false;
			}

		return true;
	}
}
