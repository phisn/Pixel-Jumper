#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>
#include <Framework/ID2Object.h>
#include <Framework/IResource.h>
#include <Framework/Window.h>

#include <Windows.h>
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>

#include <vector>
#include <cstdio>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#define PXJ_BORDER_COLOR D2D1::ColorF::ColorF(50, 50, 50)
#define PXJ_PLAYER_COLOR D2D1::ColorF::ColorF(255, 20, 20)
#define PXJ_WALL_COLOR D2D1::ColorF::ColorF(180, 180, 180)
#define PXJ_SPACE_COLOR D2D1::ColorF::ColorF(0, 0, 0)
#define PXJ_ENTRY_COLOR D2D1::ColorF::ColorF(20, 255, 20)
#define PXJ_EXIT_COLOR D2D1::ColorF::ColorF(20, 20, 255)
#define PXJ_TEXT_COLOR D2D1::ColorF(255, 255, 255)

#define MB_FAILED(func, result) \
	wchar_t buff[64] = L""; \
	swprintf_s( \
		buff, \
		func L" Failed,\nECode: %d", \
		result); \
	MessageBox( \
		NULL, \
		buff, \
		L"Error", \
		MB_OK);

namespace Direct2D
{
	_Success_(return == true)
	bool initialize();

	void onCreate();
	void onPaint();
	void onSize(
		UINT width,
		UINT height);

	void registerD2Object(
		ID2Object* object);
	void registerResource(
		IResource* resource);
	void recreateResources();

	void removeAllObjects();
	void removeAllResources();

	D2D1_SIZE_F getWindowSize();

	ID2D1Factory* getFactory();
	ID2D1HwndRenderTarget* getHwndRenderTarget();

	void createCharacterFormat(
		float tileSize);
	IDWriteTextFormat* getCharacterFormat();
	IDWriteTextFormat* getTextFormat();
}
