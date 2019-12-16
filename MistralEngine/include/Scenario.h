#ifndef SCENARIO_H
#define SCENARIO_H
#pragma once
#include <string>

class MistralEngine;

class Scenario
{
public:
	Scenario(MistralEngine* g);
	void ReadScenario(string path);
	void ChangeScenario(string path);
	void CheckAndChangeScenario();

	string name;

private:
	MistralEngine* game;

	bool room2change = false;
	string nextRoom;
};
#endif