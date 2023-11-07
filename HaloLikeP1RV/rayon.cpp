#include "rayon.h"
#include <iostream>
#include "glm/glm/glm.hpp"
#include "Camera.h"
#include "Objet3D.h"
#include "glm/glm/glm.hpp"

#define DISTANCECALCUL 10

// Contructeurs
rayon::rayon(glm::vec3 O, glm::vec3 D,vector<vraiFace> f)
{
	Origin = O;
	faces = f;
	return;
}
rayon::rayon(Camera& camera, vector<vraiFace> f)
{
	Origin = camera.getPosition();
	faces = f;
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
void rayon::setLocation(glm::vec3 O)
{
	Origin = O;
	return;
}

glm::vec3 rayon::ptIntersectionF( glm::vec3 pos)
{
	//pos.y += 20;
	
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
			length((*face).vertexC - pos) < DISTANCECALCUL) {

			// Vérification que "down" et la normale ne soit pas perpndiculaires 
			if (      dot(down, (*face).normal    ) != 0) {
				///(glm::length(down)* glm::length((*face).normal))  
				float D = -dot((*face).normal, (*face).vertexA);
				float distance = -(dot((*face).normal, pos) + D) / dot((*face).normal, down);
				//std::cout << "Distance : " << distance << endl;
				
				// Vérification de distance > 0 (le plan bien "devant" le rayon)
				if (distance > 0) {
					// on calcule maintenant trois produits vectoriels et on vérifie que P intersecte bien avec le triangle
					pt = pos + distance * down; // Position de l'intersetion
					glm::vec3 AB = (*face).vertexB - (*face).vertexA;
					glm::vec3 Apt = pt - (*face).vertexA;

					glm::vec3 AC = (*face).vertexC - (*face).vertexA;
					glm::vec3 Cpt = pt - (*face).vertexC;

					glm::vec3 BC = (*face).vertexC - (*face).vertexB;
					glm::vec3 Bpt = pt - (*face).vertexB;

					glm::vec3 normi = cross(AB, AC);

					// Dernière verification
					if (dot(cross(AB, Apt), normi) > 0 &&
						dot(cross(Cpt, AC), normi) > 0 &&
						dot(cross(BC, Bpt), normi) > 0)
					{
						
						return pt; // Retourner la valeure finale de pt
					}
					
				}
			}
		}

		
		
	}

	 pt = { -100,-100,-100 };
	return pt;

}
