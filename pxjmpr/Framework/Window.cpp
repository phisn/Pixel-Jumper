#include "Window.h"
#include <Framework/Direct2D.h>

#include <iostream>
namespace
{
	float timeSum;
	int _framerate_micro = 1000 * 20;

	HWND _window = NULL;
	WNDCLASS _windowClass;

	LRESULT CALLBACK windowProc(
		HWND window, 
		UINT message, 
		WPARAM wparam, 
		LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);

			break;
		case WM_KEYDOWN:
			if (wparam == VK_ESCAPE)
			{
				DestroyWindow(window);
			}

			break;
		/*case WM_PAINT:
			Direct2D::onPaint();

			break;*/
		case WM_SIZE:
			Direct2D::onSize(
				LOWORD(lparam),
				HIWORD(lparam));

			break;
		case WM_NCCREATE:
			_window = window;
			Direct2D::onCreate();

		default:
			return DefWindowProc(
				window,
				message,
				wparam,
				lparam);
		}

		return 0;
	}
}


#include <iostream>
#include <Framework/Timer.h>
namespace Window
{
	bool initialize()
	{
		ZeroMemory(&_windowClass, sizeof(WNDCLASS));
		_windowClass.hInstance = GetModuleHandle(NULL);
		_windowClass.lpfnWndProc = windowProc;
		_windowClass.lpszClassName = L"pxjmpr_window";
		_windowClass.style = CS_HREDRAW | CS_HREDRAW;

		RegisterClass(&_windowClass);

		_window = CreateWindow(
			_windowClass.lpszClassName,
			L"Pixel Jumper",
			WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			_windowClass.hInstance,
			NULL);
		if (_window)
		{
			ShowWindow(_window, SW_SHOWMAXIMIZED);
			UpdateWindow(_window);
		}
		else
		{
			MB_FAILED(L"CreateWindow", GetLastError());

			exit(0);
		}

		return true;
	}

	HWND getHandle()
	{
		return _window;
	}
	void update(float time)
	{
/*		timeSum += time;
		
		if (timeSum > _framerate_micro)
		{
			// _time -= _framerate_micro;
			timeSum = 0;

			Direct2D::onPaint();
		}*/

		float wait = _framerate_micro - time;
		if (wait > 0.f)
		{
			Sleep((DWORD) (wait / 1000.f));
		}

		Direct2D::onPaint();
	}
}
