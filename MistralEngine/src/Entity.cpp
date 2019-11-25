#include "MistralEngine.h"
#include "Entity.h"


using namespace std;

// ==================================================================
//    THESE METHODS SHOULD NOT BE OVERWRITTED ON AN INHERITED CLASS
// ==================================================================
Entity::Entity(MistralEngine* g) {
	name = "";
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	x_origin = 0.0f;
	y_origin = 0.0f;
	z_origin = 0.0f;
	x_scale = 1.0f;
	y_scale = 1.0f;
	z_scale = 1.0f;
	x_angle = 0.0f;
	y_angle = 0.0f;
	z_angle = 0.0f;
	red = 1;
	green = 1;
	blue = 1;

	game = g;


	id = g->EntitiesList.size();
	game->EntitiesCount();

	g->EntitiesList.push_back(this);
}

void Entity::LoadModel(string modelPath, string vertexPath, string fragmentPath) {
	if (!visible) {
		program.create(vertexPath.c_str(), fragmentPath.c_str());
		model.create(modelPath.c_str());
		visible = true;
	}
}

void Entity::DrawSelf() {
	if (visible) {
		program.use();

		// render the loaded model
		glm::mat4 modelMat = glm::mat4(4.0f);
		modelMat = glm::scale(modelMat, glm::vec3(x_scale, y_scale, z_scale));	// it's a bit too big for our scene, so scale it down
		modelMat = glm::rotate(modelMat, glm::degrees(x_angle), glm::vec3(1.0f, 0.0f, 0.0f));
		modelMat = glm::rotate(modelMat, glm::degrees(y_angle), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMat = glm::rotate(modelMat, glm::degrees(z_angle), glm::vec3(0.0f, 0.0f, 1.0f));
		modelMat = glm::translate(modelMat, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene
		modelMat = glm::translate(modelMat, glm::vec3(x_origin, y_origin, z_origin)); // translate it down so it's at the center of the scene
		program.setMat4("model", modelMat);
		model.Draw(program);
	}
}


// ==================================================================
//    THESE ARE THE GETTERS AND SETTERS OF THE ENTITY CLASS
// ==================================================================

string Entity::get_name() { return name; }

unsigned int Entity::get_id() { return id; }

float Entity::get_x() { return x; }

float Entity::get_y() { return y; }

float Entity::get_z() { return z; }

float Entity::get_x_origin() { return x_origin; }

float Entity::get_y_origin() { return y_origin; }

float Entity::get_z_origin() { return z_origin; }

float Entity::get_x_scale() { return x_scale; }

float Entity::get_y_scale() { return y_scale; }

float Entity::get_z_scale() { return z_scale; }

float Entity::get_x_angle() { return x_angle; }

float Entity::get_y_angle() { return y_angle; }

float Entity::get_z_angle() { return z_angle; }

float Entity::get_red() { return red; }

float Entity::get_green() { return green; }

float Entity::get_blue() { return blue; }

float Entity::get_alpha() { return alpha; }

void Entity::set_name(string value) { name = value; }

void Entity::set_x( float value ) { x = value; }

void Entity::set_y( float value ) { y = value; }

void Entity::set_z( float value) { z = value; }

void Entity::set_x_origin( float value ) { x_origin = value; }

void Entity::set_y_origin( float value ) { y_origin = value; }

void Entity::set_z_origin( float value ) { z_origin = value; }

void Entity::set_x_scale( float value ) { x_scale = value; }

void Entity::set_y_scale( float value ) { y_scale = value; }

void Entity::set_z_scale( float value ) { z_scale = value; }

void Entity::set_x_angle( float value ) { x_angle = value; }

void Entity::set_y_angle( float value ) { y_angle = value; }

void Entity::set_z_angle( float value ) { z_angle = value; }

void Entity::set_red( float value ) { red = value; }

void Entity::set_green( float value ) { green = value; }

void Entity::set_blue( float value ) { blue = value; }

void Entity::set_alpha(float value) { alpha = value; }