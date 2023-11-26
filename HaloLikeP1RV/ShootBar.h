#pragma once
#include "Shader.h"
class ShootBar
{
protected :
	float amo;
	float numAmoMax;
public : 
	ShootBar();
	void affichage();
	void downAmo();
	void resetAmo();
	float getAmo();

};

