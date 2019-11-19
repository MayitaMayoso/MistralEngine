#include "MistralEngine.h"

using namespace std;

MistralEngine* MistralEngine::self = 0;

MistralEngine::MistralEngine() {
	// ------------- INITIALIZING THE ENGINE VARIABLES ---------------

	// VIEW VARIABLES
	width = 1280;
	height = 720;
	AspectRatio = float(width) / float(height);
	fov = 60;
	fps = 60;

	// TIMER VARIABLES
	t0 = chrono::high_resolution_clock::now();
	CurrentTime = 0;

	// INSTANCES VARIABLES
	EntitiesCount = 0;
}

float MistralEngine::wave(float from, float to, float duration, float offset) {
	float A = float((to - from) * 0.5);
	float W = float(CurrentTime * 0.001);

	return float(from + A + A * sin((2 * PI * W) / duration + offset));
}

Entity * MistralEngine::Instantiate( int ObjectType ) {
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

void MistralEngine::CalculateTime() {
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	chrono::duration<float> timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
	CurrentTime = int(timer.count() * 1000);
}

void MistralEngine::GeneralDraw() {

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, AspectRatio, 0.01, 1000);
	gluLookAt(8, 8, 8, 0, 0, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->DrawSelf();
	}

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->Draw();
	}

	glutSwapBuffers();
}
void MistralEngine::GeneralUpdate(int value) {
	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->Update();
	}
	CalculateTime();
	glutTimerFunc(1000 / fps, UpdateCallback, 0);
	glutPostRedisplay();
}


int MistralEngine::Run(int argc, char * args[], MistralEngine* s) {
	setSelf(s);
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
	glutDisplayFunc(DrawCallback);

	glutTimerFunc(int(1000/fps), UpdateCallback, 0);

	glutMainLoop();

	return 0;
}