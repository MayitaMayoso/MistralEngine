#ifndef GAME_OBJECTS_H 
#define GAME_OBJECTS_H

#include "Entity.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>


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

	void Create() {
		visible = false;
	}

private:
	double skyRed = 0.01, skyGreen = 0.05, skyBlue = 0.07;
	float skyRadius = 900;
};

class Camera : public Entity {
public:
	Camera( MistralEngine* g ) : Entity(g) { Create(); };

	void Create();

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

	void Create() {
		visible = false;
	}

private:
	bool initialized = false;

	int starsNumber = 10000;

	int starsPos[10000][3];
};

class Character : public Entity {
public:

	Character(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("link/pose.obj");
		//y_origin = -8.0f;
		x_scale = 0.05f;
		y_scale = 0.05f;
		z_scale = 0.05f;
		y = -6;
	}

	void Update() {
		y_angle -= 0.001;
	}
};

class Nanosuit : public Entity {
public:

	Nanosuit(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("nanosuit/nanosuit.obj");
		//y_origin = -8.0f;
		x_scale = 0.05f;
		y_scale = 0.05f;
		z_scale = 0.05f;
		y = -6;
	}

	void Update() {
		x -= 0.1;
	}
};

#endif