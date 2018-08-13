#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/ComPtr.h>

#include <Framework/ID2Object.h>
#include <Framework/IResource.h>

#include <Game/Elements/Collision.h>
#include <Game/PlayerContainer.h>

#include <Windows.h>
#include <d2d1.h>

#include <utility>

#pragma comment(lib, "d2d1.lib")

#define ENUM_HAS_VALUE(_enum, value) (int) _enum & (int) value
#define ENUM_ADD_VALUE(_enum, value) (int&) _enum |= (int) value

class Rectangle_Object;
class Rectangle_Resource
	: public IResource
{
	friend Rectangle_Object;
public:
	Rectangle_Resource(
		const D2D1_COLOR_F color);

	HRESULT create() override;
	void release() override;
private:
	const D2D1_COLOR_F color;
	ComPtr<ID2D1SolidColorBrush> solidColorBrush;
};

class Rectangle_Object
	: public ID2Object
{
public:
	Rectangle_Object(
		Rectangle_Resource* resource,
		D2D1_SIZE_F position,
		Collision::Level level);

	void checkCollisionEdge(
		PlayerContainer player,
		Collision* collision);
	void checkCollisionCorner(
		PlayerContainer player,
		Collision* collision);

	bool checkFallingCornerHorizontal(
		D2D1_SIZE_F position);

	void setPosition(D2D1_SIZE_F position);
	const D2D1_SIZE_F getPosition() const;
	void reloadRect();

	// Return == notify
	virtual bool onCollision(
		PlayerContainer player,
		Collision::Side side) = 0;
	void draw() override;
private:
	void collisionHit(
		PlayerContainer player,
		Collision* collision,
		Collision::Side side);

	bool checkEdgeCollisionPart(
		const float& mainCollider,
		const float& subCollider,
		const float& mainObject,
		const float& subObject,
		const float&& mainOffset) const;

	void checkCollisionCornerHorizontal(
		PlayerContainer player,
		Collision* collision);
	void checkCollisionCornerVertical(
		PlayerContainer player,
		Collision* collision);

	bool checkCornerCollisionPart(
		const float& mainCollider,
		const float& subCollider,
		const float& mainObject,
		const float& subObject,
		const float&& mainOffset) const;
	bool checkCommonCollisionPart(
		const float& collider,
		const float& object,
		const float&& step) const;

	D2D1_SIZE_F position;
	Collision::Level level;

	Rectangle_Resource* resource;
	D2D1_RECT_F rect;
};

inline bool Rectangle_Object::checkFallingCornerHorizontal(
	D2D1_SIZE_F position)
{
	return
		checkCommonCollisionPart(position.width, this->position.width, 0.f) ||
		checkCommonCollisionPart(position.width, this->position.width, 0.5f) ||
		checkCommonCollisionPart(position.width, this->position.width, 1.f);
}

inline const D2D1_SIZE_F Rectangle_Object::getPosition() const
{
	return position;
}

inline bool Rectangle_Object::checkEdgeCollisionPart(
	const float& mainCollider,
	const float& subCollider,
	const float& mainObject,
	const float& subObject,
	const float&& mainOffset) const
{
	return 
		checkCommonCollisionPart(mainCollider, mainObject, std::move(mainOffset)) &&
		checkCommonCollisionPart(subCollider, subObject, 0.5f);
}

inline bool Rectangle_Object::checkCornerCollisionPart(
	const float& mainCollider,
	const float& subCollider,
	const float& mainObject,
	const float& subObject,
	const float&& mainOffset) const
{
	return
		checkCommonCollisionPart(mainCollider, mainObject, std::move(mainOffset)) &&
		(
			checkCommonCollisionPart(subCollider, subObject, 0.f) ||
			checkCommonCollisionPart(subCollider, subObject, 1.f)
		);
}

inline bool Rectangle_Object::checkCommonCollisionPart(
	const float& collider,
	const float& object,
	const float&& collider_offset) const
{
	return
		collider + collider_offset > object && 
		collider + collider_offset < object + 1.f;
}

