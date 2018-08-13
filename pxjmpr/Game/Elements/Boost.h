#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Boost_Resource
	: public Rectangle_Resource
{
public:
	Boost_Resource() noexcept
		: Rectangle_Resource(
			D2D1::ColorF(D2D1::ColorF::Blue))
	{
	}
};

#define BOOST_CHARACTER L'%'
class Boost_Object
	: public Rectangle_Object
{
public:
	Boost_Object(
		D2D1_SIZE_F position);

	bool onCollision(
		PlayerContainer player,
		Collision::Side side) override;

	static void initialize();
private:
	size_t triggerRate = 1000 * 1000;
	float lastTime = 0.f;

	static Boost_Resource* BoostResource;
};
