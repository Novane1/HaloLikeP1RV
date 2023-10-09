//Librairies

#include "windows.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/gl.h>
#include <glut.h>
#include "Camera.h"
#include "Vector3.h"
#include <GLFW/glfw3.h>

using namespace std;

void Camera::updateCamera()
{
	//On réinitialise
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Changement de position de la caméra
	gluLookAt(camera_position.x, camera_position.y, camera_position.z,
		camera_center_vector.x, camera_center_vector.y, camera_center_vector.z,
		camera_up_vector.x, camera_up_vector.y, camera_up_vector.z);
	/*cout << "a";*/
}



void Camera::goFrontCamera(float speed)
{
	
	camera_position.z = camera_position.z + speed;
	camera_center_vector.z = camera_center_vector.z + speed;
	this->updateCamera();
	
	
}

void Camera::goSideCamera(float speed)
{
	camera_position.x = camera_position.x + speed;
	camera_center_vector.x = camera_center_vector.x + speed;
	this->updateCamera();
}

Camera::Camera()
{
	camera_position.x = 0;
	camera_position.y = 0;
	camera_position.z = 4;
	camera_center_vector.x = 0;
	camera_center_vector.y = 0;
	camera_center_vector.z = 0;
	camera_up_vector.y = 0;
	camera_up_vector.y = 1;
	camera_up_vector.z = 0;
}

void Camera::updateRotation(GLdouble x, GLdouble y, GLdouble oldX, GLdouble oldY, GLdouble mouseSensitivityAngle, GLdouble& actualAngleX, GLdouble& actualAngleY){


	actualAngleX += mouseSensitivityAngle * (x - oldX);
	camera_center_vector.x = camera_position.x + cos(actualAngleX)*4; // le 4, c'est la distance de la caméra à l'endroit où elle regarde
	camera_center_vector.z = camera_position.z + sin(actualAngleX)*4;
	
	actualAngleY += mouseSensitivityAngle * (y- oldY);
	

	camera_center_vector.y = camera_position.y + sin(actualAngleY) * 4;
	camera_center_vector.z = camera_position.z + cos(actualAngleY) * 4;
	/*cout << camera_center_vector.x << " " << camera_center_vector.z <<" " << camera_center_vector.y << endl;*/
	this->updateCamera();

	
	//cout << actualAngleX*360/2/ 3.141592 << " " << actualAngleY * 360 / 2 / 3.141592 << endl;

	
}




