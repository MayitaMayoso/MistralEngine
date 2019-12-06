#ifndef GAME_OBJECTS_H 
#define GAME_OBJECTS_H

#include "Entity.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

class Character : public Entity {
public:

	Character(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("aircraft/aircraft.obj");
		//y_origin = -8.0f;
		x_scale = 0.4f;
		y_scale = 0.4f;
		z_scale = 0.4f;
	}

	void Update();

	float max_spd = 0.2f;
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

class Planet : public Entity {
public:

	Planet(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {

		LoadModel("moon/moon.obj");
	}

	void Update();
};

class Nanosuit : public Entity {
public:

	Nanosuit(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("link/pose.obj");
	}
};

/*
class Spaceship : public Entity {
public:

	Spaceship(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		LoadModel("aircraft/aircraft.obj");
	}
};
*/

class Universe : public Entity {
public:

	Universe(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		program.load("_resources/Shaders/universe_vertex.frag", "_resources/Shaders/universe_fragment.frag");

		glGenTextures(1, &star_texture);
		glBindTexture(GL_TEXTURE_2D, star_texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		int width, height, nrChannels;
		unsigned char* data = stbi_load("_resources/Textures/tx_wall.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		glGenVertexArrays(1, &star_vao);
		glBindVertexArray(star_vao);



		struct star_t
		{
			glm::vec3     position;
			glm::vec3     color;
		};

		glGenBuffers(1, &star_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, star_buffer);
		glBufferData(GL_ARRAY_BUFFER, NUM_STARS * sizeof(star_t), NULL, GL_STATIC_DRAW);

		star_t* star = (star_t*)glMapBufferRange(GL_ARRAY_BUFFER, 0, NUM_STARS * sizeof(star_t), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		int i;

		for (i = 0; i < 1000; i++)
		{
			star[i].position[0] = (randomFloat() * 2.0f - 1.0f) * 100.0f;
			star[i].position[1] = (randomFloat() * 2.0f - 1.0f) * 100.0f;
			star[i].position[2] = randomFloat();
			star[i].color[0] = 0.8f + randomFloat() * 0.2f;
			star[i].color[1] = 0.8f + randomFloat() * 0.2f;
			star[i].color[2] = 0.8f + randomFloat() * 0.2f;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(star_t), NULL);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(star_t), (void*)sizeof(glm::vec3));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


	}

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

#endif