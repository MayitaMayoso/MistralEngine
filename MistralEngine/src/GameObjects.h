#ifndef GAME_OBJECTS_H 
#define GAME_OBJECTS_H 

#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include "Entity.h"

using namespace std;

class Axis : public Entity {
public:
	Axis( MistralEngine* g ) : Entity(g) { Create(); };

	void Draw();

private:
	GLfloat length = 10;
};

class SkyBox : public Entity {
public:
	SkyBox( MistralEngine* g ) : Entity(g) { Create(); };

	void Draw();

private:
	double skyRed = 0.01, skyGreen = 0.05, skyBlue = 0.07;
	float skyRadius = 900;
};

class Camera : public Entity {
public:
	Camera( MistralEngine* g ) : Entity(g) { Create(); };

	void CameraUpdate();

	Entity* target;
};

class SpaceShip : public Entity {
public:
	SpaceShip( MistralEngine* g ) : Entity(g) { Create(); };

	void Update();

	void Draw();

private:
	double y_rot = 0;
	double z_rot = 0;
	double radius = 10;
	double spd = 0.015;
};

class Planet : public Entity {
public:
	Planet( MistralEngine* g ) : Entity(g) { Create(); };

	void Update();
	void Draw();

private:
	double spd = 0.5;
	double planetR = 0.6, planetG = 0.2, planetB = 0.1;
	float planetRadius = 6;
};

class Stars : public Entity {
public:
	Stars( MistralEngine*  g ) : Entity(g) { Create(); };

	void Draw();

private:
	bool initialized = false;

	int starsNumber = 10000;

	int starsPos[10000][3];
};

class Eye : public Entity {
public:

	Eye(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("Resources/Models/Eyeball/Eyeball.obj", "Resources/Shaders/vertex1.frag", "Resources/Shaders/fragment1.frag");
		y_origin = -8.0f;
		x_scale = 0.1f;
		y_scale = 0.1f;
		z_scale = 0.1f;
		y = id;
	}

	void Update() {
		y_angle += 0.001;
	}
};

class NanoSuit : public Entity {
public:

	NanoSuit(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("Resources/Models/nanosuit/nanosuit.obj", "Resources/Shaders/vertex1.frag", "Resources/Shaders/fragment1.frag");
		y_origin = -8.0f;
		x_scale = 0.1f;
		y_scale = 0.1f;
		z_scale = 0.1f;
	}

	void Update() {
		z_angle += 0.001;
	}
};

#endif