#pragma once

#include <Windows.h>
#include "Camera.h"
#include "Objet3D.h"

// Classe définissant une source de rayons basique, tirant (pour l'instant) uniquement vers le bas. Servant à placer le joueur sur un navMesh.
// Contient le navMesh
class rayon
{
	// ATTRIBUTS ///////////////////////////////////////
	glm::vec3 Origin;
	vector<Face> navMesh;

	/* POUR IMPLEMENTATION D'AUTRES DIRECTIONS PLUS TARD
	glm::vec3 Direction; */

public :

	// CONSTRUCTEURS ///////////////////////////////////
	rayon(glm::vec3 O, glm::vec3 D);
	rayon(Camera &camera);


	// GETTERS /////////////////////////////////////////
	int getOx() const;int getOy() const;int getOz() const;
	glm::vec3 getOrigin() const;

	/* POUR IMPLEMENTATION D'AUTRES DIRECTIONS PLUS TARD
	int getdirx(); int getdiry(); int getdirz(); 
	glm::vec3 getDirection(); */


	// SETTERS /////////////////////////////////////////
	void setLocation(glm::vec3 O);

	/* POUR IMPLEMENTATION D'AUTRES DIRECTIONS PLUS TARD
	void setDirection(glm::vec3 D); */


	// METHODES /////////////////////////////////////////
	
	// Distance d'intersection entre plan et rayon

	// Distance d'intersection (si intersection) entre face et rayon

	// Point d'intersection entre plan et rayon

	// Point d'intersection (si intersection) entre face et rayon
	glm::vec3 ptIntersectionF(Objet3D &NavMesh) const;


};

