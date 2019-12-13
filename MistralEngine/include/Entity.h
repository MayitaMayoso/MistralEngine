#ifndef ENTITY_H 
#define ENTITY_H 

#include "Model.h"
#include "Program.h"

#include <iostream>
#include <string>
#include <typeinfo>

#pragma once

using namespace std;

class MistralEngine;

class Entity {
	public:
		Entity( MistralEngine* g ); // Class constructor. Initializes all the Entities built-in variables.
		~Entity();
		void DrawSelf(); // Draws the Entitys body. Position, scale and angle affects how the bodys is drawn.

		virtual void Create() {};
		virtual void Update() {}; // This method is called in the Timer Function of the main loop.

		virtual void LoadModel( string modelPath);

		// ------------------- Getters and Setters -----------------------
		bool visible = true;
		string get_name();
		unsigned int get_id();
		float get_x(), get_y(), get_z();
		float get_x_origin(), get_y_origin(), get_z_origin();
		float get_x_scale(), get_y_scale(), get_z_scale();
		float get_x_angle(), get_y_angle(), get_z_angle();
		float get_red(), get_green(), get_blue(), get_alpha();

		void set_position( float x_value, float y_value, float z_value ), set_x( float value ), set_y( float value ), set_z( float value );
		void set_origin(float x_value, float y_value, float z_value), set_x_origin( float value ), set_y_origin( float value ), set_z_origin( float value );
		void set_scale(float x_value, float y_value, float z_value), set_x_scale( float value ), set_y_scale( float value ), set_z_scale( float value );
		void set_angle(float x_value, float y_value, float z_value), set_x_angle( float value ), set_y_angle( float value ), set_z_angle( float value );
		void set_rgba(float r_value, float g_value, float b_value, float a_value), set_red( float value), set_green( float value), set_blue( float value), set_alpha( float value );

	protected:
		unsigned int id;
		float x, y, z;
		float x_origin, y_origin, z_origin;
		float x_scale, y_scale, z_scale;
		float x_angle, y_angle, z_angle;
		float red, green, blue, alpha;

		Model model;
		Program program;

		MistralEngine* game;
};
#endif