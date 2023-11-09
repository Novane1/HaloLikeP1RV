
#include "Physics.h"
#include <iostream>
bool Physics::getIsJumping()
{
	return isJumping;
}

float Physics::getYCoord()
{
	return yCoord;
}

Physics::Physics()
{
 actualInitialSpeed = 0; isJumping = false; t = 0; float actualYPosition = 0;
}

void Physics::setJump(float vInit, float y)
{
	t = 0;
	yCoord = y;
	isJumping = true;
	actualInitialSpeed = vInit;
	actualYInitialPosition = y;
}

void Physics::resetJump()
{
	yCoord = 0;
	t = 0;
	isJumping = false;

}

void Physics::actualizeJump()
{
	if (isJumping)
	{
		yCoord = actualYInitialPosition + actualInitialSpeed * t - 9.81 * t * t / 2;
		t += 0.01;
		
	}
	
	
	
}

bool Physics::isGoingDown()
{

	return (yCoord - (actualYInitialPosition + actualInitialSpeed * t - 9.81 * t * t / 2))>0.0;
}
