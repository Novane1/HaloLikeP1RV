#include "rayon.h"
#include <iostream>
#include "glm/glm/glm.hpp"
#include "Camera.h"
#include "Objet3D.h"
#include "glm/glm/glm.hpp"

#define DISTANCECALCUL 100000

// Contructeurs
rayon::rayon(glm::vec3 O, glm::vec3 D,vector<vraiFace> f)
{
	Origin = O;
	faces = f;
	
	return;
}
rayon::rayon( vector<vraiFace> f)
{
	Origin = glm::vec3(0);
	faces = f;

	return;
}
rayon::rayon()
{

	return;
}

// Getters
float rayon::getOx()
{
	return Origin.x;
}
float rayon::getOy() 
{
	return Origin.y;
}
float rayon::getOz() 
{
	return Origin.z;
}
glm::vec3 rayon::getOrigin() const
{
	return Origin;
}
bool rayon::isVraiFaceNull()
{
	return faces.size() == 0;
}
void rayon::setLocation(glm::vec3 O)
{
	Origin = O;
	return;
}


void rayon::setVraiFaces(vector<vraiFace> f) {

	faces = f;
}


bool RayIntersectsTriangle(glm::vec3 rayOrigin,
	glm::vec3 rayVector,
	glm::vec3 vertex0,
	glm::vec3 vertex1,
	glm::vec3 vertex2,
	glm::vec3& outIntersectionPoint)
{

	const float EPSILON = 0.0000001;
	glm::vec3 edge1, edge2, h, s, q;
	float a, f, u, v;
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0;
	h = glm::cross(rayVector,edge2);
	a = glm::dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return false;    // si parallèle
	f = 1.0 / a;
	s = rayOrigin - vertex0;
	u = f * dot(s,h);
	if (u < 0.0 || u > 1.0)
		return false;
	q = cross(s,edge1);
	v = f * dot(rayVector,q);
	if (v < 0.0 || u + v > 1.0)
		return false;

	float t = f * dot(edge2,q);
	if (t > EPSILON || t < -EPSILON) // intersection
	{
		outIntersectionPoint = rayOrigin + rayVector * t;
	
	return true;
	}
	else { 

		return false; }// pas d'inter

}

glm::vec3 rayon::ptIntersectionF( glm::vec3 pos)
{
	

	glm::vec3 pt(0.0f);// pt d'intersection
	glm::vec3 down;
	down.x = 0;
	down.y = -1;
	down.z = 0;

	


	// Pour toutes les faces, vérifier l'intersection puis l'inclusion du pt dans la surface de la face.
	for (vector<vraiFace>::iterator face = faces.begin(); face != faces.end(); face++) {
		 //Verifier si proche
		if (length((*face).vertexA - pos) < DISTANCECALCUL ||
			length((*face).vertexB - pos) < DISTANCECALCUL ||
			length((*face).vertexC - pos) < DISTANCECALCUL) 
		{
			bool isOk = RayIntersectsTriangle(pos, down, (*face).vertexC, (*face).vertexB, (*face).vertexA, pt);
			if (isOk) { return pt; }

		}
	}
	pt = { -100,-100,-100 }; return pt;
		
}

bool rayon::ptIntersectionGlobalF(glm::vec3 pos,glm::vec3 dir)
{


	glm::vec3 pt;







	// Pour toutes les faces, vérifier l'intersection puis l'inclusion du pt dans la surface de la face.
	for (vector<vraiFace>::iterator face = faces.begin(); face != faces.end(); face++) {

			bool isOk = RayIntersectsTriangle(pos, dir, (*face).vertexC, (*face).vertexB, (*face).vertexA, pt);
			if (isOk) { return true; }

	}
	return false;

}

		

