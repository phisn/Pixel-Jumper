#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Game/Level.h>

#include <Windows.h>
#include <Shlwapi.h>

#include <fstream>
#include <vector>

namespace LevelLoader
{
	_Success_(return == true)
	bool initialize();
	Level* getNextLevel();
}