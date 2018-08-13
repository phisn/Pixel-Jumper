#include "Factory.h"

namespace
{
	std::map<wchar_t, ElementFactory::CreationCallBack> 
		rectangleCreationCallBacks;
}

namespace ElementFactory
{
	Rectangle_Object* createRectangleObject(
		wchar_t character,
		D2D1_SIZE_F position)
	{
		decltype(rectangleCreationCallBacks)::iterator iterator 
			= rectangleCreationCallBacks.find(character);
		if (iterator == rectangleCreationCallBacks.end())
		{
			return NULL;
		}
		else
		{
			return iterator->second(position);
		}
	}

	void registerRectangleObject(
		wchar_t character,
		CreationCallBack callBack)
	{
		rectangleCreationCallBacks[character] = callBack;
	}
}
