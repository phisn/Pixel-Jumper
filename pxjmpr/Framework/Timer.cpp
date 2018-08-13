#include "Timer.h"

namespace
{
	float _frequency;
	LARGE_INTEGER _counter;
}

#include <iostream>
namespace Timer
{
	void start()
	{
		LARGE_INTEGER frequency;
		if (!QueryPerformanceFrequency(
				&frequency))
		{
			MessageBox(
				NULL, 
				L"Your system does not support\nthe function: QueryPerformanceFrequency", 
				L"Error",
				MB_OK);


			exit(NULL);
		}

		_frequency = frequency.QuadPart / (1000 * 1000); // micro
		reset();
	}

	float reset()
	{
		register LARGE_INTEGER temp_counter =
			_counter;
		QueryPerformanceCounter(
			&_counter);

		return (_counter.QuadPart - temp_counter.QuadPart) / _frequency;
	}

	float getMicroTime()
	{
		register LARGE_INTEGER time;
		QueryPerformanceCounter(
			&time);

		return time.QuadPart / _frequency;
	}
}
