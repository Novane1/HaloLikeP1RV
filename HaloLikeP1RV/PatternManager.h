#pragma once
#include "Objet3D.h"
class PatternManager
{
protected:
	Objet3D meteor;
	float timeMeteor;
	bool isMeteorActive;
	glm::vec3 spawnPointMeteor;
	glm::vec3 finishPointMeteor;
public:
	void meteorAttack();
	void updateMeteor();
};

