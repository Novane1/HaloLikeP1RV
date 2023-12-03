#include "MovementManager.h"

MovementManager::MovementManager(Ennemi* o)
{
	chasing = false;
	idle = true;
	tIdle = 0;
	attackCloseRange = false;
	closeRangle = 0;
	attackLongRange = false;
	longRange = 0;
	obj = o;
}

void MovementManager::updatePos(Camera& c, PatternManager& p)
{
	glm::vec3 pos = c.getPosition();
	if (idle) {
		tIdle += 0.01;
		if (tIdle >= 2) { // Out on time

			tIdle = 0;
			chasing = true;
			idle = false;
			return;
		}
		return;

		
	}


	if (chasing) {
		
		if (glm::length(pos - obj->getPos()) <= 10.0f) { // Out on condition
			attackCloseRange = true;
			chasing = false;
			return;
		}

		if (glm::length(pos - obj->getPos()) >= 300.0f) { // Out on condition
			attackLongRange = true;
			chasing = false;
			return;
		}

		obj->setPos(    obj->getPos() + glm::normalize(pos - obj->getPos() )*0.1f ) ;
		return;

	}

	if (attackCloseRange) {
		closeRangle += 0.01;
		if (closeRangle >= 10) {
			if (glm::length(pos - obj->getPos()) <= 10.0f) {
				c.setHealth(c.getHealth()-2);
			}
			idle = true;
			attackCloseRange = false;
			closeRangle += 0.01;
		}
		return;
	}

	if (attackLongRange) {
		longRange += 0.01f;
		if (longRange >= 1) {
			pos.y -= 1;
			p.meteorAttack(glm::vec3(50), pos);
			chasing = true;
			attackLongRange = false;
		}
		return;
	}
}
