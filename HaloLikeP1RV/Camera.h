#ifndef Camera_h
#define Camera_h

//Librairies
#include <GL/gl.h>
#include "glm/glm/glm.hpp"


using namespace std;
// D�finition de la classe cam�ra
class Camera {
	glm::vec3 camera_position;
	glm::vec3 camera_up_vector;
	glm::vec3 camera_center_vector;


public :
	void updateCamera();//Mettre les coordonn�es de notre objet camera dans la vrai cam�ra de la sc�ne
	void goFrontCamera(float speed); // Augmente la coordonn�e Z  de la cam�ra de z 
	void goSideCamera(float speed);
	Camera();
	void updateRotation(GLdouble x, GLdouble y, GLdouble oldX, GLdouble oldY, GLdouble mouseSensitivityAngle, GLdouble& actualAngleX, GLdouble& actualAngleY);
};

#endif

