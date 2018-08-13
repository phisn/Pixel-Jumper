#include "LevelLoader.h"

namespace
{
	std::vector<wchar_t*> levelPaths;

	size_t lastLevelPosition = 0;
	Level* lastLevel = NULL;
}

bool LevelLoader::initialize()
{
	for (int i = 1; ; ++i)
	{
		levelPaths.push_back(new wchar_t[MAX_PATH]);
		ZeroMemory(levelPaths.back(), MAX_PATH * sizeof(wchar_t));
		swprintf_s(levelPaths.back(), MAX_PATH, L"px%d.jmpr", i);

		if (!PathFileExists(levelPaths.back()))
		{
			delete levelPaths.back();
			levelPaths.pop_back();

			break;
		}
	}

	if (levelPaths.size() == 0)
	{
		MessageBox(
			NULL,
			L"No levels found",
			L"Error",
			MB_OK);

		return false;
	}

	return true;
}

Level* LevelLoader::getNextLevel()
{
	if (lastLevel)
	{
		delete lastLevel;
	}

	if (levelPaths.size() - 1 < lastLevelPosition)
	{
		return NULL;
	}

	return lastLevel = new Level(
		levelPaths[lastLevelPosition++]);
}
