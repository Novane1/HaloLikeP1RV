#ifndef Camera_h
#define Camera_h

//Librairies
#pragma once
#include "windows.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/gl.h>
#include <glut.h>
#include "Vector3.h"
using namespace std;
// D�finition de la classe cam�ra
class Camera {
	Vector3 camera_position;
	Vector3 camera_up_vector;
	Vector3 camera_center_vector;


public :
	void updateCamera();//Mettre les coordonn�es de notre objet camera dans la vrai cam�ra de la sc�ne
	void goFrontCamera(float speed); // Augmente la coordonn�e Z  de la cam�ra de z 
	void goSideCamera(float speed);
	Camera();
	void updateRotation(GLdouble x, GLdouble y, GLdouble oldX, GLdouble oldY, GLdouble mouseSensitivityAngle, GLdouble& actualAngleX, GLdouble& actualAngleY);
};

#endif

