using namespace std;

class MistralEngine;

class Entity;

class Camera {
public:
	Camera(MistralEngine* g);

	void UpdateCamera();

	void SetTarget( Entity* t );

	void zoom(float zoom_factor);
	void pan(float pan_factorX, float pan_factorY, float pan_factorZ);
	void rotate(glm::vec3 rotation_center, float angle_X_inc, float angle_Y_inc);

	glm::vec3 position = glm::vec3(0.0f, 1.0f, 5.0f);
	glm::vec3 lookat = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);


private:
	Entity* target;
	MistralEngine* game;

	glm::mat4x4 view_matrix;

	float spd = 0.3f;
};