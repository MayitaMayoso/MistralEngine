#ifndef GAME_OBJECTS_H 
#define GAME_OBJECTS_H

#include "Entity.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

class Character : public Entity {
public:

	Character(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("aircraft/aircraft.obj");
		//y_origin = -8.0f;
		x_scale = 0.4f;
		y_scale = 0.4f;
		z_scale = 0.4f;
	}

	void Update();

	float max_spd = 0.2f;
	float max_rspd = 1.0f;
	float x_spd = 0.0f;
	float y_spd = 0.0f;
	float z_spd = 0.0f;
	float rx_spd = 0.0f;
	float ry_spd = 0.0f;
	float rz_spd = 0.0f;
	float spd = 0.0f;
	float acceleration = 0.01f;
};

class Planet : public Entity {
public:

	Planet(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {

		LoadModel("moon/moon.obj");
	}

	void Update();
};

class Nanosuit : public Entity {
public:

	Nanosuit(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("link/pose.obj");
	}
};

/*
class Spaceship : public Entity {
public:

	Spaceship(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("aircraft/aircraft.obj");
	}
};
*/

#endif