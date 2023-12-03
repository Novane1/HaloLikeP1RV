#include "Ennemi.h"
std::vector<Ennemi*> Ennemi::listEnnemi;

void Ennemi::setHealth(float h)
{
	health = h;
}

void Ennemi::setHeight(float h)
{
	ourPos.y = h;
}

float Ennemi::getHealth()
{
	return health;
}

int Ennemi::getDamageFrame()
{
	return damageFrame;
}



Ennemi::Ennemi(float d, float h)
{
	health = h; damage = d; 
	listEnnemi.push_back(this);
	damageFrame = 0;
	isInvicible = false;
	ourPos = glm::vec3(0);
}

Ennemi::~Ennemi()
{
}

float Ennemi::isShot(glm::vec3 pos, glm::vec3 dir)
{
	if (snap.isVraiFaceNull()) {
		snap.setVraiFaces(vraiFaces);
	}
	if (!isInvicible)
	{
		glm::vec3 pt = snap.ptIntersectionGlobalF(pos-ourPos, dir);
		if (pt == glm::vec3(-1000000, -1000000, -1000000)) {
			return 0;
		}
		else {
			return glm::length(pt-pos+ourPos);
		}
		
	}
	else 
	{
		return 0;
	}
	

}

void Ennemi::startDamageAnimation()
{
	damageFrame = 1;
	isInvicible = true;
}

void Ennemi::increaseDamageFrame()
{
	if (damageFrame >= 1)
	{
		if (damageFrame < 100)
		{
			damageFrame++;
		}
		else { damageFrame = 0; isInvicible = false; }
	}
	
}

void Ennemi::resetDamageAnimation()
{
	damageFrame = 0;
}



float Ennemi::addHealth(float h)
{
	health += h;
	return health;
}
