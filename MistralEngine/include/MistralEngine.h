#ifndef MISTRAL_ENGINE_H 
#define MISTRAL_ENGINE_H 

#include <iostream>
#include <chrono>
#include <list>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <glm.hpp>
#include <iostream>
#include <vector>
#include "Program.h"

# define PI 3.14159265358979323846

using namespace std;

class Entity;

class MistralEngine {
public:
	MistralEngine();

	int Run(int argc, char* args[], MistralEngine* s);
	float wave(float from, float to, float duration, float offset);

	static MistralEngine* self;

	static void setSelf(MistralEngine* s) { self = s;  };
	GLint getProgram(string name);


	int width, height, fov, fps;
	float AspectRatio;

	glm::mat4 cameraView = glm::mat4(1.0f);

	chrono::high_resolution_clock::time_point t0;
	int CurrentTime;

	unsigned int EntitiesCount();
	list<Entity*> EntitiesList;
	vector<pair<string, GLint>> programs;

private:
	void CalculateTime();

	virtual void GeneralUpdate(int value);
	virtual void GeneralDraw();

	static void UpdateCallback(int value) { self->GeneralUpdate(value); };
	static void DrawCallback() { self->GeneralDraw(); };
};
#endif