#pragma once
#include "Objet3D.h"
#include "ShootBar.h"

class ReloadManager
{

protected:
	Objet3D orb;
	Shader orbShader;
	ShootBar *shoot;
	bool isActive;
	glm::vec3 pos;
	float time;
	vector<vraiFace> faces;
public:
	void spawnOrb();
	ReloadManager(Objet3D o, Shader s, vector<vraiFace> f, ShootBar* sh);
	void actTime(glm::vec3 camPos, glm::vec3 camTarget);
	bool isIn(glm::vec3 playerPos);
	void affichage(glm::vec3 camPos,glm::vec3 camTarget);
};

