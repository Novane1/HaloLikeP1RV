#include "PatternManager.h"

PatternManager::PatternManager()
{
	isMeteorActive = false;
	spawnPointMeteor = glm::vec3(0);
	finishPointMeteor = glm::vec3(0);
	t = 0;
}

void PatternManager::meteorAttack(glm::vec3 s, glm::vec3 f)
{
	spawnPointMeteor = s;
	finishPointMeteor = f;
	isMeteorActive = true;
}

void PatternManager::updateMeteor(Shader meteorShader, glm::vec3 camPos,glm::vec3 targetPos)
{
	if (isMeteorActive) {
		if (t < 1) {
			t += 0.005;
			meteor->setPos(spawnPointMeteor * (1 - t) + finishPointMeteor * t);
			meteor->affichageShaderOffset(meteorShader, camPos, targetPos, glm::vec3(0, 1, 0), meteor->getPos());
		}
		else {
			t = 0;
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

glm::vec3 PatternManager::getActivePoint()
{
	return spawnPointMeteor * (1 - t) + finishPointMeteor * t;
}
