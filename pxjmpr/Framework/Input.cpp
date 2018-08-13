#include "Input.h"

namespace
{
	int _keys[INPUT_NKEYS] =
	{
		VK_UP,		// Jump
		VK_LEFT,	// Left
		VK_RIGHT,	// Right
		VK_DOWN,	// Down
		'R',		// Reset
		'E',		// Interact
	};
}

namespace Input
{
	const Key getPressedKeys()
	{
		Key resultKey = (Key) 0, currentKey = (Key) 1;

		for (int i = 0; i < INPUT_NKEYS; ++i, (int&) currentKey *= 2)
			if (GetAsyncKeyState(_keys[i]) & 0x8000)
			{
				(int&)resultKey |= (int)currentKey;
			}

		return resultKey;
	}

	void changeVirtualKeyKey(
		const Key key, 
		const int virtualKey)
	{
		_keys[(int) std::log2((int) key)] = virtualKey;
	}
}