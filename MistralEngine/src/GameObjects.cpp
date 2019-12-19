#include "MistralEngine.h"
#include "Input.h"
#include "Camera.h"
#include "GameObjects.h"
#include "Scenario.h"

float approach(float a, float b, float amount) {
	if (a < b) {
		float shift = a + amount;
		return (shift > b) ? b : shift;
	} else {
		float shift = a - amount;
		return (shift < b) ? b : shift;
	}
}

float lerp(float a, float b, float amount) {
	return a + (b - a) * amount;
}

float distance( float x1, float y1, float z1, float x2, float y2, float z2) {
	float xx = x2 - x1;
	float yy = y2 - y1;
	float zz = z2 - z1;
	return sqrt(xx*xx + yy*yy + zz*zz);
}

int sign(float value) {
	if (value == 0) {
		return 0;
	} else {
		return (value > 0) ? 1 : -1;
	}
}

void Character::Update() {
	int r_input = (int)game->input->InputCheck("LEFT", InputState::HOLD) - (int)game->input->InputCheck("RIGHT", InputState::HOLD);
	int f_input = (int)game->input->InputCheck("BACKWARD", InputState::HOLD) - (int)game->input->InputCheck("FORWARD", InputState::HOLD);
	int v_input = (int)game->input->InputCheck("UP", InputState::HOLD) - (int)game->input->InputCheck("DOWN", InputState::HOLD);

	float cx = game->camera->position[0];
	float cy = game->camera->position[1];
	float cz = game->camera->position[2];

	if (game->scenario->name == "Scenario.txt") {
		ry_spd = lerp(ry_spd, max_rspd * r_input, acceleration);

		y_spd = lerp(y_spd, max_spd * v_input, acceleration);
		spd = lerp(spd, max_spd * f_input, acceleration);

		y_angle += ry_spd;
		//x_angle += rx_spd;

		x_spd = spd * sin(glm::radians(y_angle));
		z_spd = spd * cos(glm::radians(y_angle));

		x += x_spd;
		y += y_spd;
		z += z_spd;

		game->camera->lookat = glm::vec3(x, y + 0.1f, z);

		float radius = 0.5f;
		float ncx = x + radius * sin(glm::radians(y_angle));
		float ncy = y + 0.1f;
		float ncz = z + radius * cos(glm::radians(y_angle));

		game->camera->position = glm::vec3(lerp(cx, ncx, 0.1), lerp(cy, ncy, 0.1), lerp(cz, ncz, 0.1));

		game->cameraView = glm::lookAt(game->camera->position, game->camera->lookat, glm::vec3(0.0f, 1.0f, 0.0f));

		for (Entity* e : game->EntitiesList) {
			if (e->get_name() == "Planet") {
				float dist = distance(e->get_x(), e->get_y(), e->get_z(), x, y, z);
				if (dist < 1.1) {
					game->scenario->ChangeScenario("RedPlanet.txt");
				}
			} else {
				if (e->get_name() == "Planet2") {
					float dist = distance(e->get_x(), e->get_y(), e->get_z(), x, y, z);
					if (dist < 1.1) {
						game->scenario->ChangeScenario("Naboo.txt");
					}
				} else {
					if (e->get_name() == "Planet3") {
						float dist = distance(e->get_x(), e->get_y(), e->get_z(), x, y, z);
						if (dist < 1.1) {
							game->scenario->ChangeScenario("Tatooine.txt");
						}
					}
				}
			}
		}

	} else {
		if (game->input->InputCheck("SHOOT", InputState::PRESSED)) {
			game->scenario->ChangeScenario("Scenario.txt");
		}

		x_spd = lerp(x_spd, max_spd * -r_input, acceleration*10);
		z_spd = lerp(z_spd, max_spd * f_input, acceleration*10);

		x += x_spd;
		z += z_spd;

		game->camera->lookat = glm::vec3(x, y, z);

		game->camera->position = glm::vec3(lerp(cx, x, 0.1), lerp(cy, y+2, 0.1), lerp(cz, z, 0.1));
		game->cameraView = glm::lookAt(game->camera->position, game->camera->lookat, glm::vec3(0.0f, 0.0f, -1.0f));
	}
}

