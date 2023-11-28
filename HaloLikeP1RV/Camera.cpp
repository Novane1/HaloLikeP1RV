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
	camera_initial_position.x = -5;
	camera_initial_position.y = 1.5;
	camera_initial_position.z = -5;
	camera_position.x = -5;
	camera_position.y = 1.5;
	camera_position.z = -5;
	camera_center_vector.x = -5;
	camera_center_vector.y = 1.5;
	camera_center_vector.z = -9;
	camera_up_vector.y = 0;
	camera_up_vector.y = 1;
	camera_up_vector.z = 0;
	viewMatrix = glm::lookAt(camera_position, camera_center_vector, camera_up_vector);
	actualAngleX = 3.141592 / 2;
	actualAngleY = 0;
	playerHealth = 1;
	isInvicibleActTime = 0;
	isInvicible = false;
	actFrame = 0;
	
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




float Camera::getHealth()
{
	return playerHealth;
}

void Camera::addY(float y)
{
	camera_position.y += y;
}

UI Camera::getUI()
{
	return Ui;
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
void Camera::goFrontCamera(float speed, vector<Objet3D*> otherCollider)
{
	glm::vec3 target = camera_position - camera_center_vector;// vector forward
	glm::normalize(target);// normalizing so we have just the direction 
	camera_position.x = camera_position.x + speed * target.x; // we go in the direction of the vector forward
	camera_position.z = camera_position.z + speed * target.z;
	camera_center_vector.x = camera_center_vector.x + speed * target.x; // we change the target of the camera 
	camera_center_vector.z = camera_center_vector.z + speed * target.z;
	for (Objet3D* it : otherCollider) 
	{
		if (this->isThereCollision(*it->getCollider(), it->getPos()))
		{
			camera_position.x = camera_position.x - speed * target.x; // we go in the direction of the vector forward
			camera_position.z = camera_position.z - speed * target.z;
			camera_center_vector.x = camera_center_vector.x - speed * target.x; // we change the target of the camera 
			camera_center_vector.z = camera_center_vector.z - speed * target.z;
			if (!isInvicible) { playerHealth -= 1; isInvicible = true; }
			return;
		}
	}
	return;
	
	
	//this->updateCamera();
}
void Camera::goSideCamera(float speed, vector<Objet3D*> otherCollider)
{
	glm::vec3 target = camera_position - camera_center_vector; // vector forward
	glm::vec3 right = glm::cross(target, camera_up_vector); // we get the right vector of our camera
	
	camera_position.x = camera_position.x + speed * right.x; // we go in the direction of the vector right
	camera_position.z = camera_position.z + speed * right.z; // we go in the direction of the vector right
	camera_center_vector.x = camera_center_vector.x + speed * right.x; // we change the target of the camera 
	camera_center_vector.z = camera_center_vector.z + speed * right.z;
	for (Objet3D* it : otherCollider)
	{
		if (this->isThereCollision(*it->getCollider(),it->getPos()))
		{
			
			camera_position.x = camera_position.x - speed * right.x; // we go in the direction of the vector right
			camera_position.z = camera_position.z - speed * right.z; // we go in the direction of the vector right
			camera_center_vector.x = camera_center_vector.x - speed * right.x; // we change the target of the camera 
			camera_center_vector.z = camera_center_vector.z - speed * right.z;
			if(!isInvicible){ playerHealth -= 1; isInvicible = true;}
			
			
			return;
		}
	}
	return;
}
void Camera::affichageUI(std::vector<bool> keys, std::vector<bool> mouseClick, Shader healthShader,Shader alphaShader)
{
	glPushMatrix();// On sauvegarde la matrice actuelle, vu que l'on veut effectuer des modifs de cette matrice seulement pour l'UI
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // On reset la matrice de vue à l'identité, comme ca on affichage par rapport à la caméra et les objets restent ainsi fixes par rapport à la caméra
	Ui.affichage(keys, mouseClick, healthShader,alphaShader,camera_position,camera_center_vector,playerHealth,actFrame);
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
	//cout << Ui.isShowedFunc()[i] << endl;
}
void Camera::setHealth(float h)
{
	playerHealth = h;
}
void Camera::setJump()
{
	if (!jump.getIsJumping()) {
		jump.setJump(10.0f,camera_position.y);
	}
}

void Camera::updateJump(float intersectiony)
{

	if (jump.getIsJumping())
	{
		
		jump.actualizeJump();
		
		if (intersectiony > (jump.getYCoord()-4.0) && jump.isGoingDown()) { // on est en dessous du navMesh
			jump.resetJump();
		}
		else { // on peut continuer à descendre
			// on remet bien la target de la caméra au bon endroit
			float delta = camera_position.y;
			camera_position.y = jump.getYCoord();
			delta = camera_position.y - delta;

			camera_center_vector.y += delta;

		}
		
	}
}

bool Camera::isJumping()
{
	return jump.getIsJumping();
}

void Camera::resetJump()
{
	jump.resetJump();
}

void Camera::setCollider(const char* filename)
{
	c.LoadCollider(filename);
}

void Camera::drawCollider()
{
	c.affichage();
}

bool Camera::isThereCollision(Collider collider,glm::vec3 posi)
{
	return c.checkCollision(collider,camera_position,posi);
}

void Camera::updateCheckInvicibility()
{
	if (isInvicible) 
	{ 
		if(isInvicibleActTime<=100)
		{
			isInvicibleActTime += 1;
		}
		else { isInvicibleActTime = 0; isInvicible = false; }
		
	}
}

void Camera::updateFrame()
{
	actFrame++;
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




