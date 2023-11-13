#pragma once

#include <Windows.h>
#include "Objet3D.h"
#include "rayon.h"
class Ennemi : public Objet3D
{
protected:
	float damage; // dégats de l'ennemi
	float health; // vie de l'ennemi
	rayon snap;
public:
	static vector<Ennemi*> listEnnemi;
	//Setters
	void setHealth(float h);
	//Getters
	float getHealth();
	//Contructeurs
	Ennemi(float d, float h);

	//Fonctions
	float addHealth(float h); // soustraire h de health
	bool isShot(glm::vec3 pos, glm::vec3 dir);

	//destructor
	virtual ~Ennemi();
};