#include <Game/Game.h>
#include <Game/Level.h>
#include <Game/Map.h>

#include <Framework/Direct2D.h>
#include <Framework/Timer.h>
#include <Framework/Window.h>

#include <iostream>

#ifdef _DEBUG
int main()
#else
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
#endif
{
	if (!Direct2D::initialize())
	{
		exit(1);
	}

	if (!Window::initialize())
	{
		exit(2);
	}

	if (!Game::initialize())
	{
		exit(3);
	}

	MSG message;
	float time;

	Timer::start();
	while (true)
	{
		if (PeekMessage(
			&message,
			NULL,
			0,
			0,
			PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		time = Timer::reset();

		Game::update(time);

		// dont need to display faster than games tickrate
		// idea: remove tickrate, position = movx * time;
		Window::update(time);
	}
}