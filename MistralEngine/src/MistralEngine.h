#include <iostream>
#include <GL/glut.h>
#include <chrono>
#include <list>

#include "Entity.h"
#include "GameObjects.h"

# define PI 3.14159265358979323846

class MistralEngine {
public:
	MistralEngine();

	int Run(int argc, char* args[], MistralEngine* s);
	Entity* Instantiate(int ObjectType);
	float wave(float from, float to, float duration, float offset);

	static MistralEngine* self;

	static void setSelf(MistralEngine* s) { self = s;  };

private:
	void CalculateTime();

	virtual void GeneralUpdate(int value);
	virtual void GeneralDraw();

	static void UpdateCallback(int value) { self->GeneralUpdate(value); };
	static void DrawCallback() { self->GeneralDraw(); };

	int width, height, fov, fps;
	float AspectRatio;

	chrono::high_resolution_clock::time_point t0;
	int CurrentTime;

	unsigned int EntitiesCount;
	list<Entity*> EntitiesList;
};

int main(int argc, char* args[]) {
	MistralEngine *game = new MistralEngine();

	game->Run(argc, args, game);
}