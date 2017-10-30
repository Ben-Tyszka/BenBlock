#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	Projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);
	View = glm::lookAt(
		glm::vec3(x, y, z),
		glm::vec3(lx, ly, 0),
		glm::vec3(0, 1, 0)
	);
}

void Camera::TranslateCamera(glm::vec3 tran)
{
	View = glm::lookAt(
		tran,
		glm::vec3(lx, ly, 0),
		glm::vec3(0, 1, 0));
	this->x = tran.x;
	this->y = tran.y;
	this->z = tran.z;
}

void Camera::LookAt(double xm, double ym)
{
	horizontalAngle = 0.0f;
	verticalAngle = 0.0f;
	horizontalAngle += lookSpeed * float(1280 / 2 - xm);
	verticalAngle += lookSpeed* float(720 / 2 - ym);
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	View = glm::lookAt(
		glm::vec3(x, y, z),
		glm::vec3(x, y, z) + direction,
		glm::vec3(0, 1, 0));

	this->lx = direction.x;
	this->ly = direction.y;
	this->lookDir = direction;
}

void Camera::MoveForward()
{
	glm::vec3 pos = glm::vec3(x, y, z);
	pos += this->lookDir * speed;
	View = glm::lookAt(pos, lookDir, glm::vec3(0, 1, 0));
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
}
void Camera::MoveBackwards()
{
	glm::vec3 pos = glm::vec3(x, y, z);
	pos -= this->lookDir * speed;
	View = glm::lookAt(pos, lookDir, glm::vec3(0, 1, 0));
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
}
void Camera::MoveLeft()
{
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	glm::vec3 pos = glm::vec3(x, y, z);
	pos -= right * speed;
	View = glm::lookAt(pos, lookDir, glm::vec3(0, 1, 0));
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
}

void Camera::MoveRight()
{
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	glm::vec3 pos = glm::vec3(x, y, z);
	pos += right * speed;
	View = glm::lookAt(pos, lookDir, glm::vec3(0, 1, 0));
	this->x = pos.x;
	this->y = pos.y;
	this->z = pos.z;
}
