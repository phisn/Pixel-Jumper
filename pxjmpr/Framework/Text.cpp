#include "Text.h"
#include <Framework/Direct2D.h>

HRESULT TextResource::create()
{
	return Direct2D::getHwndRenderTarget()->CreateSolidColorBrush(
		color,
		&solidColorBrush);
}

void TextResource::release()
{
	solidColorBrush.release();
}

Text::Text(
	TextResource* resource,
	float x,
	float y)
	:
	resource(resource),
	x(x),
	y(y)
{
}

Text::~Text()
{
}

void Text::draw()
{
	if (text)
	{
		Direct2D::getHwndRenderTarget()->DrawTextW(
			text,
			textLength,
			Direct2D::getTextFormat(),
			rect,
			resource->solidColorBrush.get());
	}
}

void Text::setText(const wchar_t* text)
{
	this->text = text;
	textLength = wcslen(text);

	rect.top = y;
	rect.left = x;

	float fontSize = Direct2D::getTextFormat()->GetFontSize();

	rect.bottom = y + fontSize;
	rect.right = x + fontSize * textLength;
}