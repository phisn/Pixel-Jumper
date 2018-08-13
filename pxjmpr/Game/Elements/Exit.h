#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

#define EXIT_CHARACTER L'&'
class Exit_Resource;
class Exit_Object
	: public Rectangle_Object
{
public:
	Exit_Object(
		D2D1_SIZE_F position);

	bool onCollision(
		PlayerContainer player,
		Collision::Side side) override;

	static void initialize();
private:
	static Exit_Resource* exitResource;
};

class Exit_Resource
	: public Rectangle_Resource
{
public:
	Exit_Resource() noexcept
		:
		Rectangle_Resource(D2D1::ColorF::ColorF(0.1f, 1.f, 0.1f))
	{
	}
};

//	D2D1_COLOR_F color = D2D1::ColorF::ColorF(0.1f, 1.f, 0.1f);
