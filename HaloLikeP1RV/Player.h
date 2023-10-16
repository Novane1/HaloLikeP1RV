#pragma once
#include "camera.h"
#include "Objet3D.h"
class Player : public Camera {
protected :
	Objet3D *player;
	glm::vec3 position;
public : 
	glm::vec3 getPosition();
	glm::vec3 setPosition(glm::vec3 v);
	void affichage(); 
};