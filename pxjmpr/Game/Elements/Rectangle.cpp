#include "Rectangle.h"
#include <Framework/Direct2D.h>
#include <Game/Map.h>

Rectangle_Resource::Rectangle_Resource(
	const D2D1_COLOR_F color)
	:
	color(color)
{
}

HRESULT Rectangle_Resource::create()
{
	std::cout << color.r << std::endl;
	std::cout << color.g << std::endl;
	std::cout << color.b << std::endl;
	std::cout << color.a << std::endl;
	std::cout << " -------------------- " << std::endl;

	return Direct2D::getHwndRenderTarget()->CreateSolidColorBrush(
		color,
		&solidColorBrush);
}

void Rectangle_Resource::release()
{
	solidColorBrush.release();
}

 Rectangle_Object::Rectangle_Object(
	 Rectangle_Resource* resource, 
	 D2D1_SIZE_F position, 
	 Collision::Level level)
	 :
	 resource(resource),
	 level(level),
	 position(position),
	 rect({ })
{
}

 void Rectangle_Object::checkCollisionEdge(
	 PlayerContainer player, 
	 Collision* collision)
 {
	 if (checkEdgeCollisionPart(
			 player.position->width,
			 player.position->height,
			 position.width,
			 position.height,
			 1.f)) // Right
	 {
		 collisionHit(player, collision, Collision::Side::Right);
	 }

	 if (checkEdgeCollisionPart(
			 player.position->height,
			 player.position->width,
			 position.height,
			 position.width,
			 1.f)) // Bottom
	 {
		 collisionHit(player, collision, Collision::Side::Bottom);
	 }

	 if (checkEdgeCollisionPart(
			 player.position->width,
			 player.position->height,
			 position.width,
			 position.height,
			 0.f)) // Left
	 {
		 collisionHit(player, collision, Collision::Side::Left);
	 }

	 if (checkEdgeCollisionPart(
			 player.position->height,
			 player.position->width,
			 position.height,
			 position.width,
			 0.f)) // Top
	 {
		 collisionHit(player, collision, Collision::Side::Top);
	 }
}

 void Rectangle_Object::checkCollisionCorner(
	 PlayerContainer player, 
	 Collision* collision)
{
	 float r = (player.position->width + 1.f) - position.width;
	 float l = (position.width + 1.f) - player.position->width;

	 float b = (player.position->height + 1.f) - position.height;
	 float t = (position.height + 1.f) - player.position->height;

	 if (r > 0.f && r < 1.f)
	 {
		 if (b > 0.f && b < 1.f)
		 {
			 if (r < b)
			 {
				 checkCollisionCornerHorizontal(
					 player,
					 collision);
			 }
			 else
			 {
				 checkCollisionCornerVertical(
					 player,
					 collision);
			 }
		 }
		 else if (t > 0.f && t < 1.f)
		 {
			 if (r < t)
			 {
				 checkCollisionCornerHorizontal(
					 player,
					 collision);
			 }
			 else
			 {
				 checkCollisionCornerVertical(
					 player,
					 collision);
			 }
		 }
		 else
		 {
			 checkCollisionCornerHorizontal(
				 player,
				 collision);
		 }
	 }
	 else if (l > 0.f && l < 1.f)
	 {
		 if (b > 0.f && b < 1.f)
		 {
			 if (l < b)
			 {
				 checkCollisionCornerHorizontal(
					 player,
					 collision);
			 }
			 else
			 {
				 checkCollisionCornerVertical(
					 player,
					 collision);
			 }
		 }
		 else if (t > 0.f && t < 1.f)
		 {
			 if (l < t)
			 {
				 checkCollisionCornerHorizontal(
					 player,
					 collision);
			 }
			 else
			 {
				 checkCollisionCornerVertical(
					 player,
					 collision);
			 }
		 }
		 else
		 {
			 checkCollisionCornerHorizontal(
				 player,
				 collision);
		 }
	 }
	 else
	 {
		 checkCollisionCornerVertical(
			player,
			collision);
	 }
}

void Rectangle_Object::checkCollisionCornerHorizontal(
	PlayerContainer player, 
	Collision* collision)
{
	if (checkCornerCollisionPart(
		player.position->width,
		player.position->height,
		position.width,
		position.height,
		1.f)) // Right
	{
		collisionHit(player, collision, Collision::Side::Right);
	}


	if (checkCornerCollisionPart(
		player.position->width,
		player.position->height,
		position.width,
		position.height,
		0.f)) // Left
	{
		collisionHit(player, collision, Collision::Side::Left);
	}
}

void Rectangle_Object::checkCollisionCornerVertical(
	PlayerContainer player, 
	Collision* collision)
{
	if (checkCornerCollisionPart(
		player.position->height,
		player.position->width,
		position.height,
		position.width,
		1.f)) // Bottom
	{
		collisionHit(player, collision, Collision::Side::Bottom);
	}


	if (checkCornerCollisionPart(
		player.position->height,
		player.position->width,
		position.height,
		position.width,
		0.f)) // Top
	{
		collisionHit(player, collision, Collision::Side::Top);
	}
}

void Rectangle_Object::draw()
{
	Direct2D::getHwndRenderTarget()->FillRectangle(
		rect,
		resource->solidColorBrush.get());
}

void Rectangle_Object::collisionHit(
	PlayerContainer player,
	Collision* collision,
	Collision::Side side)
{
	if (onCollision(player, side))
	{
		if (collision->level == level)
		{
			ENUM_ADD_VALUE(
				collision->side,
				side);
		}
		else
		{
			collision->level = level;
			collision->side = side;
		}
	}
}

void Rectangle_Object::setPosition(
	D2D1_SIZE_F position)
{
	this->position = position;
	reloadRect();
}

void Rectangle_Object::reloadRect()
{
	rect = Map::positionToRect(
		position);
}

