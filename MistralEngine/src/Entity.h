#ifndef ENTITY_H 
#define ENTITY_H 

#include <iostream>
#include <string>
#include "Model.h"
#include "Program.h"

#pragma once

using namespace std;

class MistralEngine;

class Entity {
	public:
		Entity( unsigned int identifier, MistralEngine* g ); // Class constructor. Initializes all the Entities built-in variables.
		void DrawSelf(); // Draws the Entitys body. Position, scale and angle affects how the bodys is drawn.

		virtual void Update() {}; // This method is called in the Timer Function of the main loop.
		virtual void Draw() {}; // This method is called on the Display Function of the main loop.
		virtual void DrawGUI() {}; // Currently not availabl  e.
		virtual void CameraUpdate() {};

		// ------------------- Getters and Setters -----------------------
		string get_name();
		unsigned int get_id();
		float get_x(), get_y(), get_z();
		float get_x_origin(), get_y_origin(), get_z_origin();
		float get_x_scale(), get_y_scale(), get_z_scale();
		float get_x_angle(), get_y_angle(), get_z_angle();
		float get_red(), get_green(), get_blue();

		void set_name( string value );
		void set_x( float value ), set_y( float value ), set_z( float value );
		void set_x_origin( float value ), set_y_origin( float value ), set_z_origin( float value );
		void set_x_scale( float value ), set_y_scale( float value ), set_z_scale( float value );
		void set_x_angle( float value ), set_y_angle( float value ), set_z_angle( float value );
		void set_red( float value), set_green( float value), set_blue( float value);
		void set_target( Entity* t );
		

	protected:
		unsigned int id;
		string name;
		float x, y, z;
		float x_origin, y_origin, z_origin;
		float x_scale, y_scale, z_scale;
		float x_angle, y_angle, z_angle;
		float red, green, blue;

		Model model;
		Program program;

		MistralEngine* game;
		Entity* target;
};
#endif