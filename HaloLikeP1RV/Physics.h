
class Physics
{
protected:
	float yCoord;
	float actualInitialSpeed;
	float actualYInitialPosition;
	bool isJumping;
	float t;
public : 
	bool getIsJumping();
	float getYCoord();
	Physics();

	void setJump(float vInit,float y);
	void resetJump();
	void actualizeJump();
	bool isGoingDown();
};
