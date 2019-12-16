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

void Character::Update() {
	int r_input = (int)game->input->InputCheck("LEFT", InputState::HOLD) - (int)game->input->InputCheck("RIGHT", InputState::HOLD);
	int f_input = (int)game->input->InputCheck("BACKWARD", InputState::HOLD) - (int)game->input->InputCheck("FORWARD", InputState::HOLD);
	int v_input = (int)game->input->InputCheck("UP", InputState::HOLD) - (int)game->input->InputCheck("DOWN", InputState::HOLD);

	float cx = game->camera->position[0];
	float cy = game->camera->position[1];
	float cz = game->camera->position[2];

	if (game->scenario->name != "Game.txt") {
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
				if (dist < 2) {
					game->scenario->ChangeScenario("Game.txt");
				}
			}
		}

	} else {
		x_spd = lerp(x_spd, max_spd * -r_input, acceleration*10);
		z_spd = lerp(z_spd, max_spd * f_input, acceleration*10);

		x += x_spd;
		z += z_spd;

		game->camera->lookat = glm::vec3(x, y, z);

		game->camera->position = glm::vec3(lerp(cx, x, 0.05), lerp(cy, y+2, 0.1), lerp(cz, z, 0.05));
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