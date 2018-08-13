#include "Player.h"
#include <Framework/Direct2D.h>
#include <Framework/Input.h>
#include <Game/Elements/Rectangle.h>
#include <Game/Game.h>
#include <Game/Map.h>

bool Player::initialize()
{
	Direct2D::registerResource(&resource);

	return true;
}

void Player::registerObject()
{
	Direct2D::registerD2Object(this);
}

void Player::reset()
{
	position = Map::getEntry();

	movx = 0.f, movy = 0.f;
	ground = false;
}

void Player::update()
{
	handleInput();
	
	/*D2D1_SIZE_F destination = D2D1::SizeF(
		position.width + movx,
		position.height + movy);*/
	Collision collision = Map::checkCollision(
		PlayerContainer(
			movx,
			movy,
			position));

	if (collision.level == Collision::Level::Exit)
	{
		Game::onLevelFinished();
		return;
	}

	if (collision.isSolid() && ENUM_HAS_VALUE(collision.side, Collision::Side::Bottom))
	{
		ground = true;
	}

	if (ground)
	{
		movx *= 0.975f;

		if (abs(movx) < 0.02f)
		{
			movx = 0.f;
		}
		else
		{
			movx +=
				movx > 0 ?
				-0.02f :
				movx < 0 ?
				0.02f :
				0.f;
		}

		ground = !Map::falling(
			position);
	}
	else
	{
		movy += 0.02;
	}
}

void Player::draw()
{
	Direct2D::getHwndRenderTarget()->FillRectangle(
		Map::positionToRect(position),
		resource.solidColorBrush.get());
}

void Player::handleInput()
{
	Input::Key key = Input::getPressedKeys();

	if (key != Input::Key::None)
	{
		int a;
	}

	if (ENUM_HAS_VALUE(key, Input::Key::Left))
	{
		if (movx > -1.f)
		{
			if (movx > 0)
			{
				movx *= 0.95f;
			}
			
			movx -= ground ? 0.04f : 0.01f;

			if (movx < -1.f)
			{
				movx = -1.f;
			}
		}
	}

	if (ENUM_HAS_VALUE(key, Input::Key::Right))
	{
		if (movx < 1.f)
		{
			if (movx < 0)
			{
				movx *= 0.95f;
			}

			movx += ground ? 0.04f : 0.01f;

			if (movx > 1.f)
			{
				movx = 1.f;
			}
		}
	}

	if (ENUM_HAS_VALUE(key, Input::Key::Jump))
	{
		if (ground)
		{
			ground = false;

			movy = -0.6f;
		}
	}

	if (ENUM_HAS_VALUE(key, Input::Key::Down))
	{
		if (!ground && movy < 1.f)
		{
			movy += 0.02f;

			if (movy > 1.f)
			{
				movy = 1.f;
			}
		}
	}

	if (ENUM_HAS_VALUE(key, Input::Key::Reset))
	{
		reset();
	}
}

HRESULT Player_Resource::create()
{
	return Direct2D::getHwndRenderTarget()->CreateSolidColorBrush(
		color,
		&solidColorBrush);
}

void Player_Resource::release()
{
	solidColorBrush.release();
}
