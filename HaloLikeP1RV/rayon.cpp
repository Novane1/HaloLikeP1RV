#include "rayon.h"

rayon::rayon(glm::vec3 O, glm::vec3 D)
{
	Origin = O;
	return;
}
rayon::rayon(Camera& camera)
{
	Origin = camera.getPosition();
	return;
}
int rayon::getOx() const
{
	return Origin.x;
}
int rayon::getOy() const
{
	return Origin.y;
}
int rayon::getOz() const
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

glm::vec3 rayon::ptIntersectionF(Objet3D& NM) const
{
	glm::vec3 pt; // pt d'intersection
	glm::vec3 faceNormal;
	glm::vec3 facex, facey, facez;
	

	// Pour toutes les faces, vérifier l'intersection puis l'inclusion du pt dans la surface de la face.
	for (vector<Face>::iterator it = navMesh.begin(); it != navMesh.end(); it++) {
		faceNormal = NM.
	}


	return;
}
