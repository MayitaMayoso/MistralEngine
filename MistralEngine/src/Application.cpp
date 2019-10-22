#include <iostream>
#include <GL/glut.h>
#include <ctime>
#include <ratio>
#include <chrono>

# define PI 3.14159265358979323846

using namespace std;

int width = 1280;
int height = 720;
float aspect_ratio = float(width) / float(height);
int fov = 60;
int fps = 10;

chrono::high_resolution_clock::time_point t0 = chrono::high_resolution_clock::now();
chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
chrono::duration<float> timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
int current_time = int(timer.count()*1000);

float dis = 0;

float wave(float from, float to, float duration, float offset) {
	float A = float((to - from) * 0.5);
	float W = float(current_time * 0.001);

	return float(from + A + A * sin((2 * PI * W) / duration + offset));
}

void UpdateCurrentTime() {
	t1 = chrono::high_resolution_clock::now();
	timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
	current_time = int(timer.count() * 1000);
}

void Initialize() {

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(1920/2 - width/2, 1080 / 2 - height / 2);

	glutCreateWindow("Mistral Engine");

	glClearColor(0, 0, 0, 1);

	gluPerspective(fov, aspect_ratio, 0.01, 100);

	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		glColor3f(0.5f, 0.5f, 0.5f);
		glPushMatrix();
			glTranslatef(dis, dis, -dis);
			glutWireTeapot(1);
		glPopMatrix();

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
		gluLookAt(200, 2, 2, 0, 0, 0, 0, 1, 0);
	glPopMatrix();
	glutSwapBuffers();
}

void Update(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000/fps, Update, 0);
	UpdateCurrentTime();
	dis = wave(-5, 5, 3, 0);
	cout << current_time << endl;
}

int main(int argc, char * args[]) {

	glutInit(&argc, args);

	Initialize();

	glutDisplayFunc(Draw);

	glutTimerFunc(int(1000/fps), Update, 0);

	glutMainLoop();

	return 0;
}