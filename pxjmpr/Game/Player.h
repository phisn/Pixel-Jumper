#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>

#include <Framework/ID2Object.h>
#include <Framework/IResource.h>

#include <Game/PlayerContainer.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Player;
class Player_Resource
	: public IResource
{
public:
	HRESULT create() override;
	void release() override;

private:
	friend Player;

	D2D1_COLOR_F color = D2D1::ColorF::ColorF(1.f, 0.f, 0.f);
	ComPtr<ID2D1SolidColorBrush> solidColorBrush;
};

class Player
	: public ID2Object
{
public:
	Player() noexcept
	{
		deleteOnRelease = false;
	}

	_Success_(return == true)
	bool initialize();

	void registerObject();
	void reset();
	void update();

	void draw() override;

	const D2D1_SIZE_F getPosition() const;
private:
	void handleInput();

	D2D1_SIZE_F position = { };
	float movx = 0.f, movy = 0.f;

	bool ground = false, slide = false;

	Player_Resource resource;
};

inline const D2D1_SIZE_F Player::getPosition() const
{
	return position;
}