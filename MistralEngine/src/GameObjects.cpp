#include "MistralEngine.h"
#include "GameObjects.h"

void Axis::Draw() {
	glPushMatrix();
	GLUquadric* qobj = gluNewQuadric();
	float length = 4;
	float radius = float(0.1);
	float clen = float(0.5);
	float crad = float(0.2);

	// Axis X (Red)
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRotatef(90, 0, 1, 0);
	gluCylinder(qobj, radius, radius, length, 10, 1);
	glTranslatef(0, 0, length);
	glutSolidCone(crad, clen, 10, 10);
	glPopMatrix();

	// Axis Y (Green)
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, radius, radius, length, 10, 1);
	glTranslatef(0, 0, length);
	glutSolidCone(crad, clen, 10, 10);
	glPopMatrix();

	// Axis Z (Blue)
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	gluCylinder(qobj, radius, radius, length, 10, 1);
	glTranslatef(0, 0, length);
	glutSolidCone(crad, clen, 10, 10);
	glPopMatrix();

	// White sphere
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.3, 10, 10);
	glPopMatrix();
	glPopMatrix();

	cout << game->EntitiesCount;
}