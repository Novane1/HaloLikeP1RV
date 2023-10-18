#include <windows.h>
#include "Player.h"

glm::vec3 Player::getPosition()
{
	return position;
}

void Player::setPosition(glm::vec3 v)
{
	position = v;
}



void Player::setPlayer(Objet3D *p)
{
	player = p;
}

void Player::affichage()
{
	player->affichage();
}

Player::Player()
{

	position = { 0,0,0 };
}
