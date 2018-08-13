#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>

#include <Framework/ID2Object.h>
#include <Framework/IResource.h>

#include <Windows.h>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Border_Resource;
class Border_Object
	: public ID2Object
{
public:
	Border_Object(
		float widthBorder,
		float heightBorder);

	void draw() override;
	static void initialize();
private:
	bool wb, hb;

	D2D1_RECT_F top, bottom, left, right;
	static Border_Resource* resource;
};

class Border_Resource
	: public IResource
{
public:
	_Success_(return == true)
	HRESULT create() override;
	void release() override;
private:
	friend Border_Object;

	const D2D1_COLOR_F color = D2D1::ColorF::ColorF(0.1f, 0.1f, 0.1f, 1.f);
	ComPtr<ID2D1SolidColorBrush> solidColorBrush;
};
