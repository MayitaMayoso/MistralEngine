#include "MistralEngine.h"
#include "Input.h"
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

void Camera::Create() {
	target = new Character(game);

	new Nanosuit(game);
}

void Camera::Update() {
	float spd = 0.2f;
	x = lerp(x, target->get_x(), spd);
	y = lerp(y, target->get_y()+1, spd);
	z = lerp(z, target->get_z()+3, spd);

	tx = lerp(x, target->get_x(), spd);
	ty = lerp(y, target->get_y()+1, spd);
	tz = lerp(z, target->get_z(), spd);

	// position, target, up
	game->cameraView =  glm::lookAt(glm::vec3(x, y, z), glm::vec3(tx, ty, tz), glm::vec3(0.0f, 1.0f, 0.0f));
}



void Character::Update() {
	int x_input = (int)game->input->InputCheck("RIGHT", InputState::HOLD) - (int)game->input->InputCheck("LEFT", InputState::HOLD);
	int z_input = -(int)game->input->InputCheck("UP", InputState::HOLD) + (int)game->input->InputCheck("DOWN", InputState::HOLD);
	int y_input = (int)game->input->InputCheck("FORWARD", InputState::HOLD) - (int)game->input->InputCheck("BACKWARD", InputState::HOLD);

	float dir1 = atan2( z_input, x_input );
	float z_adjusted = sin(dir1);

	float dir2 = atan2(y_input, z_input);
	float y_adjusted = sin(dir2);


	float x_adjusted = (x_input != 0) ? cos(dir1) : 0;

	x_spd = lerp(x_spd, max_spd * x_adjusted, acceleration);
	y_spd = lerp(y_spd, max_spd * y_adjusted, acceleration);
	z_spd = lerp(z_spd, max_spd * z_adjusted, acceleration);

	x += x_spd;
	y += y_spd;
	z += z_spd;
}