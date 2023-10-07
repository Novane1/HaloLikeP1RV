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

using namespace std;

void Camera::updateCamera()
{
	//On r�initialise
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Changement de position de la cam�ra
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

void Camera::updateRotation(GLdouble x, GLdouble y, GLdouble oldX, GLdouble oldY, GLdouble mouseSensitivityAngle, GLdouble& actualAngle){


	

	actualAngle += mouseSensitivityAngle * (x - oldX);

	camera_center_vector.x = camera_position.x + cos(actualAngle)*4;
	camera_center_vector.z = camera_position.z + sin(actualAngle)*4;
	
	cout << actualAngle << endl;

	this->updateCamera();
}




