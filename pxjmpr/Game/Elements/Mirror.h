#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Mirror_Resource
	: public Rectangle_Resource
{
public:
	Mirror_Resource() noexcept
		: Rectangle_Resource(
			D2D1::ColorF(D2D1::ColorF::White))
	{
	}
};

#define MIRROR_RIGHT_CHARACTER L'\\'
#define MIRROR_LEFT_CHARACTER L'/'

// Draw equ character on tile
class Mirror_Object
	: public Rectangle_Object
{
public:
	Mirror_Object(
		D2D1_SIZE_F position,
		bool invert);

	bool onCollision(
		PlayerContainer player,
		Collision::Side side) override;

	static void initialize();
private:
	size_t triggerRate = 1000 * 100;
	float lastTime = 0.f;

	bool invert;
	static Mirror_Resource* MirrorResource;
};
