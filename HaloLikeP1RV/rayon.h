#pragma once


#include <Windows.h>
#include "glm/glm/glm.hpp"
#include <iostream>
#include "Geometry.h"
#include <vector>
using namespace std;


//class Camera;
//class Objet3D;

// Classe définissant une source de rayons basique, tirant (pour l'instant) uniquement vers le bas. 
// Servant à placer le joueur sur un navMesh.
// Contient le navMesh
class rayon
{
	
	// ATTRIBUTS ///////////////////////////////////////
	glm::vec3 Origin;
	vector<vraiFace> faces;
	//vector<Face> navMesh;

	/* POUR IMPLEMENTATION D'AUTRES DIRECTIONS PLUS TARD
	glm::vec3 Direction; */

public :

	// CONSTRUCTEURS ///////////////////////////////////
	rayon(glm::vec3 O, glm::vec3 D, vector<vraiFace> f);
	rayon( vector<vraiFace> f);
	rayon();


	// GETTERS /////////////////////////////////////////
	float getOx(); float getOy(); float getOz();
	glm::vec3 getOrigin() const;
	bool isVraiFaceNull();
	/* POUR IMPLEMENTATION D'AUTRES DIRECTIONS PLUS TARD
	int getdirx(); int getdiry(); int getdirz(); 
	glm::vec3 getDirection(); */


	// SETTERS /////////////////////////////////////////
	void setLocation(glm::vec3 O);
	void setVraiFaces(vector<vraiFace> f);
	/* POUR IMPLEMENTATION D'AUTRES DIRECTIONS PLUS TARD
	void setDirection(glm::vec3 D); */


	// METHODES /////////////////////////////////////////
	
	// Distance d'intersection entre plan et rayon

	// Distance d'intersection (si intersection) entre face et rayon

	// Point d'intersection entre plan et rayon

	// Point d'intersection (si intersection) entre face et rayon
	glm::vec3 ptIntersectionF( glm::vec3 pos);
	glm::vec3 ptIntersectionGlobalF(glm::vec3 pos, glm::vec3 dir);
	bool ptIntersectionGlobalFBool(glm::vec3 pos, glm::vec3 dir);

};

