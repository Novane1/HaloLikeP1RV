#ifndef Camera_h
#define Camera_h

//Librairies
#include <GL/gl.h>
#include "glm/glm/glm.hpp"


using namespace std;
// Définition de la classe caméra
class Camera {
	glm::vec3 camera_position;
	glm::vec3 camera_up_vector;
	glm::vec3 camera_center_vector;


public :
	void updateCamera();//Mettre les coordonnées de notre objet camera dans la vrai caméra de la scène
	void goFrontCamera(float speed); // Augmente la coordonnée Z  de la caméra de z 
	void goSideCamera(float speed);
	Camera();
	void updateRotation(GLdouble x, GLdouble y, GLdouble oldX, GLdouble oldY, GLdouble mouseSensitivityAngle, GLdouble& actualAngleX, GLdouble& actualAngleY);
};

#endif

