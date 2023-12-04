#pragma once
#include "Objet3D.h"
#include "Shader.h"
class PatternManager
{
protected:
	Objet3D* meteor;
	float t;
	float speed;
	bool isMeteorActive;
	glm::vec3 spawnPointMeteor;
	glm::vec3 finishPointMeteor;
public:
	PatternManager(Objet3D* m);
	void meteorAttack(glm::vec3 s, glm::vec3 f);
	void updateMeteor(Shader meteorShader, glm::vec3 camPos, glm::vec3 targetPos,float multiply = 1.0f);
	void setMeteor(Objet3D * o);
	bool getIsActive();
	glm::vec3 getMetPos();
	float getT();
	glm::vec3 getActivePoint();
	void addSpeed(float s);
	void setSpeed(float s);
};

