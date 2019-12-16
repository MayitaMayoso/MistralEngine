#ifndef GAME_OBJECTS_H 
#define GAME_OBJECTS_H

#include "Entity.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <gtc/type_ptr.hpp>
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
		glBufferData(GL_ARRAY_BUFFER, NUM_STARS * sizeof(star_t), NULL, GL_DYNAMIC_DRAW);

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

	float opacity = 1.0;
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

class Intro : public Entity {
public:

	Intro(MistralEngine* g) : Entity(g) { Create(); };

	void Create() {
		audio.setListenerData(0.0, 0.0, 0.0);
		audioBuffer = audio.loadSound("_resources/Audios/starwars2.wav");
		program.load("_resources/Shaders/text_vertex.frag", "_resources/Shaders/text_fragment.frag");

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		FT_Face face;
		if (FT_New_Face(ft, "_resources/Fonts/STARWARS.ttf", 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Cargar primeros 128 bytes del codigo ascii
		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Poner opciones de texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Guardar caracter para usar mas tarde
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		// Al acabar destruir
		FT_Done_Face(face);
		FT_Done_FreeType(ft);


		// Configurar VAO/VBO para las texturas
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


	}
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, float opacity)
	{
		program.setFloat("opacity", opacity);
		glUniform3f(glGetUniformLocation(program.getId(), "textColor"), color.x, color.y, color.z);

		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// Iterar por todos los caracteres
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			GLfloat xpos = x + ch.Bearing.x * scale;
			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			GLfloat w = ch.Size.x * scale;
			GLfloat h = ch.Size.y * scale;
			// Actualizar VBO para cada caracter
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Renderizar caracter sobre quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Ahora avanzar cursor al nuevo caracter
			x += (ch.Advance >> 6)* scale;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Update();
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
	"see the movie playing some,", "see you today at the cinema."};

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