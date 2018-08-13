#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Game/Elements/Rectangle.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

#define ENTRY_CHARACTER L'@'
class Entry_Resource;
class Entry_Object
	: public Rectangle_Object
{
public:
	Entry_Object(
		D2D1_SIZE_F position);

	bool onCollision(
		PlayerContainer player,
		Collision::Side side) override
	{
		return false;
	}

	static void initialize();
private:
	static Entry_Resource* entryResource;
};

class Entry_Resource
	: public Rectangle_Resource
{
public:
	Entry_Resource() noexcept
		:
		Rectangle_Resource(D2D1::ColorF::ColorF(1.0f, 1.0f, 0.1f))
	{
	}
};

//	D2D1_COLOR_F color = D2D1::ColorF::ColorF(0.1f, 1.f, 0.1f);
