#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

namespace Timer
{
	void start();
	float reset();

	float getMicroTime();
}
