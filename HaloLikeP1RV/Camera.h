#pragma once
#ifndef Camera_h
#define Camera_h

//Librairies
#include <glad/glad.h>

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
	
	// CONSTRUCTEURS
	Camera();

	// GETTERS
	virtual glm::vec3 getPosition();
	virtual glm::vec3 getTarget();

	// SETTERS
	virtual void sethauteur(glm::vec3 inter, float hauteur);
	virtual void setUI(UI o);
	virtual void setPlayer(Player p);
	virtual void addY(float y);
	// METHODES
	virtual void updateCamera();//Mettre les coordonn�es de notre objet camera dans la vrai cam�ra de la sc�ne
	virtual void goFrontCamera(float speed); // Augmente la coordonn�e Z  de la cam�ra de z 
	virtual void goSideCamera(float speed);
	virtual void updateRotation(float xOffset, float yOffset, GLdouble mouseSensitivityAngle);
	virtual void updateViewMatrix();
	virtual void affichageUI(std::vector<bool> keys, std::vector<bool> mouseClick);
	virtual void affichagePlayer();
	virtual void changeState(bool b, int i);// change l'�tat d'un �l�ment de l'UI de notre cam�ra
	

	
};

#endif

