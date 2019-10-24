#include <iostream>
#include <GL/glut.h>
#include <chrono>
#include <list>

#include "Entity.h"
#include "GameObjects.h"

using namespace std;

# define PI 3.14159265358979323846

// VIEW VARIABLES
int width = 1280;
int height = 720;
float aspect_ratio = float(width) / float(height);
int fov = 60;
int fps = 60;

// TIMER VARIABLES
chrono::high_resolution_clock::time_point t0 = chrono::high_resolution_clock::now();
chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
chrono::duration<float> timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
int CurrentTime = int(timer.count()*1000);

// INSTANCES VARIABLES
unsigned int EntitiesCount = 0;
list<Entity*> EntitiesList;

float wave(float from, float to, float duration, float offset) {
	float A = float((to - from) * 0.5);
	float W = float(CurrentTime * 0.001);

	return float(from + A + A * sin((2 * PI * W) / duration + offset));
}

Entity * Instantiate( int ObjectType ) {
	Entity* e;

	switch (ObjectType) {
		case 0:	e = new Axis(EntitiesCount);	break;
		case 1:	e = new SkyBox(EntitiesCount);	break;
		default:	e = new Entity(EntitiesCount);	break;
	}
	EntitiesList.push_back(e);
	EntitiesCount++;
	return e;
}

void CalculateTime() {
	t1 = chrono::high_resolution_clock::now();
	timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
	CurrentTime = int(timer.count() * 1000);
}

void GeneralDraw() {

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, aspect_ratio, 0.01, 1000);
	gluLookAt(8, 8, 8, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->Draw();
	}

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->DrawSelf();
	}

	glutSwapBuffers();
}

void GeneralUpdate(int value) {
	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->Update();
	}
	CalculateTime();
	glutTimerFunc(1000 / fps, GeneralUpdate, 0);
	glutPostRedisplay();
}

void KeyboardDown(unsigned char key, int x_y, int y_t) {
}

int main(int argc, char * args[]) {

	// Initializing
	glutInit(&argc, args);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GL_DEPTH_BUFFER_BIT);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(1920/2 - width/2, 1080 / 2 - height / 2);

	glutCreateWindow("Mistral Engine");

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	Instantiate(0);
	Instantiate(1);

	// Setting the loop functions
	glutDisplayFunc(GeneralDraw);

	glutTimerFunc(int(1000/fps), GeneralUpdate, 0);

	glutKeyboardFunc(KeyboardDown);

	glutMainLoop();

	return 0;
}