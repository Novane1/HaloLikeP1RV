#include "ReloadManager.h"
#include <cstdlib>  // Pour rand() et srand()
#include <ctime> 
void ReloadManager::spawnOrb()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	int nombreAleatoire = std::rand() % (faces.size());
	pos = faces[nombreAleatoire].vertexA;
	pos.y += 1;
}

ReloadManager::ReloadManager(Objet3D o, Shader s, vector<vraiFace> f,ShootBar* sh)
{
	orb = o;
	orbShader = s;
	isActive = false;
	pos = glm::vec3(0);
	faces = f;
	time = 0;
	shoot = sh;
}

void ReloadManager::actTime(glm::vec3 camPos, glm::vec3 camTarget)
{
	if (!isActive) { time += 1.0f; }
	

	if (isActive && this->isIn(camPos)) {

		isActive = false;
		time = 0;
		shoot->resetAmo();
	}
	else if (time >= 1000.0f) {
		isActive = true;
		this->spawnOrb();
		time = 0;
		
	}
	
}

bool ReloadManager::isIn(glm::vec3 playerPos)
{
	return playerPos.y-4 >= (pos.y -2 ) && playerPos.y-4 <= (pos.y + 2) && playerPos.x >= (pos.x - 2) && playerPos.x <= (pos.x + 2) && playerPos.z >= (pos.z - 2) && playerPos.z <= (pos.z + 2);
}

void ReloadManager::affichage(glm::vec3 camPos, glm::vec3 camTarget)
{
	if (isActive) {
		orb.affichageShaderOffset(orbShader, camPos, camTarget, glm::vec3(0.0, 1.0, 0.0),pos);
	}
}
