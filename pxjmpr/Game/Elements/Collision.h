#pragma once

struct Collision
{
	enum class Level
	{
		None,
		Ice,
		Wall,
		Boost,
		Bounce,
		BounceBoost,
		Mirror,
		Fire,
		Exit

	} level;

	enum class Side
	{
		Top = 0b0001,
		Left = 0b0010,
		Bottom = 0b0100,
		Right = 0b1000
	} side;

	bool isSolid();
};

inline bool Collision::isSolid()
{
	return level == Level::Wall; // Bounce?
}

/*

	# - Wall
	@ - Entry
	& - Exit
	$ - Fire
	= - Bonuce
	% - Boost
	+ - BounceBoost
	~ - ice
	\ - Mirro Right
	/ - Mirro Left

*/