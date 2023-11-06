#include "Ennemi.h"
std::vector<Ennemi*> Ennemi::listEnnemi;
Ennemi::Ennemi(float d, float h)
{
	health = h; damage = d;
	listEnnemi.push_back(this);
}