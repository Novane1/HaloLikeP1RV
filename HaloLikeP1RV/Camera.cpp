//Librairies
#include <windows.h>
#include <glad/glad.h>
#include <glut.h>
#include "Camera.h"
#include <iostream>
//#include "Vector3.h"
#include "glm/glm/gtc/type_ptr.hpp"
#include "rayon.h"

using namespace std;

// Constructeur de base
Camera::Camera()
{
	camera_initial_position.x = 0;
	camera_initial_position.y = 1.5;
	camera_initial_position.z = 0;
	camera_position.x = 0;
	camera_position.y = 1.5;
	camera_position.z = 0;
	camera_center_vector.x = 0;
	camera_center_vector.y = 1.5;
	camera_center_vector.z = -4;
	camera_up_vector.y = 0;
	camera_up_vector.y = 1;
	camera_up_vector.z = 0;
	viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);
	actualAngleX = 3.141592 / 2;
	actualAngleY = 0;
	
}

// GETTERS
glm::vec3 Camera::getTarget()
{
	return camera_center_vector;
}

// SETTERS
void Camera::setPlayer(Player p)
{
	player = p;
}

void Camera::addY(float y)
{
	camera_position.y += y;
}

void Camera::sethauteur(glm::vec3 inter, float hauteur)
{
	float delta = camera_position.y;
	camera_position.y = inter.y + hauteur;
	delta = camera_position.y - delta;

	camera_center_vector.y += delta;
	//this->updateCamera();
}

// METHODES
void Camera::updateCamera()
{
	gluLookAt(camera_position.x, camera_position.y, camera_position.z,
		camera_center_vector.x, camera_center_vector.y, camera_center_vector.z,
		camera_up_vector.x, camera_up_vector.y, camera_up_vector.z);
	viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);
	//camera_position.y = 0;
}
void Camera::goFrontCamera(float speed)
{
	glm::vec3 target = camera_position - camera_center_vector;// vector forward
	glm::normalize(target);// normalizing so we have just the direction 
	camera_position.x = camera_position.x + speed * target.x; // we go in the direction of the vector forward
	camera_position.z = camera_position.z + speed * target.z;
	camera_center_vector.x = camera_center_vector.x + speed * target.x; // we change the target of the camera 
	camera_center_vector.z = camera_center_vector.z + speed * target.z;
	//this->updateCamera();
}
void Camera::goSideCamera(float speed)
{
	glm::vec3 target = camera_position - camera_center_vector; // vector forward
	glm::vec3 right = glm::cross(target, camera_up_vector); // we get the right vector of our camera
	
	camera_position.x = camera_position.x + speed * right.x; // we go in the direction of the vector right
	camera_position.z = camera_position.z + speed * right.z; // we go in the direction of the vector right
	camera_center_vector.x = camera_center_vector.x + speed * right.x; // we change the target of the camera 
	camera_center_vector.z = camera_center_vector.z + speed * right.z;
	//this->updateCamera();
}
void Camera::affichageUI(std::vector<bool> keys, std::vector<bool> mouseClick)
{
	glPushMatrix();// On sauvegarde la matrice actuelle, vu que l'on veut effectuer des modifs de cette matrice seulement pour l'UI
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // On reset la matrice de vue à l'identité, comme ca on affichage par rapport à la caméra et les objets restent ainsi fixes par rapport à la caméra
	Ui.affichage(keys, mouseClick);
	glPopMatrix();// On reprend la matrice qui était présente avant l'affichage de l'UI
}
void Camera::affichagePlayer()
{
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(camera_position.x - camera_initial_position.x-1, camera_position.y - camera_initial_position.y-1, camera_position.z - camera_initial_position.z-1);
	player.affichage();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void Camera::changeState(bool b, int i)
{
	Ui.changeState(b, i);
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
	//this->updateCamera();

	
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




