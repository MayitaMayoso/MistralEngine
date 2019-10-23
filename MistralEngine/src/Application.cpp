#include <iostream>
#include <GL/glut.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include <Windows.h>

#include "Entity.h"

# define PI 3.14159265358979323846

using namespace std;

int width = 1280;
int height = 720;
float aspect_ratio = float(width) / float(height);
int fov = 60;
int fps = 60;

chrono::high_resolution_clock::time_point t0 = chrono::high_resolution_clock::now();
chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
chrono::duration<float> timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
int current_time = int(timer.count()*1000);

float xx = 1;
float yy = 1;
float zz = 1;
float angle = 0;
float dis = 8;
float spd = 0.4f;
Entity e;

float wave(float from, float to, float duration, float offset) {
	float A = float((to - from) * 0.5);
	float W = float(current_time * 0.001);

	return float(from + A + A * sin((2 * PI * W) / duration + offset));
}

void CalculateTime() {
	t1 = chrono::high_resolution_clock::now();
	timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
	current_time = int(timer.count() * 1000);
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

	gluLookAt(dis, dis, dis, 0, 0, 0, 0, 1, 0);

	glPushMatrix();

		e.DrawSelf();

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

	xx = wave(1, 3, 3, 0);
	yy = wave(1, 3, 3, 1);
	zz = wave(1, 3, 3, 2);
	angle += 2;

	CalculateTime();
	glutTimerFunc(1000 / fps, GeneralUpdate, 0);
	glutPostRedisplay();
}

void KeyboardDown(unsigned char key, int x_y, int y_t) {
	switch (key) {
		case 'w':
			e.set_x(e.get_x() - 1);
			break;
		case 's':
			e.set_x(e.get_x() + 1);
			break;
		case 'a':
			e.set_z(e.get_z() + 1);
			break;
		case 'd':
			e.set_z(e.get_z() - 1);
			break;
		case 'q':
			e.set_y(e.get_y() + 1);
			break;
		case 'e':
			e.set_y(e.get_y() - 1);
			break;
		case 'u':
			e.set_x_rotation(e.get_x_rotation() + 3);
			break;
		case 'j':
			e.set_x_rotation(e.get_x_rotation() - 3);
			break;
		case 'i':
			e.set_y_rotation(e.get_y_rotation() + 3);
			break;
		case 'k':
			e.set_y_rotation(e.get_y_rotation() - 3);
			break;
		case 'o':
			e.set_z_rotation(e.get_z_rotation() + 3);
			break;
		case 'l':
			e.set_z_rotation(e.get_z_rotation() - 3);
			break;
		case 'r':
			e.set_x_scale(e.get_x_scale() + 0.2);
			break;
		case 'f':
			e.set_x_scale(e.get_x_scale() - 0.2);
			break;
		case 't':
			e.set_y_scale(e.get_y_scale() + 0.2);
			break;
		case 'g':
			e.set_y_scale(e.get_y_scale() - 0.2);
			break;
		case 'y':
			e.set_z_scale(e.get_z_scale() + 0.2);
			break;
		case 'h':
			e.set_z_scale(e.get_z_scale() - 0.2);
			break;
	}


	//glutPostRedisplay();
}

int main(int argc, char * args[]) {

	glutInit(&argc, args);

	GeneralInitialize();

	glutDisplayFunc(GeneralDraw);

	glutTimerFunc(int(1000/fps), GeneralUpdate, 0);

	glutKeyboardFunc(KeyboardDown);

	glutMainLoop();

	return 0;
}