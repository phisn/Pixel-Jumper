#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/Input.h>
#include <Game/Elements/Rectangle.h>
#include <Game/Level.h>
#include <Game/PlayerContainer.h>

#include <Windows.h>
#include <d2d1_1helper.h>

#include <vector>

namespace Map
{
	_Success_(return == true)
	bool initialize();
	_Success_(return == true)
	bool loadLevel(Level* level);

	D2D1_SIZE_F getSize();
	D2D1_SIZE_F getEntry();

	D2D1_RECT_F positionToRect(
		D2D1_SIZE_F position);
	Collision checkCollision(
		PlayerContainer player);
	bool falling(
		const D2D1_SIZE_F position);
}
