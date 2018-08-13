#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Fire_Resource
	: public Rectangle_Resource
{
public:
	Fire_Resource() noexcept
		: Rectangle_Resource(
			D2D1::ColorF(D2D1::ColorF::Orange))
	{
	}
};

#define FIRE_CHARACTER L'$'
class Fire_Object
	: public Rectangle_Object
{
public:
	Fire_Object(
		D2D1_SIZE_F position);

	bool onCollision(
		PlayerContainer player, 
		Collision::Side side) override;

	static void initialize();
private:
	static Fire_Resource* fireResource;
};
