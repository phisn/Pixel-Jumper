#pragma once

class ID2Object
{
public:
	virtual void draw() = 0;

	const bool isDor() const;
protected:
	bool deleteOnRelease = true;
};

inline const bool ID2Object::isDor() const
{
	return deleteOnRelease;
}