void Skybox::Update() {
	x = game->camera->position[0];
	y = game->camera->position[1];
	z = game->camera->position[2];
}

void Universe::Create() {
	game->ClearEnable = false;
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

void Universe::Destroy() {
	game->ClearEnable = true;
}

void Universe::Update() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const GLfloat one[] = { 1.0f };
	glm::mat4 proj_matrix = glm::perspective(50.0f,
		(float)game->width / (float)game->height, 0.1f, 1000.0f);
	
	t = (float)game->CurrentTime;

	if (game->input->InputCheck("FORWARD", InputState::HOLD) || game->input->InputCheck("BACKWARD", InputState::HOLD))
		t *= 0.005f;
	else
		t *= 0.0001f;

	t -= floor(t);

	//game->CurrentTime

	glViewport(0, 0, game->width, game->height);
	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, one);

	glBindTexture(GL_TEXTURE_2D, star_texture);


	program.setFloat("time", t);
	program.setMat4("proj_matrix", proj_matrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glBindVertexArray(star_vao);


	//glEnable(GL_PROGRAM_POINT_SIZE);
	glDrawArrays(GL_POINTS, 0, NUM_STARS);
	glDisable(GL_BLEND);

}

void Intro::Create() {
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

void Intro::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, float opacity) {
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

void Intro::Draw() {
	if (visible) {

		if (game->input->InputCheck("UP", InputState::PRESSED)) {
			game->scenario->ChangeScenario("Scenario.txt");
		}

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

		if (!firstAudioLoaded && loadAudio) {
			source->playSound(audioBuffer);
			loadAudio = false;
			firstAudioLoaded = true;
		}

		switch (step) {
		case 1:
			variable -= 0.005;
			renderText("A long time ago in a galaxy far, far away...", (game->width / 2) - 560.0f, game->height / 2, 1.0f, glm::vec3(0.10588f, 0.490196f, 0.921568f), variable);
			if (variable <= 0) {
				step = 2;
				variable = 4.0f;
			}
			break;
		case 2:
			if (!loadAudio)
				loadAudio = true;

			variable -= 0.005;
			renderText("MISTRAL", (game->width / 2) - variable * 100, game->height / 2 + (variable * 20), variable, glm::vec3(0.90588f, 0.68235f, 0.0196f), 1.0f);
			renderText("ENGINE", (game->width / 2) - variable * 92, game->height / 2 - (variable * 20), variable, glm::vec3(0.90588f, 0.68235f, 0.0196f), 1.0f);
			if (variable <= 0) {
				step = 3;
			}
			break;
		case 3:
			variable += 1.23f;
			position = 0.0f + variable;
			nextLine = 50.0f;
			for (int i = 0; i < (sizeof(history) / sizeof(*history)); i++)
				renderText(history[i], (game->width / 2) - (history[i].size() * 13), position = position - nextLine, 1.0f, glm::vec3(0.90588f, 0.68235f, 0.0196f), 1.0f);

			if (position > game->height) {
				game->scenario->ChangeScenario("scenario.txt");
			}
			break;
		}
	}
}

void Nanosuit::Update() {
	for (Entity* e : game->EntitiesList) {
		if (e->get_name() == "Character") {
			float ex = e->get_x();
			float ez = e->get_z();

			int x_input = sign(ex - x);
			int z_input = sign(ez - z);

			if (distance(x, 0, z, ex, 0, ez) < 0.1) {
				x_input = 0;
				z_input = 0;
			}

			x_spd = lerp(x_spd, max_spd * x_input, acceleration);
			z_spd = lerp(z_spd, max_spd * z_input, acceleration);

			y_angle = glm::degrees(-atan2( ez - z, ex - x) + 90);

			x += x_spd;
			z += z_spd;
		}
	}
}