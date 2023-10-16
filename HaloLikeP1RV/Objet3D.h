#pragma once
#include "Geometry.h"
#include "Texture.h"
class Objet3D
{
protected :
	vector<Vertex> vertices;
	vector<Face> faces;
	vector<Tex> textureCoord;
	Texture texture;



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

