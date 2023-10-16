#include "Player.h"

glm::vec3 Player::getPosition()
{
	return position;
}

glm::vec3 Player::setPosition(glm::vec3 v)
{
	position = v;
}

void Player::affichage()
{
	player->affichage();
}
