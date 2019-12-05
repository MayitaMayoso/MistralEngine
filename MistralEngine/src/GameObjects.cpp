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
	int h_input = (int)game->input->InputCheck("LEFT", InputState::HOLD) - (int)game->input->InputCheck("RIGHT", InputState::HOLD);
	int f_input = (int)game->input->InputCheck("BACKWARD", InputState::HOLD) - (int)game->input->InputCheck("FORWARD", InputState::HOLD);
	int m_input = (int)game->input->InputCheck("UP", InputState::HOLD) - (int)game->input->InputCheck("DOWN", InputState::HOLD);

	ry_spd = lerp(ry_spd, max_rspd * h_input, acceleration);
	rx_spd = lerp(rx_spd, max_rspd * f_input, acceleration);
	spd = lerp(spd, max_spd * m_input, acceleration);

	//spd = lerp(spd, max_spd * f_input, acceleration);

	y_angle += ry_spd;
	x_angle += rx_spd;

	x_spd = spd * game->camera->front[0];
	y_spd = spd * game->camera->front[1];
	z_spd = spd * game->camera->front[2];

	cout << game->camera->front[0] << endl;

	x += x_spd;
	y += y_spd;
	z += z_spd;

	game->camera->rotate(glm::vec3(x, y, z), ry_spd, rx_spd);
	game->camera->position += glm::vec3(x_spd, y_spd, z_spd);

	glm::mat4 origin = glm::mat4(1.0f);
	glm::mat4 localAxis = glm::mat4(1.0f);

	origin = glm::rotate(origin, glm::radians(x_angle), glm::vec3(localAxis[0]));
	origin = glm::rotate(origin, glm::radians(y_angle), glm::vec3(localAxis[1]));
	origin = glm::rotate(origin, glm::radians(z_angle), glm::vec3(localAxis[2]));

	game->camera->lookat = glm::vec3(x, y, z);
}

void Planet::Update() {
	x = game->camera->position[0];
	y = game->camera->position[1];
	z = game->camera->position[2];
}