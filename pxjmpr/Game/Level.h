#pragma once

#include <Game/Elements/Factory.h>
#include <Game/Elements/Rectangle.h>

#include <fstream>
#include <iostream>
#include <vector>

#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

class Level
{
public:
	Level(const wchar_t* path);
	~Level();

	const std::vector<Rectangle_Object*>& getRectangleObjects() const;

	const D2D1_SIZE_F& getSize() const;
	const D2D1_SIZE_F& getEntry() const;
	const D2D1_SIZE_F& getExit() const;
private:

	size_t fileSize;
	wchar_t* binaryFile;

	void loadFile(const wchar_t* path);
	void parseBinaryFile();

	std::vector<Rectangle_Object*> rectangleObjects;
	D2D1_SIZE_F size, begin, end;
};

inline const std::vector<Rectangle_Object*>& Level::getRectangleObjects() const
{
	return rectangleObjects;
}

inline const D2D1_SIZE_F& Level::getSize() const
{
	return size;
}

inline const D2D1_SIZE_F& Level::getEntry() const
{
	return begin;
}

inline const D2D1_SIZE_F& Level::getExit() const
{
	return end;
}
