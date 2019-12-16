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
		set_scale(0.04, 0.04, 0.04);
	}

	void Update();

	float max_spd = 0.02f;
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

class Skybox : public Entity {
public:

	Skybox(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("skybox/moon.obj");
	}

	void Update();
};

class Nanosuit : public Entity {
public:

	Nanosuit(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("link/pose.obj");
		set_scale(0.1, 0.1, 0.1);
	}
};

class Universe : public Entity {
public:

	Universe(MistralEngine* g) : Entity(g) { Create(); };

	void Create();

	void Destroy();

	float randomFloat()
	{
		float res;
		unsigned int tmp;

		seed *= 16807;

		tmp = seed ^ (seed >> 4) ^ (seed << 15);

		*((unsigned int*)&res) = (tmp >> 9) | 0x3F800000;

		return (res - 1.0f);
	}

	void Update();
private:
	bool initialized = false;
	bool moving = false;

	GLuint star_texture;
	GLuint star_vao;
	GLuint star_buffer;
	unsigned int seed = 0x13371337;
	float t = (float)glutGet(GLUT_ELAPSED_TIME);

	enum
	{
		NUM_STARS = 8000
	};

};

class Planet : public Entity {
public:

	Planet(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("moon/moon.obj");
		set_scale(0.02, 0.024, 0.02);
	}
};

#endif