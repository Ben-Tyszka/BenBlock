#pragma once
class Camera
{
public:
	Camera();
	void TranslateCamera(glm::vec3 tran);
	void LookAt(double xm, double ym);

	void MoveForward();
	void MoveBackwards();
	void MoveLeft();
	void MoveRight();

	glm::mat4 Projection, View;

	glm::vec3 lookDir = glm::vec3(0.0f, 0.0f, 0.0f);

	float x = 4, y = 3, z = 3;
	float lx = 0, ly = 0;
private:
	float speed = 0.04f;
	float lookSpeed = 0.0027f;
	float horizontalAngle = 0.0f;
	float verticalAngle = 0.0f;
};

