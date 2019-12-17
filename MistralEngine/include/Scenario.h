#ifndef SCENARIO_H
#define SCENARIO_H
#pragma once
#include <string>
#include <map>

using namespace std;

class MistralEngine;

class Scenario
{
public:
	Scenario(MistralEngine* g);
	void ReadScenario(string path);
	void ChangeScenario(string path);
	void CheckAndChangeScenario();

	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, float opacity);

	string name;

private:
	MistralEngine* game;

	bool room2change = false;
	string nextRoom;

	struct Char {
		GLuint TextureID; // Id de la textura
		glm::ivec2 Size; // Tamano del texto
		glm::ivec2 Bearing; // Offset de arriba a abajo del texto
		GLuint Advance; // Offset hacia la derecha del texto
	};

	map<GLchar, Char> Characters;

	GLuint VAO;
	GLuint VBO;

	Program program;
};
#endif