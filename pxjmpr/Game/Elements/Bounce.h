#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Bounce_Resource
	: public Rectangle_Resource
{
public:
	Bounce_Resource() noexcept
		: Rectangle_Resource(
			D2D1::ColorF(D2D1::ColorF::Magenta))
	{
	}
};

#define BOUNCE_CHARACTER L'='
class Bounce_Object
	: public Rectangle_Object
{
public:
	Bounce_Object(
		D2D1_SIZE_F position);

	bool onCollision(
		PlayerContainer player,
		Collision::Side side) override;

	static void initialize();
private:
	static Bounce_Resource* BounceResource;
};
