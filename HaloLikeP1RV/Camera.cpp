//Librairies
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include "Camera.h"
#include <iostream>
//#include "Vector3.h"
#include <GLFW/glfw3.h>
#include "rayon.h"
#include "glm/glm/gtc/type_ptr.hpp"
using namespace std;

void Camera::updateCamera()
{
	//gluLookAt(camera_position.x, /*camera_position.y*/ 0 , camera_position.z,
	//camera_center_vector.x, camera_center_vector.y, camera_center_vector.z,
	//camera_up_vector.x, camera_up_vector.y, camera_up_vector.z);
	//camera_position.y = 0;
	//viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);

	const float movementSpeed = 0.1f;
	const float rotationSpeed = 0.1f;

	// Get user input for camera movement and rotation
	// Update camera_position and camera_center_vector accordingly

	// Ensure the camera stays at a constant Y level
	camera_position.y = 0;

	// Limit the vertical viewing angle to avoid excessive tilting
	const float minVerticalAngle = -89.0f;
	const float maxVerticalAngle = 89.0f;

	glm::vec3 direction = camera_center_vector - camera_position;
	float distance = glm::length(direction);
	float pitch = glm::degrees(asin(direction.y / distance));
	pitch = glm::clamp(pitch, minVerticalAngle, maxVerticalAngle);

	direction = glm::rotate(direction, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	camera_center_vector = camera_position + direction;

	// Update the viewMatrix
	viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);
}



void Camera::goFrontCamera(float speed)
{
	glm::vec3 target = camera_position - camera_center_vector;// vector forward

	glm::normalize(target);// normalizing so we have just the direction 
	camera_position = camera_position + speed*target; // we go in the direction of the vector forward at the speed we chosed
	camera_center_vector = camera_center_vector + speed * target; // we change the target of the camera 
	this->updateCamera();
}

void Camera::goSideCamera(float speed)
{
	glm::vec3 target = camera_position - camera_center_vector; // vector forward
	glm::vec3 right = glm::cross(target, camera_up_vector); // we get the right vector of our camera
	camera_position = camera_position + speed * right; // we go in the direction of the vector forward at the speed we chosed
	camera_center_vector = camera_center_vector + speed * right; // we change the target of the camera 
	this->updateCamera();
}

Camera::Camera()
{
	camera_initial_position.x = 0;
	camera_initial_position.y = 0;
	camera_initial_position.z = 0;
	camera_position.x = 0;
	camera_position.y = 0;
	camera_position.z = 0;
	camera_center_vector.x = 0;
	camera_center_vector.y = 0;
	camera_center_vector.z = -4;
	camera_up_vector.y = 0;
	camera_up_vector.y = 1;
	camera_up_vector.z = 0;
	viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);
	actualAngleX = 3.141592 / 2;
	actualAngleY = 0;
	
}

void Camera::affichageUI(std::vector<bool> keys)
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Ui.affichage(keys);
	glPopMatrix();
}

void Camera::affichagePlayer()
{
	glPushMatrix();
	glTranslatef(camera_position.x - camera_initial_position.x-1, camera_position.y - camera_initial_position.y-1, camera_position.z - camera_initial_position.z-1);
	player.affichage();
	glPopMatrix();
}

void Camera::setPlayer(Player p)
{
	player = p;
}

void Camera::updateRotation(float xOffset,float yOffset, GLdouble mouseSensitivityAngle){


	actualAngleX += mouseSensitivityAngle * (xOffset);
	actualAngleY += mouseSensitivityAngle * (yOffset);

	if (actualAngleY >= 3.141592/2) {
		actualAngleY = 3.141592/2;
	}
	if (actualAngleY <= -3.141592/2) {
		actualAngleY = -3.141592/2;
	}

	camera_center_vector.x = camera_position.x + cos(actualAngleX) * 4; 
	camera_center_vector.z = camera_position.z + sin(actualAngleX) * 4;
	camera_center_vector.y = camera_position.y + sin(actualAngleY) * 4;
	/*cout << camera_center_vector.x << " " << camera_center_vector.z <<" " << camera_center_vector.y << endl;*/
	this->updateCamera();

	
	//cout << actualAngleX*360/2/ 3.141592 << " " << actualAngleY * 360 / 2 / 3.141592 << endl;

	
}

void Camera::updateViewMatrix()
{
	viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);
}

void Camera::setUI(UI o)
{
	Ui = o;
}

glm::vec3 Camera::getPosition()
{
	return camera_position;
}




