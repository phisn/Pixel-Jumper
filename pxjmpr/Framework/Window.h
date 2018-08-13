#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

namespace Window
{
	_Success_(return == true)
	bool initialize();

	HWND getHandle();
	// return == redraw
	void update(float time);
}
