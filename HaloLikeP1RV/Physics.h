
class Physics
{
protected:
	float yCoord; // coordonnée exact de l'objet
	float actualInitialSpeed; // Vitesse initial (pour le saut)
	float actualYInitialPosition; // Position en Y initial pour le saut
	bool isJumping; // est ce que le saut est en cours
	float t; // temps
public : 
	bool getIsJumping();
	float getYCoord();
	Physics();

	void setJump(float vInit,float y);
	void resetJump();
	void actualizeJump();
	bool isGoingDown();
};
