#pragma once
#include "Objet3D.h"
#include "Shader.h"
class PatternManager
{
protected:
	Objet3D* meteor;
	float t;
	bool isMeteorActive;
	glm::vec3 spawnPointMeteor;
	glm::vec3 finishPointMeteor;
public:
	PatternManager();
	void meteorAttack(glm::vec3 s, glm::vec3 f);
	void updateMeteor(Shader meteorShader, glm::vec3 camPos, glm::vec3 targetPos);
	void setMeteor(Objet3D * o);
	bool getIsActive();
	float getT();
	glm::vec3 getActivePoint();
};

