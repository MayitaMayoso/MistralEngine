#include <iostream>
#include <GL/glut.h>

#include "Entity.h"

using namespace std;

class Axis : public Entity {
public:
	Axis( unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {} ;

	void Draw();
};

class SkyBox : public Entity {
public:
	SkyBox(unsigned int identificator, MistralEngine* g) : Entity(identificator, g) {};

	void Draw() {
		glPushMatrix();
		glColor3d(skyRed, skyGreen, skyBlue);
		glutSolidSphere(skyRadius, 10, 10);
		glPopMatrix();
	}

private:
	double skyRed = 0.5, skyGreen = 0.85, skyBlue = 0.9;
	float skyRadius = 900;
};