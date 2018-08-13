#include "Border.h"
#include <Framework/Direct2D.h>

Border_Object::Border_Object(
	float widthBorder, 
	float heightBorder)
	:
	wb(widthBorder),
	hb(heightBorder),
	top({}),
	bottom({}),
	left({}),
	right({})
{
	D2D1_SIZE_F winSize = Direct2D::getHwndRenderTarget()->GetSize();

	if (hb)
	{
		top.top = 0.f;
		top.left = 0.f;
		top.right = winSize.width;
		top.bottom = heightBorder;

		bottom.top = winSize.height - heightBorder;
		bottom.left = 0.f;
		bottom.right = winSize.width;
		bottom.bottom = winSize.height;
	}

	if (wb)
	{
		left.top = 0.f;
		left.left = 0.f;
		left.bottom = winSize.height;
		left.right = widthBorder;

		right.top = 0.f;
		right.left = winSize.width - widthBorder;
		right.bottom = winSize.height;
		right.right = winSize.width;
	}
}

void Border_Object::draw()
{
	if (hb)
	{
		Direct2D::getHwndRenderTarget()->FillRectangle(
			top,
			resource->solidColorBrush.get());

		Direct2D::getHwndRenderTarget()->FillRectangle(
			bottom,
			resource->solidColorBrush.get());
	}

	if (wb)
	{
		Direct2D::getHwndRenderTarget()->FillRectangle(
			left,
			resource->solidColorBrush.get());

		Direct2D::getHwndRenderTarget()->FillRectangle(
			right,
			resource->solidColorBrush.get());
	}
}

Border_Resource* Border_Object::resource;
void Border_Object::initialize()
{
	Direct2D::registerResource(resource = new Border_Resource());
}

HRESULT Border_Resource::create()
{
	return Direct2D::getHwndRenderTarget()->CreateSolidColorBrush(
		color,
		&solidColorBrush);
}

void Border_Resource::release()
{
	solidColorBrush.release();
}
