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
#include "Physics.h"
#include "rayon.h"
#include "Collider.h"
using namespace std;
// Définition de la classe caméra
class Camera {
	glm::vec3 camera_position;
	glm::vec3 camera_up_vector;
	glm::vec3 camera_center_vector;
	glm::mat4 viewMatrix;
	glm::vec3 camera_initial_position;
	int playerHealth;
	int actFrame;
	GLdouble actualAngleX ;
	GLdouble actualAngleY ;
	UI Ui;
	Player player;
	Physics jump;
	Collider c;
	bool isInvicible;
	int isInvicibleActTime;


	
public :
	
	// CONSTRUCTEURS
	Camera();

	// GETTERS
	virtual glm::vec3 getPosition();
	virtual glm::vec3 getTarget();
	virtual float getHealth();
	virtual UI getUI();
	// SETTERS
	virtual void sethauteur(glm::vec3 inter, float hauteur);
	virtual void setUI(UI o);
	virtual void setPlayer(Player p);
	virtual void addY(float y);
	virtual void setHealth(float h);
	// METHODES
	virtual void updateCamera();//Mettre les coordonnées de notre objet camera dans la vrai caméra de la scène
	virtual void goFrontCamera(float speed, vector<Objet3D*> otherCollider); // Augmente la coordonnée Z  de la caméra de z 
	virtual void goSideCamera(float speed, vector<Objet3D*> otherCollider);
	virtual void updateRotation(float xOffset, float yOffset, GLdouble mouseSensitivityAngle);
	virtual void updateViewMatrix();
	virtual void affichageUI(std::vector<bool> keys, std::vector<bool> mouseClick, Shader healthShader);
	virtual void affichagePlayer();
	virtual void changeState(bool b, int i);// change l'état d'un élément de l'UI de notre caméra
	virtual void setJump();
	virtual void updateJump(float intersectiony);
	virtual bool isJumping();
	virtual void resetJump();
	virtual void setCollider(const char* filename);
	virtual void drawCollider();
	virtual bool isThereCollision(Collider collider,glm::vec3 posi);
	virtual void updateCheckInvicibility();
	virtual void updateFrame();
};

#endif

