#include <string>

#pragma once

using namespace std;

class Entity
{
	public:
		Entity();
		~Entity();
		void DrawSelf();
		void Initialize();
		void Destroy();
		void Update();
		void Draw();
		void DrawGUI();

		string get_name();
		float get_x(), get_y(), get_z();
		float get_x_origin(), get_y_origin(), get_z_origin();
		float get_x_scale(), get_y_scale(), get_z_scale();
		float get_x_rotation(), get_y_rotation(), get_z_rotation();

		void set_name( string value );
		void set_x( float value ), set_y( float value ), set_z( float value );
		void set_x_origin( float value ), set_y_origin( float value ), set_z_origin( float value );
		void set_x_scale( float value ), set_y_scale( float value ), set_z_scale( float value );
		void set_x_rotation( float value ), set_y_rotation( float value ), set_z_rotation( float value );

	private:
		string name;
		float x, y, z;
		float x_origin, y_origin, z_origin;
		float x_scale, y_scale, z_scale;
		float x_rotation, y_rotation, z_rotation;
		float red, green, blue;

};

