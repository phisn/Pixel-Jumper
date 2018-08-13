#include "ScoreBoard.h"
#include <Framework/Direct2D.h>

bool ScoreBoard::initialize()
{
	textResource = new TextResource(
		D2D1::ColorF(D2D1::ColorF::White));
	Direct2D::registerResource(textResource);

	score = new Text(
		textResource,
		10.f,
		10.f);
	time = new Text(
		textResource,
		10.f,
		15.f + Direct2D::getTextFormat()->GetFontSize());

	updateScoreText();

	return true;
}

ScoreBoard::~ScoreBoard()
{
	delete textResource;
	delete time;
}

void ScoreBoard::registerObjects()
{
	Direct2D::registerD2Object(score);
	Direct2D::registerD2Object(time);
}

void ScoreBoard::onNextLevel()
{
	lastUpdate = 0.f;
	timeSum = 0.f;

	++levelNumber;
	updateScoreText();
}

#define TEXT_BUFFER 64

static wchar_t timeBuffer[TEXT_BUFFER];
void ScoreBoard::update(
	float time)
{
	timeSum += time;

	if (lastUpdate + updateStep < timeSum)
	{
		lastUpdate = timeSum;

		ZeroMemory(timeBuffer, TEXT_BUFFER * sizeof(wchar_t));
		swprintf_s(
			timeBuffer,
			time_text, 
			lastUpdate / (1000 * 1000));
		this->time->setText(timeBuffer);
	}
}

static wchar_t scoreBuffer[TEXT_BUFFER];
void ScoreBoard::updateScoreText()
{
	ZeroMemory(scoreBuffer, TEXT_BUFFER * sizeof(wchar_t));
	swprintf_s(
		scoreBuffer,
		score_text,
		levelNumber);
	score->setText(scoreBuffer);
}
