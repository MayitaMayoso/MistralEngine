#ifndef SCENARIO_H
#define SCENARIO_H
#pragma once
#include <string>
#include "MistralEngine.h"
#include "GameObjects.h"


class Scenario
{
public:
	Scenario(MistralEngine* game);
	void ReadScenario(string path);

private:
	MistralEngine* m_game;
};
#endif