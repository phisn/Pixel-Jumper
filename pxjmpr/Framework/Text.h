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

class Text;
class TextResource
	: public IResource
{
public:
	TextResource(
		D2D1_COLOR_F color)
		:
		color(color)
	{
	}

	HRESULT create() override;
	void release() override;
private:
	friend Text;
	ComPtr<ID2D1SolidColorBrush> solidColorBrush;

	D2D1_COLOR_F color;
};

class Text
	: public ID2Object
{
public:
	Text(
		TextResource* resource,
		float x,
		float y);
	~Text();

	void setText(const wchar_t* text);
	void draw() override;
private:
	float x, y;
	D2D1_RECT_F rect;

	TextResource* resource;
	const wchar_t* text = NULL;
	size_t textLength;
};
