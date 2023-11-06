#pragma once

#include <Windows.h>
#include "Objet3D.h"
class Ennemi : public Objet3D
{
protected:
	float damage; // dégats de l'ennemi
	float health; // vie de l'ennemi
public:
	static vector<Ennemi*> listEnnemi;
	//Setters
	//Getters
	//Contructeurs
	Ennemi(float d, float h);
	//Fonctions
};