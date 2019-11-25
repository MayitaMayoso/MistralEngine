#include <iostream>
#include <string>

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
		double get_x(), get_y(), get_z();
		double get_x_origin(), get_y_origin(), get_z_origin();
		double get_x_scale(), get_y_scale(), get_z_scale();
		double get_x_angle(), get_y_angle(), get_z_angle();
		double get_red(), get_green(), get_blue();

		void set_name( string value );
		void set_x( double value ), set_y( double value ), set_z( double value );
		void set_x_origin( double value ), set_y_origin( double value ), set_z_origin( double value );
		void set_x_scale( double value ), set_y_scale( double value ), set_z_scale( double value );
		void set_x_angle( double value ), set_y_angle( double value ), set_z_angle( double value );
		void set_red( double value), set_green( double value), set_blue( double value);
		void set_target( Entity* t );
		

	protected:
		unsigned int id;
		string name;
		double x, y, z;
		double x_origin, y_origin, z_origin;
		double x_scale, y_scale, z_scale;
		double x_angle, y_angle, z_angle;
		double red, green, blue;

		MistralEngine* game;
		Entity* target;
};