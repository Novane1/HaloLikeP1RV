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
	longCircleRadius = 40.0f;
	closeCircleRadius = 10.0f;
	meteorChase = false;
}

void MovementManager::updatePos(Camera& c, PatternManager& p)
{
	
	glm::vec3 pos = c.getPosition();

	if (p.getIsActive() && 10.0f+pos.y<= p.getMetPos().y && meteorChase ) {
		p.addSpeed(0.005f);
		p.meteorAttack(p.getMetPos(), glm::vec3(pos));
		
	}
	else {
		meteorChase = false;
	}

	

	if (idle) {
		tIdle += 0.01;
		if (tIdle >= 1) { // Out on time

			tIdle = 0;
			chasing = true;
			idle = false;
			return;
		}
		return;

		
	}


	if (chasing) {
		longCircleRadius -= .1f;
		if (glm::length(pos - obj->getPos()) <= 10.0f) { // Out on condition
			attackCloseRange = true;
			chasing = false;
			longCircleRadius = 40.0f;
			return;
		}

		if (glm::length(pos - obj->getPos()) >= longCircleRadius) { // Out on condition
			attackLongRange = true;
			chasing = false;
			longCircleRadius = 40.0f;
			return;
		}

		obj->setPos(    obj->getPos() + glm::normalize(pos - obj->getPos() )*0.1f ) ;
		return;

	}

	if (attackCloseRange) {
		closeCircleRadius = 20.0f;
		closeRangle += 0.01;
		
		if (closeRangle >= 1) {
			if (glm::length(pos - obj->getPos()) <= closeCircleRadius) {
				c.setHealth(c.getHealth()-2);
			}
			idle = true;
			attackCloseRange = false;
			closeRangle = 0;
			closeCircleRadius = 10.0f;
		}
		return;
	}

	if (attackLongRange) {
		
		if (longRange >= 1) {
			pos.y -= 1;
			if (!p.getIsActive()) {
				p.setSpeed(1.0f);
				p.meteorAttack(glm::vec3(50), pos);
				meteorChase = true;
			}
			
			chasing = true;
			attackLongRange = false;
			longRange = 0;
		}
		longRange += 0.01f;
		return;
	}

	/// update meteor
	
	
}

float MovementManager::getlongRadius()
{
	return longCircleRadius;
}

float MovementManager::getCloseRange()
{
	return closeRangle;
}

float MovementManager::getcloseRadius()
{
	return closeCircleRadius;
}
