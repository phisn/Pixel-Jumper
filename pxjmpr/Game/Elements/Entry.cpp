#include "Entry.h"
#include <Framework/Direct2D.h>
#include <Game/Elements/Factory.h>
#include <Game/Game.h>

Entry_Object::Entry_Object(
	D2D1_SIZE_F position)
	:
	Rectangle_Object(
		entryResource,
		position,
		Collision::Level::None)
{
}

Entry_Resource* Entry_Object::entryResource;
void Entry_Object::initialize()
{
	Direct2D::registerResource(entryResource = new Entry_Resource());
	ElementFactory::registerRectangleObject(
		ENTRY_CHARACTER,
		[](D2D1_SIZE_F position)->Rectangle_Object*
	{
		return new Entry_Object(position);
	});
}
