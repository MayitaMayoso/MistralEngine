#include "MistralEngine.h"
#include "Input.h"
#include "Camera.h"
#include "GameObjects.h"

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

	
}

void Planet::Update() {
	x = game->camera->position[0];
	y = game->camera->position[1];
	z = game->camera->position[2];
}