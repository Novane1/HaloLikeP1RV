#pragma once
#ifndef Texture_h
#define Texture_h
#include "Geometry.h"
#include <GL/gl.h>
class Texture
{
protected :
	GLuint ID;
public :
	//Getters
	GLuint getID();
	Texture();
	void setID(GLuint n);
};

#endif

