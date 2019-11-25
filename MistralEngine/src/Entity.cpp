#include "MistralEngine.h"
#include "Entity.h"

using namespace std;

// ==================================================================
//    THESE METHODS SHOULD NOT BE OVERWRITTED ON AN INHERITED CLASS
// ==================================================================
Entity::Entity( unsigned int identidier, MistralEngine* g) {
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
	x_angle = 0;
	y_angle = 0;
	z_angle = 0;
	red = 1;
	green = 1;
	blue = 1;

	game = g;
}

void Entity::DrawSelf() {
	glPushMatrix();
		glColor3f(red, green, blue);
		glTranslatef(x_origin, y_origin, z_origin);
		glTranslatef(x, y, z);
		glRotatef(x_angle, 1, 0, 0);
		glRotatef(y_angle, 0, 1, 0);
		glRotatef(z_angle, 0, 0, 1);
		glScalef(x_scale, y_scale, z_scale);
	glPopMatrix();
}


// ==================================================================
//    THESE ARE THE GETTERS AND SETTERS OF THE ENTITY CLASS
// ==================================================================

string Entity::get_name() { return name; }

unsigned int Entity::get_id() { return id; }

double Entity::get_x() { return x; }

double Entity::get_y() { return y; }

double Entity::get_z() { return z; }

double Entity::get_x_origin() { return x_origin; }

double Entity::get_y_origin() { return y_origin; }

double Entity::get_z_origin() { return z_origin; }

double Entity::get_x_scale() { return x_scale; }

double Entity::get_y_scale() { return y_scale; }

double Entity::get_z_scale() { return z_scale; }

double Entity::get_x_angle() { return x_angle; }

double Entity::get_y_angle() { return y_angle; }

double Entity::get_z_angle() { return z_angle; }

double Entity::get_red() { return red; }

double Entity::get_green() { return green; }

double Entity::get_blue() { return blue; }

void Entity::set_name(string value) { name = value; }

void Entity::set_x( double value ) { x = value; }

void Entity::set_y( double value ) { y = value; }

void Entity::set_z( double value) { z = value; }

void Entity::set_x_origin( double value ) { x_origin = value; }

void Entity::set_y_origin( double value ) { y_origin = value; }

void Entity::set_z_origin( double value ) { z_origin = value; }

void Entity::set_x_scale( double value ) { x_scale = value; }

void Entity::set_y_scale( double value ) { y_scale = value; }

void Entity::set_z_scale( double value ) { z_scale = value; }

void Entity::set_x_angle( double value ) { x_angle = value; }

void Entity::set_y_angle( double value ) { y_angle = value; }

void Entity::set_z_angle( double value ) { z_angle = value; }

void Entity::set_red( double value ) { red = value; }

void Entity::set_green( double value ) { green = value; }

void Entity::set_blue( double value ) { blue = value; }

void Entity::set_target( Entity* t ) { target = t; }