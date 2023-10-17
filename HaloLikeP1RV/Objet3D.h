#pragma once
#ifndef Objet3D_h
#define Objet3D_h
#include "Geometry.h"
#include "Texture.h"

glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
class Objet3D
{
protected :
	vector<Vertex> vertices;
	vector<Face> faces;
	vector<Tex> textureCoord;
	Texture texture;
	glm::mat4 viewMatrix;



public :
	vector<Vertex> getVertices();
	vector<Face> getFaces();  
	Texture getTexture();
	vector<Tex> getTextureCoord();
	void setVertices(vector<Vertex> v);
	void setFaces(vector<Face> f);
	void setTextureCoord(vector<Tex> t);
	void setTexture(Texture t);
	void affichage();
	Objet3D();
	
};

#endif
