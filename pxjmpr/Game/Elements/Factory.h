#pragma once

#include <Game/Elements/Rectangle.h>

#include <map>

namespace ElementFactory
{
	typedef Rectangle_Object* (*CreationCallBack)(
		D2D1_SIZE_F size);

	_Success_(return != NULL)
	Rectangle_Object* createRectangleObject(
		wchar_t character,
		D2D1_SIZE_F position);
	void registerRectangleObject(
		wchar_t character,
		CreationCallBack callBack);
}