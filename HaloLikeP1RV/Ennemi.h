#pragma once

#include <Windows.h>
#include "Objet3D.h"
#include "rayon.h"
#include "PatternManager.h"
class Ennemi : public Objet3D
{
protected:
	float damage; // dégats de l'ennemi
	float health; // vie de l'ennemi
	rayon snap;
	int damageFrame;
	bool isInvicible;
	glm::vec3 ourPos;

public:
	static vector<Ennemi*> listEnnemi;
	//Setters
	void setHealth(float h);
	//Getters
	float getHealth();
	int getDamageFrame();
	//Contructeurs
	Ennemi(float d, float h);

	//Fonctions
	float addHealth(float h); // soustraire h de health
	bool isShot(glm::vec3 pos, glm::vec3 dir);
	void startDamageAnimation();
	void increaseDamageFrame();
	void resetDamageAnimation();
	//destructor
	virtual ~Ennemi();
};