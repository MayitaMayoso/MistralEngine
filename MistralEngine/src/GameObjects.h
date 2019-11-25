#include <iostream>
#include <GL/glut.h>

#include "Entity.h"

using namespace std;

class Axis : public Entity {
public:
	Axis( unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {} ;

	void Draw();

private:
	GLfloat length = 10;
};

class SkyBox : public Entity {
public:
	SkyBox(unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {};

	void Draw();

private:
	double skyRed = 0.01, skyGreen = 0.05, skyBlue = 0.07;
	float skyRadius = 900;
};

class Camera : public Entity {
public:
	Camera(unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {};

	void CameraUpdate();
};

class SpaceShip : public Entity {
public:
	SpaceShip(unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {};

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
	Planet(unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {};

	void Update();
	void Draw();

private:
	double spd = 0.5;
	double planetR = 0.6, planetG = 0.2, planetB = 0.1;
	float planetRadius = 6;
};

class Stars : public Entity {
public:
	Stars(unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {};

	void Draw();

private:
	bool initialized = false;

	int starsNumber = 10000;

	int starsPos[10000][3];
};