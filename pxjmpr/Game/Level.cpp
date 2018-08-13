#include "Level.h"


Level::Level(
	const wchar_t* path)
	:
	fileSize(NULL),
	binaryFile(NULL)
{
	std::wcout << "Loading " << path << std::endl;

	loadFile(path);
	parseBinaryFile();

	delete binaryFile;

	std::wcout << L"Width: " << size.width << L", Height: " << size.height << std::endl;
	std::wcout << L"Start, X:" << begin.width << L", Y:" << begin.height << std::endl;
	std::wcout << L"End, X:" << end.width << L", Y:" << end.height << std::endl;
	std::wcout << "Object count: " << rectangleObjects.size() << std::endl;
}

Level::~Level()
{
	for (Rectangle_Object* object : rectangleObjects)
	{
		delete object;
	}
}

void Level::loadFile(
	const wchar_t* path)
{
	std::wifstream file(
		path,
		std::ios::in |
		std::ios::binary |
		std::ios::ate);

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	binaryFile = new wchar_t[fileSize];

	file.seekg(0, std::ios::beg);
	file.read(binaryFile, fileSize);
	file.close();
}

void Level::parseBinaryFile()
{
	size = { };

	for (int i = 0, remain = 0; i < fileSize; ++i)
	{
		Rectangle_Object* object = ElementFactory::createRectangleObject(
			binaryFile[i],
			D2D1::SizeF(
				i - remain,
				size.height));

		switch (binaryFile[i])
		{
		case '\r':
		case '\n':
			++size.height;

			if (i - remain > size.width)
			{
				size.width = i - remain;
			}

			if (binaryFile[i + 1] == '\r' || 
				binaryFile[i + 1] == '\n')
			{
				++i;
			}

			remain = i + 1;

			break;
		case '@':
			begin = object->getPosition();

			break;
		case '&':
			end = object->getPosition();

			break;
		case ' ': // Ignore
			break; 
		default:
			if (!object)
			{
				std::wcout
					<< L"Unsupported character" << binaryFile[i]
					<< L"at position x: " << remain - i 
					<< L", y: " << size.height << std::endl;
			}

			break;
		}

		if (object)
		{
			rectangleObjects.push_back(object);
		}
	}

	++size.height;
}
