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
	vector<glm::vec3> norms;
	vector<Face> faces;
	vector<Tex> textureCoord;
	Texture texture;
	glm::mat4 viewMatrix;

	// Nouvelle structure de données pour face, permettant de tout stocker dans un vector
	vector<vraiFace> vraiFaces;




public :

	// Constructeurs
	Objet3D();

	// Getters
	vector<Vertex> getVertices();
	vector<Face> getFaces();  
	vector<glm::vec3> getNormals();
	Texture getTexture();
	vector<Tex> getTextureCoord();
	vector<vraiFace> getvraiFaces();

	// Setters
	void setVertices(vector<Vertex> v);
	void setFaces(vector<Face> f);
	void setTextureCoord(vector<Tex> t);
	void setTexture(Texture t);

	void setVraiFaces(); // A appeler une seule fois par objet, après loadOBJ pour transferer la structure de données

	// Methodes 
	void affichage();
	void LoadTexture(const char* path);
	void LoadOBJ(const char* filename);
	
};

#endif