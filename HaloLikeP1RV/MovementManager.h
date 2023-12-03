#pragma once

#include "Ennemi.h"
#include "Camera.h"
#include "glm/glm/glm.hpp"
#include "PatternManager.h"
class MovementManager
{
protected:
	Ennemi* obj;
	bool chasing;
	bool idle;
	float tIdle;
	bool attackCloseRange;
	float closeRangle;
	bool attackLongRange;
	float longRange;
	
public:
	MovementManager(Ennemi* o);
	void updatePos(Camera &c, PatternManager &p);
};

