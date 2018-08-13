#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#include <Framework/Text.h>
#include <Windows.h>


class ScoreBoard
{
public:
	_Success_(return == true)
	bool initialize();
	~ScoreBoard();

	void registerObjects();

	void onNextLevel();
	void update(float time);
private:
	void updateScoreText();

	TextResource* textResource;
	Text* time, * score;

	size_t levelNumber = 1;
	float 
		timeSum,
		lastUpdate = 0.f,
		updateStep = 1000 * 10; // 10 Milli
	const wchar_t
		* score_text = L"Current Level: %d",
		* time_text = L"Time: %.2f";
};

