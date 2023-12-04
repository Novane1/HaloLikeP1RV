#include "PatternManager.h"

PatternManager::PatternManager(Objet3D* m)
{
	isMeteorActive = false;
	meteor = m;
	speed = 1;
	spawnPointMeteor = glm::vec3(50);
	finishPointMeteor = glm::vec3(50);
	meteor->setPos(glm::vec3(50));
	t = 0;
}

void PatternManager::meteorAttack(glm::vec3 s, glm::vec3 f)
{
	t = 0;
	spawnPointMeteor = s;
	finishPointMeteor = f;
	isMeteorActive = true;
}

void PatternManager::updateMeteor(Shader meteorShader, glm::vec3 camPos,glm::vec3 targetPos, float multiply )
{
	if (isMeteorActive) {
		if (t < 1) {
			t += 0.005*speed*multiply;
			meteor->setPos(spawnPointMeteor * (1 - t) + finishPointMeteor * t);
			meteor->affichageShaderOffset(meteorShader, camPos, targetPos, glm::vec3(0, 1, 0), meteor->getPos());
		}
		else {
			t = 0;
			isMeteorActive = false;
			meteor->setPos(glm::vec3(50));
		}
	}
}

void PatternManager::setMeteor(Objet3D* o)
{
	meteor = o;
}

bool PatternManager::getIsActive()
{
	return isMeteorActive;
}

float PatternManager::getT()
{
	return t;
}

glm::vec3 PatternManager::getMetPos()
{
	return meteor->getPos();
}

glm::vec3 PatternManager::getActivePoint()
{
	return spawnPointMeteor * (1 - t) + finishPointMeteor * t;
}

void PatternManager::setSpeed(float s)
{
	speed = s;
}

void PatternManager::addSpeed(float s)
{
	speed += s;
}
