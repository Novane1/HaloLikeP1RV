#include "Ennemi.h"
std::vector<Ennemi*> Ennemi::listEnnemi;

void Ennemi::setHealth(float h)
{
	health = h;
}

float Ennemi::getHealth()
{
	return health;
}

Ennemi::Ennemi(float d, float h)
{
	health = h; damage = d; 
	listEnnemi.push_back(this);
}

Ennemi::~Ennemi()
{
}

bool Ennemi::isShot(glm::vec3 pos, glm::vec3 dir)
{
	if (snap.isVraiFaceNull()) {
		snap.setVraiFaces(vraiFaces);
	}
	return snap.ptIntersectionGlobalF(pos, dir);

}

float Ennemi::addHealth(float h)
{
	health += h;
	return health;
}
