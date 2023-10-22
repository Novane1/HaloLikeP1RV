#pragma once
#ifndef Camera_h
#define Camera_h

//Librairies
#include <GL/gl.h>

/*#ifndef APIENTRY
#define APIENTRY
#endif*/

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "UI.h"
#include "Player.h"
using namespace std;
// Définition de la classe caméra
class Camera {
	glm::vec3 camera_position;
	glm::vec3 camera_up_vector;
	glm::vec3 camera_center_vector;
	glm::mat4 viewMatrix;
	glm::vec3 camera_initial_position;
	GLdouble actualAngleX ;
	GLdouble actualAngleY ;
	UI Ui;
	Player player;
	
public :
	virtual void updateCamera();//Mettre les coordonnées de notre objet camera dans la vrai caméra de la scène
	virtual void goFrontCamera(float speed); // Augmente la coordonnée Z  de la caméra de z 
	virtual void goSideCamera(float speed);
	virtual void updateRotation(float xOffset, float yOffset, GLdouble mouseSensitivityAngle);
	virtual void updateViewMatrix();
	virtual void setUI(UI o);
	virtual glm::vec3 getPosition();
	virtual void affichageUI(std::vector<bool> keys);
	virtual void affichagePlayer();
	virtual void setPlayer(Player p);

	Camera();
};

#endif

