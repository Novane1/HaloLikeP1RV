#pragma once
#ifndef ¨Player_h
#define Player_h
#include "camera.h"
#include "Objet3D.h"
class Player : public Camera {
protected :
	Objet3D *player;
	glm::vec3 position;
public : 
	glm::vec3 getPosition();
	void setPosition(glm::vec3 v);
	void setPlayer(Objet3D *p);
	void affichage(); 
};

#endif