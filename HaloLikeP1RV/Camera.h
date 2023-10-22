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
// D�finition de la classe cam�ra
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
	virtual void updateCamera();//Mettre les coordonn�es de notre objet camera dans la vrai cam�ra de la sc�ne
	virtual void goFrontCamera(float speed); // Augmente la coordonn�e Z  de la cam�ra de z 
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

