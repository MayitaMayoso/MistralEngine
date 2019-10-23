#include <iostream>
#include <GL/glut.h>
#include <chrono>
#include <list>
#include "Entity.h"

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

Entity * Instantiate() {
	Entity *e = new Entity(EntitiesCount);
	EntitiesList.push_back(e);
	EntitiesCount++;
	return e;
}

void CalculateTime() {
	t1 = chrono::high_resolution_clock::now();
	timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
	CurrentTime = int(timer.count() * 1000);
}

void GeneralInitialize() {

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(20, 20);//1920/2 - width/2, 1080 / 2 - height / 2);

	glutCreateWindow("Mistral Engine");

	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);

	gluPerspective(fov, aspect_ratio, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
}

void GeneralDraw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(8, 8, 8, 0, 0, 0, 0, 1, 0);

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->Draw();
	}

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->DrawSelf();
	}

	glPushMatrix();

		glBegin(GL_LINES);
			float lines_length = 10.0f;
			// Axis X (Red)
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(lines_length, 0.0f, 0.0f);

			// Axis Y (Green)
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, lines_length, 0.0f);

			// Axis Z (Blue)
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, lines_length);
		glEnd();

	glPopMatrix();
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

	for (int i = 0; i < 10; i++) {
		Entity *e = Instantiate();
		e->set_z(float(i));
	}



	glutInit(&argc, args);

	GeneralInitialize();

	glutDisplayFunc(GeneralDraw);

	glutTimerFunc(int(1000/fps), GeneralUpdate, 0);

	glutKeyboardFunc(KeyboardDown);

	glutMainLoop();

	return 0;
}