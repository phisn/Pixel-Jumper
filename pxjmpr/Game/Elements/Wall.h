#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

#define WALL_CHARACTER L'#'
class Wall_Resource;
class Wall_Object
	: public Rectangle_Object
{
public:
	Wall_Object(
		D2D1_SIZE_F position);

	bool onCollision(
		PlayerContainer player,
		Collision::Side side) override;

	static void initialize();
private:
	static Wall_Resource* wallResource;
};

class Wall_Resource 
	: public Rectangle_Resource
{
public:
	Wall_Resource() noexcept
		:
		Rectangle_Resource(D2D1::ColorF::ColorF(0.6f, 0.6f, 0.6f, 1.f))
	{
	}
};

