//Librairies

#include "windows.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/gl.h>
#include <glut.h>
#include "Camera.h"
//#include "Vector3.h"
#include <GLFW/glfw3.h>

using namespace std;

void Camera::updateCamera()
{
	
	

	gluLookAt(camera_position.x, camera_position.y, camera_position.z,
		camera_center_vector.x, camera_center_vector.y, camera_center_vector.z,
		camera_up_vector.x, camera_up_vector.y, camera_up_vector.z);
	viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);
	
}



void Camera::goFrontCamera(float speed)
{
	
	
	glm::vec3 target =  camera_position - camera_center_vector;// vector forward
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
}

void Camera::updateRotation(float xOffset,float yOffset, GLdouble mouseSensitivityAngle, GLdouble& actualAngleX, GLdouble& actualAngleY){


	actualAngleX += mouseSensitivityAngle * (xOffset);
	actualAngleY += mouseSensitivityAngle * (yOffset);

	if (actualAngleY >= 3.141592/2) {
		actualAngleY = 3.141592/2;
	}
	if (actualAngleY <= -3.141592/2) {
		actualAngleY = -3.141592/2;
	}

	camera_center_vector.x = camera_position.x + cos(actualAngleX) * 4; // le 4, c'est la distance de la caméra à l'endroit où elle regarde
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

glm::vec3 Camera::getPosition()
{
	return camera_position;
}




