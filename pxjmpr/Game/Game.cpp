#include "Game.h"

#include <Framework/Direct2D.h>

#include <Game/Level.h>
#include <Game/LevelLoader.h>
#include <Game/Map.h>
#include <Game/Player.h>
#include <Game/ScoreBoard.h>

namespace 
{
	float tickSpeed = 10000.f; // in micro
	float timeSum = 0.f;

	Player player;
	ScoreBoard scoreBoard;
}

namespace Game
{
	bool initialize()
	{
		if (!LevelLoader::initialize())
		{
			return false;
		}

		if (!player.initialize())
		{
			return false;
		}

		if (!scoreBoard.initialize())
		{
			return false;
		}

		if (!Map::initialize())
		{
			return false;
		}

		if (!Map::loadLevel(
				LevelLoader::getNextLevel()))
		{
			return false;
		}

		return true;
	}

	void update(
		float time)
	{
		scoreBoard.update(time);
		timeSum += time;

		while (timeSum > tickSpeed)
		{
			timeSum -= tickSpeed;

			player.update();
		}
	}

	void onLevelFinished()
	{
		Level* level = LevelLoader::getNextLevel();
		if (!level)
		{
			MessageBox(NULL,
				L"All avaible levels played",
				L"Information",
				MB_OK);

			exit(0);
		}

		if (!Map::loadLevel(level))
		{
			MessageBox(NULL,
				L"Unable to load level",
				L"Error",
				MB_OK);

			exit(0);
		}

		scoreBoard.onNextLevel();
	}

	void resetExternalObjects()
	{
		scoreBoard.registerObjects();

		player.reset();
		player.registerObject();
	}

	Player* getPlayer()
	{
		return &player;
	}
}
