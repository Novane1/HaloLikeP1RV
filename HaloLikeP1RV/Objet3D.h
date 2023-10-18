#pragma once
#ifndef Objet3D_h
#define Objet3D_h
#include <vector>
#include "Texture.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"


using namespace std;
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
	void LoadTexture(const char* path);
	void LoadOBJ(const char* filename);
	
};

#endif
