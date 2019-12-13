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

class Light;

class Input;

class Camera;

class Scenario;

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

	Light* lightscene;
	unsigned int EntitiesCount();
	list<Entity*> EntitiesList;
	vector<pair<string, GLint>> programs;
	Input* input;
	Camera* camera;
	Scenario* scenario;

private:
	void CalculateTime();

	virtual void GeneralUpdate(int value);
	virtual void GeneralDraw();
	virtual void GeneralPressKeyboard( unsigned char key, int x, int y );
	virtual void GeneralPressSpecial( int key, int x, int y );
	virtual void GeneralPressGamepad( unsigned int key, int x, int y, int z );
	virtual void GeneralReleaseKeyboard(unsigned char key, int x, int y);
	virtual void GeneralReleaseSpecial(int key, int x, int y);
	//virtual void GeneralReleaseGamepad(unsigned int key, int x, int y, int z);

	static void UpdateCallback( int value ) { self->GeneralUpdate(value); };
	static void DrawCallback() { self->GeneralDraw(); };
	static void KeyboardPressCallback( unsigned char key, int x, int y ) { self->GeneralPressKeyboard( key, x, y); };
	static void SpecialPressCallback( int key, int x, int y) { self->GeneralPressSpecial(key, x, y); };
	static void GamepadPressCallback( unsigned int key, int x, int y, int z ) { self->GeneralPressGamepad(key, x, y, z); };
	static void KeyboardReleaseCallback(unsigned char key, int x, int y) { self->GeneralReleaseKeyboard(key, x, y); };
	static void SpecialReleaseCallback(int key, int x, int y) { self->GeneralReleaseSpecial(key, x, y); };
	//static void GamepadReleaseCallback(unsigned int key, int x, int y, int z) { self->GeneralReleaseGamepad(key, x, y, z); };
};
#endif