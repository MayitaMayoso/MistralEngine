#include "MistralEngine.h"
#include "Scenario.h"
#include "GameObjects.h"
#include "Entity.h"

Scenario::Scenario(MistralEngine* g)
{
	game = g;

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
		Char character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Char>(c, character));
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

void Scenario::ReadScenario(string path)
{
	string str;
	string aux;
	string object;
	float x;
	float y;
	float z;

	name = path;

	ifstream file( "_resources/Scenarios/" + path);

	if (file.is_open())
	{

		while (std::getline(file, str))
		{
			std::istringstream is(str);
			int i = 0;
			while (getline(is, aux, '/'))
			{
				if (i == 0)
					object = aux;


				if (i == 1)
					x = std::stof(aux);
				if (i == 2)
					y = std::stof(aux);
				if (i == 3)
				{
					z = std::stof(aux);

					if (object == "Character")
					{
						Character* p = new Character(game);
						p->set_position(x, y, z);
					}

					if (object == "Skybox")
					{
						Skybox* p = new Skybox(game);
						p->set_position(x, y, z);
					}

					if (object == "Nanosuit")
					{
						Nanosuit* p = new Nanosuit(game);
						p->set_position(x, y, z);
					}

					if (object == "Universe")
					{
						Universe* p = new Universe(game);
						p->set_position(x, y, z);
					}

					if (object == "Planet")
					{
						Planet* p = new Planet(game);
						p->set_position(x, y, z);
					}

					if (object == "Planet2")
					{
						Planet2* p = new Planet2(game);
						p->set_position(x, y, z);
					}

					if (object == "Planet3")
					{
						Planet3* p = new Planet3(game);
						p->set_position(x, y, z);
					}

					if (object == "LevelPlanet")
					{
						LevelPlanet* p = new LevelPlanet(game);
						p->set_position(x, y, z);
					}

					if (object == "LevelPlanet2")
					{
						LevelPlanet2* p = new LevelPlanet2(game);
						p->set_position(x, y, z);
					}

					if (object == "LevelPlanet3")
					{
						LevelPlanet3* p = new LevelPlanet3(game);
						p->set_position(x, y, z);
					}

					if (object == "Intro")
					{
						Intro* p = new Intro(game);
						p->set_position(x, y, z);
					}


				}


				i++;

			}


		}
	}

}

void Scenario::ChangeScenario(string path) {
	room2change = true;
	nextRoom = path;
}

void Scenario::CheckAndChangeScenario() {
	if (room2change) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderText("Loading Screen", (game->width / 2) - 560.0f, game->height / 2, 1.0f, glm::vec3(0.10588f, 0.490196f, 0.921568f), 1.0f);
		glutSwapBuffers();

		for (Entity* e : game->EntitiesList) {
			e->Destroy();
			delete e;
		}

		game->EntitiesList.clear();

		room2change = false;

		ReadScenario(nextRoom);
	}
}

void Scenario::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, float opacity) {


	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	program.use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0, 0.0f));
	program.setMat4("model", model);



	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(game->width), 0.0f, static_cast<GLfloat>(game->height));
	//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)game->width / (float)game->height, 0.1f, 100.0f);
	program.setMat4("projection", projection);

	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, camZ));
	//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	//view = glm::lookAt(glm::vec3(0.0, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	program.setMat4("view", view);

	program.setFloat("opacity", opacity);
	glUniform3f(glGetUniformLocation(program.getId(), "textColor"), color.x, color.y, color.z);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterar por todos los caracteres
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Char ch = Characters[*c];

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