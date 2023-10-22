#pragma once
#ifndef ¨Player_h
#define Player_h

#include "Objet3D.h"

class Player  {
protected :
	Objet3D player;
	glm::vec3 position;
public : 
	glm::vec3 getPosition();
	void setPosition(glm::vec3 v);

	void setPlayer(Objet3D p);
	
	void affichage();
	Player();
};

#endif