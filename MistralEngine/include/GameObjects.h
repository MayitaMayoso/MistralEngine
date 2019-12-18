#ifndef GAME_OBJECTS_H 
#define GAME_OBJECTS_H

#include "Entity.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Audio.h"
#include "AudioSource.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

class Character : public Entity {
public:

	Character(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("aircraft/aircraft.obj");
		set_scale(0.04, 0.04, 0.04);
	}

	void Update();

	float max_spd = 0.06f;
	float max_rspd = 1.0f;
	float x_spd = 0.0f;
	float y_spd = 0.0f;
	float z_spd = 0.0f;
	float rx_spd = 0.0f;
	float ry_spd = 0.0f;
	float rz_spd = 0.0f;
	float spd = 0.0f;
	float acceleration = 0.01f;
};

class Skybox : public Entity {
public:

	Skybox(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("skybox/moon.obj");
		//set_scale(0.01, 0.01, 0.01);
	}

	void Update();
};

class Nanosuit : public Entity {
public:

	Nanosuit(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("gman/Ork_1.obj");
		set_scale(0.001, 0.0012, 0.001);
	}

	void Update();

	int hp = 100;

	float max_spd = 0.02f;
	float max_rspd = 1.0f;
	float x_spd = 0.0f;
	float z_spd = 0.0f;
	float r_spd = 0.0f;
	float spd = 0.0f;
	float acceleration = 0.3f;
};

class Universe : public Entity {
public:

	Universe(MistralEngine* g) : Entity(g) { Create(); };

	void Create();

	void Destroy();

	float randomFloat()
	{
		float res;
		unsigned int tmp;

		seed *= 16807;

		tmp = seed ^ (seed >> 4) ^ (seed << 15);

		*((unsigned int*)&res) = (tmp >> 9) | 0x3F800000;

		return (res - 1.0f);
	}

	void Update();
private:
	bool initialized = false;
	bool moving = false;

	GLuint star_texture;
	GLuint star_vao;
	GLuint star_buffer;
	unsigned int seed = 0x13371337;
	float t = (float)glutGet(GLUT_ELAPSED_TIME);

	enum
	{
		NUM_STARS = 8000
	};

};

class Planet : public Entity {
public:

	Planet(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("moon/moon.obj");
		set_scale(0.02, 0.024, 0.02);
	}
};

class Planet2 : public Entity {
public:

	Planet2(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("Planet2/Mercury 1K.obj");
		set_scale(0.02, 0.024, 0.02);
	}
};

class Planet3 : public Entity {
public:

	Planet3(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("Planet3/Mars 2K.obj");
		//LoadModel("Planet2/Mercury 1K.obj");
		set_scale(0.02, 0.024, 0.02);
	}
};

class LevelPlanet : public Entity {
public:

	LevelPlanet(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("naboo/naboo.obj");
		set_scale(1, 0.03, 1);
	}
};

class LevelPlanet2 : public Entity {
public:

	LevelPlanet2(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("tatooine/tatooine.obj");
		set_scale(1, 0.03, 1);
	}
};

class LevelPlanet3 : public Entity {
public:

	LevelPlanet3(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("redsurface/redsurface.obj");
		set_scale(1, 0.03, 1);
	}
};

class Intro : public Entity {
public:

	Intro(MistralEngine* g) : Entity(g) { Create(); };

	void Create();
	void Draw();

	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, float opacity);
private:
	bool visible = true;
	bool moving = false;

	struct Character {
		GLuint TextureID; // Id de la textura
		glm::ivec2 Size; // Tamano del texto
		glm::ivec2 Bearing; // Offset de arriba a abajo del texto
		GLuint Advance; // Offset hacia la derecha del texto
	};

	std::map<GLchar, Character> Characters;

	GLuint VAO;
	GLuint VBO;

	std::string history[25] = { "Mistral Engine", "Episode I","Creating the motor", "", "After much effort and sweat",
	" our engineers have developed", "   a functional graphic engine." , "Taking advantage of the death" ,
	"of the supreme leader Snoke," , "   will use the engine to fight " ,
	"the new order throughout" , "the galaxy." , "","You are the protagonist and", "you must fly the spaceship.", "It is time to destroy",
	"all the bases of the", "first order, end the Sith", "forces and bring peace back", " to the galaxy ...", "", "Feed your hype to",
	"see the movie playing some,", "see you today at the cinema." };

	int step = 1;
	float variable = 1.0f;
	float position = 0.0f;
	float nextLine = 50.0f;
	bool loadAudio = false;
	bool firstAudioLoaded = false;

	Audio audio;
	int audioBuffer;
	AudioSource* source = new AudioSource;
};

#endif