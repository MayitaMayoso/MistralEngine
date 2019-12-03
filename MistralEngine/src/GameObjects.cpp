#include "MistralEngine.h"
#include "Input.h"
#include "GameObjects.h"

void Axis::Draw() {
	glPushMatrix();
	GLUquadric* qobj = gluNewQuadric();
	float radius = float(0.1);
	float clen = float(0.5);
	float crad = float(0.2);

	// Axis X (Red)
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRotatef(90, 0, 1, 0);
	gluCylinder(qobj, radius, radius, length, 10, 1);
	glTranslatef(0, 0, length);
	glutSolidCone(crad, clen, 10, 10);
	glPopMatrix();

	// Axis Y (Green)
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, radius, radius, length, 10, 1);
	glTranslatef(0, 0, length);
	glutSolidCone(crad, clen, 10, 10);
	glPopMatrix();

	// Axis Z (Blue)
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	gluCylinder(qobj, radius, radius, length, 10, 1);
	glTranslatef(0, 0, length);
	glutSolidCone(crad, clen, 10, 10);
	glPopMatrix();

	// White sphere
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.3, 10, 10);
	glPopMatrix();
	glPopMatrix();
}

void SkyBox::Draw() {
	glPushMatrix();
	glColor3d(skyRed, skyGreen, skyBlue);
	glutSolidSphere(skyRadius, 10, 10);
	glPopMatrix();
}

void Camera::Create() {
	target = new SpaceShip(game);
	set_position(20, 20, 20);

	cout << get_name();
}

void Camera::CameraUpdate() {
	// position, target, up
	game->cameraView =  glm::lookAt(glm::vec3(x, y, z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//game->cameraView =  glm::lookAt(glm::vec3(x, y, z), glm::vec3(target->get_x(), target->get_y(), target->get_z()), glm::vec3(0.0f, 1.0f, 0.0f));
	//gluLookAt(x, y, z, target->get_x(), target->get_y(), target->get_z(), 0, 1, 0);
}

void SpaceShip::Update() {
	y_rot += spd;
	z_rot += spd*0.5;

	x = float(radius * sin(y_rot));
	z = float(radius * cos(y_rot));
	y = float(radius * sin(z_rot));

	z_angle += 2;
	y_angle += 2;
	z_angle += 2;
}

void SpaceShip::Draw() {

	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslatef(x_origin, y_origin, z_origin);
	glTranslatef(x, y, z);
	glRotatef(x_angle, 1, 0, 0);
	glRotatef(y_angle, 0, 1, 0);
	glRotatef(z_angle, 0, 0, 1);
	glScalef(x_scale, y_scale, z_scale);
	glutSolidCube(2);
	glColor3f(0, 0, 0);
	glutWireCube(2);
	glPopMatrix();
}

void Planet::Update() {
	z_angle += spd;
	x_angle = 110;
}

void Planet::Draw() {
	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslatef(x_origin, y_origin, z_origin);
	glTranslatef(x, y, z);
	glRotatef(x_angle, 1, 0, 0);
	glRotatef(y_angle, 0, 1, 0);
	glRotatef(z_angle, 0, 0, 1);
	glScalef(x_scale, y_scale, z_scale);
	glColor3d(planetR, planetG, planetB);
	glutSolidSphere(planetRadius, 20, 20);
	glColor3f(0, 0, 0);
	glutWireSphere(planetRadius, 20, 20);
	glPopMatrix();
}

void Stars::Draw() {
	if (!initialized) {
		for (int i = 0; i < starsNumber; i++) {
			starsPos[i][0] = rand() % 900 - 450;
			starsPos[i][1] = rand() % 900 - 450;
			starsPos[i][2] = rand() % 900 - 450;
		}

		initialized = true;
	} else {
		glBegin(GL_POINTS);
		for (int i = 0; i < starsNumber; i++) {
			glColor3f(1, 1, 1);
			glPointSize(5.0f);
			glVertex3i(starsPos[i][0], starsPos[i][1], starsPos[i][2]);
		}
		glEnd();
	}
}

void Character::Update() {
	if (game->input->InputCheck("UP", InputState::HOLD)) {
		y += 1;
	}


	if (game->input->InputCheck("DOWN", InputState::HOLD)) {
		y -= 1;
	}

	if (game->input->InputCheck("RIGHT", InputState::HOLD)) {
		x += 1;
	}


	if (game->input->InputCheck("LEFT", InputState::HOLD)) {
		x -= 1;
	}

	if (game->input->InputCheck("FORWARD", InputState::HOLD)) {
		z += 1;
	}


	if (game->input->InputCheck("BACKWARD", InputState::HOLD)) {
		z -= 1;
	}
}