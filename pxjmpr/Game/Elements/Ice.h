#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Ice_Resource
	: public Rectangle_Resource
{
public:
	Ice_Resource() noexcept
		: Rectangle_Resource(
			D2D1::ColorF(D2D1::ColorF::LightBlue))
	{
	}
};

#define ICE_CHARACTER L'~'
class Ice_Object
	: public Rectangle_Object
{
public:
	Ice_Object(
		D2D1_SIZE_F position);

	bool onCollision(
		PlayerContainer player,
		Collision::Side side) override;

	static void initialize();
private:
	static Ice_Resource* IceResource;
};
