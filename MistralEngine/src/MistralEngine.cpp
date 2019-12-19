#define GLEW_STATIC
#include "GameObjects.h"
#include "MistralEngine.h"
#include "Scenario.h"
#include "Audio.h"
#include "AudioSource.h"
#include "Input.h"
#include "Light.h"
#include "Camera.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <glm.hpp>
#include <iostream>
#include <vector>

#include "Program.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ImageLoader.h"

using namespace std;

MistralEngine* MistralEngine::self = 0;

MistralEngine::MistralEngine() {
	// ------------- INITIALIZING THE ENGINE VARIABLES ---------------

	// VIEW VARIABLES
	width = 1280;
	height = 720;
	AspectRatio = float(width) / float(height);
	fov = glm::radians(50.0f);
	fps = 60;

	// TIMER VARIABLES
	t0 = chrono::high_resolution_clock::now();
	CurrentTime = 0;

	input = new Input();
}

unsigned int MistralEngine::EntitiesCount() {
	return EntitiesList.size();
}

GLint MistralEngine::getProgram(string name) {
	auto it = std::find_if(programs.begin(), programs.end(),
		[&name](const pair<string, GLint>& element) { return element.first == name; });

	return it->second;
}


float MistralEngine::wave(float from, float to, float duration, float offset) {
	float A = float((to - from) * 0.5);
	float W = float(CurrentTime * 0.001);

	return float(from + A + A * sin((2 * PI * W) / duration + offset));
}

void MistralEngine::CalculateTime() {
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	chrono::duration<float> timer = chrono::duration_cast<chrono::duration<float>>(t1 - t0);
	CurrentTime = int(timer.count() * 1000);
}

void MistralEngine::GeneralDraw() {

	glClearDepth(1.0f);

	if (ClearEnable)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov, AspectRatio, 0.001, 10000);

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
	// Update all the Input States
	input->UpdateInputs();
	//camera->UpdateCamera();

	// Draw all the entities
	for (Entity* e : EntitiesList) {
		e->Update();
	}

	CalculateTime();
	glutTimerFunc(1000 / fps, UpdateCallback, 0);
	glutPostRedisplay();
	scenario->CheckAndChangeScenario();
}

void MistralEngine::GeneralPressKeyboard(unsigned char key, int x, int y) {
	input->KeyboardPressHandle(toupper(key));
}

void MistralEngine::GeneralPressSpecial( int key, int x, int y) {
	input->KeyboardPressHandle(key);
}

void MistralEngine::GeneralPressGamepad( unsigned int key, int x, int y, int z) {
	cout << key << "	---	" << x << "	---	" << y << "	---	" << z << endl;
}

void MistralEngine::GeneralReleaseKeyboard(unsigned char key, int x, int y) {
	input->KeyboardReleaseHandle(toupper(key));
}

void MistralEngine::GeneralReleaseSpecial(int key, int x, int y) {
	input->KeyboardReleaseHandle(key);
}

void GLAPIENTRY MessageCallback(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar* message,const void* userParam)
{
	// Show OpenGL errors
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}



int MistralEngine::Run(int argc, char * args[], MistralEngine* s) {
	// Initializing
	glutInit(&argc, args);
	setSelf(s);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GL_DEPTH_BUFFER_BIT);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(1920/2 - width/2, 1080 / 2 - height / 2);

	glutCreateWindow("Mistral Engine");

	GLenum glewerror = glewInit();

	

	if (glewerror != GLEW_OK)
	{
		cerr << "GLEW initilization error: " << glewGetErrorString(glewerror) << endl;
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	
	
	//glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(MessageCallback, 0);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);

	glClearColor(.0f, .0f, .0f, 1.0f);

	lightscene = new Light(self);

	lightscene->SetR(1.0f);
	lightscene->SetG(1.0f);
	lightscene->SetB(1.0f);
	lightscene->SetX(0.0f);
	lightscene->SetY(0.0f);
	lightscene->SetZ(0.0f);
	lightscene->SetStrenght(1.0f);
	lightscene->SetSpecularStrenght(64);


	string vertexPath = "_resources/Shaders/vertex1.frag";
	string fragmentPath = "_resources/Shaders/fragment1.frag";
	programs.push_back(make_pair("model", Program(vertexPath.c_str(), fragmentPath.c_str()).getId()));


	scenario = new Scenario(self);
	scenario->ReadScenario("Intro.txt");
	
	camera = new Camera(self);

	// Setting the loop functions
	glutDisplayFunc(DrawCallback);

	glutTimerFunc(int(1000/fps), UpdateCallback, 0);

	glutKeyboardFunc(KeyboardPressCallback);
	glutSpecialFunc(SpecialPressCallback);
	glutJoystickFunc(GamepadPressCallback, 25);

	glutKeyboardUpFunc(KeyboardReleaseCallback);
	glutSpecialUpFunc(SpecialReleaseCallback);

	glutIgnoreKeyRepeat(1);

	glutMainLoop();

	return 0;
}


int main(int argc, char* args[]) {
	MistralEngine* game = new MistralEngine();

	game->Run(argc, args, game);
}