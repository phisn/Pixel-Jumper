#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <cmath>

#define INPUT_NKEYS 6
#define ENUM_HAS_VALUE(keyi, key) ((int) keyi & (int) key)

namespace Input
{
	enum class Key
	{
		None		= 0b000000,
		Jump		= 0b000001,
		Left		= 0b000010,
		Right		= 0b000100,
		Down		= 0b001000,
		Reset		= 0b010000,
		Interact	= 0b100000, // ? remove maybe
	};

	const Key getPressedKeys();
	void changeVirtualKeyKey(
		const Key key, 
		const int virtualKey);
}
