#include "MistralEngine.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"


using namespace std;

// ==================================================================
//    THESE METHODS SHOULD NOT BE OVERWRITTED ON AN INHERITED CLASS
// ==================================================================
Entity::Entity(MistralEngine* g) {
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

Entity::~Entity() {/*
	int pos = 0;
	for (Entity* e : game->EntitiesList) {
		if (e == this) break;
		pos++;
	}
	game->EntitiesList.erase(pos);*/
}

void Entity::DrawSelf() {
	if (visible) {
		program.use();	
		
		
		program.setVec3("lightColor",game->lightscene->getR() , game->lightscene->getG(), game->lightscene->getB());
		program.setVec3("lightPos", game->lightscene->getX(), game->lightscene->getY(), game->lightscene->getZ());
		program.setFloat("intensity", game->lightscene->getStrenght());
		program.setVec3("viewPos", game->camera->position); //posicion de la camara
		program.setInt("specularintensity", game->lightscene->getSpecularStrenght());


		// render the loaded model
		glm::mat4 modelMat = glm::mat4(1.0f);

		glm::mat4 localAxis = glm::mat4(1.0f);

		modelMat = glm::translate(modelMat, glm::vec3(x_origin, y_origin, z_origin)); // translate it down so it's at the center of the scene
		modelMat = glm::translate(modelMat, glm::vec3(x, y, z)); // translate it down so it's at the center of the scene

		/*
		localAxis = glm::rotate(localAxis, glm::radians(x_angle), glm::vec3(1.0f, 0.0f, 0.0f));
		localAxis = glm::rotate(localAxis, glm::radians(y_angle), glm::vec3(0.0f, 1.0f, 0.0f));
		localAxis = glm::rotate(localAxis, glm::radians(z_angle), glm::vec3(0.0f, 0.0f, 1.0f));*/

		modelMat = glm::rotate(modelMat, glm::radians(x_angle), glm::vec3(localAxis[0]));
		modelMat = glm::rotate(modelMat, glm::radians(y_angle), glm::vec3(localAxis[1]));
		modelMat = glm::rotate(modelMat, glm::radians(z_angle), glm::vec3(localAxis[2]));

		modelMat = glm::scale(modelMat, glm::vec3(x_scale, y_scale, z_scale));	// it's a bit too big for our scene, so scale it down

		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 1080.0f/ 720.0f, 0.1f, 100.0f);

		
		const std::string& name = "model";
		const std::string& nameCamera = "view";
		const std::string& nameZ = "projection";

		glProgramUniformMatrix4fv(program.getId(), glGetUniformLocation(program.getId(), name.c_str()), 1, GL_FALSE, &modelMat[0][0]);
		glProgramUniformMatrix4fv(program.getId(), glGetUniformLocation(program.getId(), nameCamera.c_str()), 1, GL_FALSE, &game->cameraView[0][0]);
		glProgramUniformMatrix4fv(program.getId(), glGetUniformLocation(program.getId(), nameZ.c_str()), 1, GL_FALSE, &projection[0][0]);

		model.Draw(program.getId());
	}
}

void Entity::LoadModel(string modelPath) {
	string vertexPath = "_resources/Shaders/vertex1.frag";
	string fragmentPath = "_resources/Shaders/fragment1.frag";
	modelPath = "_resources/Models/" + modelPath;
	program.load(vertexPath.c_str(), fragmentPath.c_str());
	model.create(modelPath.c_str());
}

// ==================================================================
//    THESE ARE THE GETTERS AND SETTERS OF THE ENTITY CLASS
// ==================================================================

// GETTERS

unsigned int Entity::get_id() { return id; }

string Entity::get_name() {
	string ctype = typeid(*this).name();
	int len = ctype.length();
	return ctype.substr(6, len);
}

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


// SETTERS

void Entity::set_position(float x_value, float y_value, float z_value) { x = x_value; y = y_value; z = z_value; }

void Entity::set_x( float value ) { x = value; }

void Entity::set_y( float value ) { y = value; }

void Entity::set_z( float value) { z = value; }


void Entity::set_origin(float x_value, float y_value, float z_value) { x_origin = x_value; y_origin = y_value; z_origin = z_value; }

void Entity::set_x_origin( float value ) { x_origin = value; }

void Entity::set_y_origin( float value ) { y_origin = value; }

void Entity::set_z_origin( float value ) { z_origin = value; }


void Entity::set_scale(float x_value, float y_value, float z_value) { x_scale = x_value; y_scale = y_value; z_scale = z_value; }

void Entity::set_x_scale( float value ) { x_scale = value; }

void Entity::set_y_scale( float value ) { y_scale = value; }

void Entity::set_z_scale( float value ) { z_scale = value; }


void Entity::set_angle(float x_value, float y_value, float z_value) { x_angle = x_value; y_angle = y_value; z_angle = z_value; }

void Entity::set_x_angle( float value ) { x_angle = value; }

void Entity::set_y_angle( float value ) { y_angle = value; }

void Entity::set_z_angle( float value ) { z_angle = value; }


void Entity::set_rgba(float r_value, float g_value, float b_value, float a_value) { red = r_value; green = g_value; blue = b_value; alpha = a_value;  }

void Entity::set_red( float value ) { red = value; }

void Entity::set_green( float value ) { green = value; }

void Entity::set_blue( float value ) { blue = value; }

void Entity::set_alpha(float value) { alpha = value; }