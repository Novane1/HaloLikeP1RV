#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "rayon.h"
using namespace std;
class Collider 
{
protected :
	vector<Vertex> vertices;
	vector<Face> faces;
	vector<glm::vec3> norms;
	vector<vraiFace> vraiFaces;
	rayon ray;
	glm::vec3 offset;
	bool isActive;
	

public:
	
	void LoadCollider(const char* filename);
	bool checkCollision(Collider c,glm::vec3 offset);
	vector<Vertex> getVertices();
	vector<Face> getFaces();
	bool isInCollider(glm::vec3 pos);
	void setVraiFaces();
	void affichage();
	void setOffset(glm::vec3 pos);
	glm::vec3 getOffset();
	Collider();
	void setActive(bool set);
	bool getActive();
	
};

