#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#pragma comment(lib, "Shlwapi.lib")

#include <Windows.h>
#include <Shlwapi.h>

#include <vector>

class Player;
namespace Game
{
	_Success_(return == true)
	bool initialize();
	void update(float time);

	void onLevelFinished();
	void resetExternalObjects();

	Player* getPlayer();
}
