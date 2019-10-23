#include "Entity.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

// ================================================================
//    THESE METHODS SHOULD BE OVERWRITTED ON AN INHERITED CLASS
// ================================================================
void Entity::Initialize() {}

void Entity::Destroy() {}

void Entity::Update() {}

void Entity::Draw() {}

void Entity::DrawGUI() {}

// ==================================================================
//    THESE METHODS SHOULD NOT BE OVERWRITTED ON AN INHERITED CLASS
// ==================================================================
Entity::Entity( unsigned int identidier ) {
	id = identidier;

	name = "";
	x = 0;
	y = 0;
	z = 0;
	x_origin = 0;
	y_origin = 0;
	z_origin = 0;
	x_scale = 1;
	y_scale = 1;
	z_scale = 1;
	x_rotation = 0;
	y_rotation = 0;
	z_rotation = 0;
	red = 1;
	green = 1;
	blue = 1;

	Initialize();
}

Entity::~Entity() {
	Destroy();
}

void Entity::DrawSelf() {
	glPushMatrix();
		glColor3f(red, green, blue);
		glTranslatef(x_origin, y_origin, z_origin);
		glTranslatef(x, y, z);
		glRotatef(x_rotation, 1, 0, 0);
		glRotatef(y_rotation, 0, 1, 0);
		glRotatef(z_rotation, 0, 0, 1);
		glScalef(x_scale, y_scale, z_scale);
		glutWireTeapot(1);
	glPopMatrix();
}


// ==================================================================
//    THESE ARE THE GETTERS AND SETTERS OF THE ENTITY CLASS
// ==================================================================

string Entity::get_name() { return name; }

float Entity::get_x() { return x; }

float Entity::get_y() { return y; }

float Entity::get_z() { return z; }

float Entity::get_x_origin() { return x_origin; }

float Entity::get_y_origin() { return y_origin; }

float Entity::get_z_origin() { return z_origin; }

float Entity::get_x_scale() { return x_scale; }

float Entity::get_y_scale() { return y_scale; }

float Entity::get_z_scale() { return z_scale; }

float Entity::get_x_rotation() { return x_rotation; }

float Entity::get_y_rotation() { return y_rotation; }

float Entity::get_z_rotation() { return z_rotation; }

void Entity::set_name(string value) { name = value; }

void Entity::set_x( float value ) { x = value; }

void Entity::set_y( float value ) { y = value; }

void Entity::set_z( float value) { z = value; }

void Entity::set_x_origin( float value) { x_origin = value; }

void Entity::set_y_origin( float value) { y_origin = value; }

void Entity::set_z_origin( float value) { z_origin = value; }

void Entity::set_x_scale( float value) { x_scale = value; }

void Entity::set_y_scale( float value) { y_scale = value; }

void Entity::set_z_scale( float value) { z_scale = value; }

void Entity::set_x_rotation( float value) { x_rotation = value; }

void Entity::set_y_rotation( float value) { y_rotation = value; }

void Entity::set_z_rotation( float value) { z_rotation = value; }