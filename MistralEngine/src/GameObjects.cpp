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


void Character::Update() {
	int r_input = (int)game->input->InputCheck("LEFT", InputState::HOLD) - (int)game->input->InputCheck("RIGHT", InputState::HOLD);
	int f_input = (int)game->input->InputCheck("BACKWARD", InputState::HOLD) - (int)game->input->InputCheck("FORWARD", InputState::HOLD);
	int v_input = (int)game->input->InputCheck("UP", InputState::HOLD) - (int)game->input->InputCheck("DOWN", InputState::HOLD);

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

	game->camera->lookat = glm::vec3(x, y + 1.0f, z);

	float radius = 5.0f;
	float ncx = x + radius * sin(glm::radians(y_angle));
	float ncy = y + 1;
	float ncz = z + radius * cos(glm::radians(y_angle));
	float cx = game->camera->position[0];
	float cy = game->camera->position[1];
	float cz = game->camera->position[2];

	game->camera->position = glm::vec3(lerp(cx, ncx, 0.1), lerp(cy, ncy, 0.1), lerp(cz, ncz, 0.1));

	// generate view matrix
	game->cameraView = glm::lookAt(game->camera->position, game->camera->lookat, glm::vec3(0.0f, 1.0f, 0.0f));

	if (game->input->InputCheck("UP", InputState::HOLD)) {
		game->scenario->ChangeScenario("scenario.txt");
	}
}

void Planet::Update() {
	x = game->camera->position[0];
	y = game->camera->position[1];
	z = game->camera->position[2];
}

void Universe::Update() {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const GLfloat one[] = { 1.0f };
	glm::mat4 proj_matrix = glm::perspective(50.0f, (float)game->width / (float)game->height, 0.1f, 1000.0f);

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

void Intro::Update() {
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

		if (position > game->height)
			cout << "END INTRO" << endl;
		break;
	}
}