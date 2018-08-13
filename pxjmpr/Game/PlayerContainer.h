#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

struct PlayerContainer
{
	PlayerContainer(
		float& movx,
		float& movy,
		D2D1_SIZE_F& position)
		:
		movx(&movx),
		movy(&movy),
		position(&position)
	{
	}

	float *movx;
	float *movy;
	D2D1_SIZE_F *position;
};